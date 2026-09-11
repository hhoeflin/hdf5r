#!/usr/bin/env bash
# Build HDF5 from source into an absolute prefix.
set -euo pipefail

HDF5_VERSION="${1:?usage: compile-hdf5.sh <hdf5-version> <prefix> [jobs] [build-system]}"
PREFIX="${2:?usage: compile-hdf5.sh <hdf5-version> <prefix> [jobs] [build-system]}"
JOBS="${3:-$(command -v nproc >/dev/null && nproc || sysctl -n hw.ncpu 2>/dev/null || echo 4)}"
BUILD_SYSTEM="${4:-auto}"
MARKER="${PREFIX}/.hdf5r-harness-complete"

# Never let MAKEFLAGS from an outer gmake invocation leak into HDF5's build.
unset MAKEFLAGS MAKEOVERRIDES MFLAGS MAKEFILES GNUMAKEFLAGS

die() { echo "compile-hdf5.sh: ERROR: $*" >&2; exit 1; }

version_major="${HDF5_VERSION%%.*}"
case "${BUILD_SYSTEM}" in
    auto)
        if [ "${version_major}" -ge 2 ]; then
            BUILD_SYSTEM=cmake
        else
            BUILD_SYSTEM=autotools
        fi
        ;;
    autotools|cmake) ;;
    *) die "unsupported HDF5 build system: ${BUILD_SYSTEM}" ;;
esac

if [ "${BUILD_SYSTEM}" = "autotools" ] && [ "${version_major}" -ge 2 ]; then
    die "HDF5 ${HDF5_VERSION} requires CMake"
fi

case "${PREFIX}" in
    /*) ;;
    *) die "prefix must be an absolute path: ${PREFIX}" ;;
esac

installed_version() {
    "${PREFIX}/bin/h5cc" -showconfig \
        | awk '/HDF5 Version:/ { print $NF; exit }'
}

if [ -f "${MARKER}" ] && [ -x "${PREFIX}/bin/h5cc" ]; then
    actual_version="$(installed_version)"
    [ "${actual_version}" = "${HDF5_VERSION}" ] \
        || die "${PREFIX} contains HDF5 ${actual_version}, expected ${HDF5_VERSION}"
    installed_build_system="$(cat "${MARKER}")"
    [ -z "${installed_build_system}" ] || [ "${installed_build_system}" = "${BUILD_SYSTEM}" ] \
        || die "${PREFIX} contains HDF5 built with ${installed_build_system}, expected ${BUILD_SYSTEM}"
    echo "compile-hdf5.sh: HDF5 ${HDF5_VERSION} already present at ${PREFIX}"
    exit 0
fi

if [ -e "${PREFIX}" ]; then
    die "incomplete install at ${PREFIX}; remove it before rebuilding"
fi

WORKDIR="$(mktemp -d)"
STAGE="$(dirname "${PREFIX}")/.hdf5-stage-$$"
cleanup() { rm -rf "${WORKDIR}" "${STAGE}"; }
trap cleanup EXIT
mkdir -p "${STAGE}"

cd "${WORKDIR}"
MAJOR_MINOR="${HDF5_VERSION%.*}"
URLS=(
    "https://github.com/HDFGroup/hdf5/releases/download/${HDF5_VERSION}/hdf5-${HDF5_VERSION}.tar.gz"
    "https://github.com/HDFGroup/hdf5/releases/download/hdf5_${HDF5_VERSION}/hdf5-${HDF5_VERSION}.tar.gz"
    "https://github.com/HDFGroup/hdf5/releases/download/hdf5-${HDF5_VERSION//./_}/hdf5-${HDF5_VERSION}.tar.gz"
    "https://support.hdfgroup.org/releases/hdf5/v$(echo "${MAJOR_MINOR}" | tr '.' '_')/v${HDF5_VERSION//./_}/downloads/hdf5-${HDF5_VERSION}.tar.gz"
    "https://support.hdfgroup.org/ftp/HDF5/releases/hdf5-${MAJOR_MINOR}/hdf5-${HDF5_VERSION}/src/hdf5-${HDF5_VERSION}.tar.gz"
)
TARBALL="hdf5-${HDF5_VERSION}.tar.gz"

downloaded=false
for url in "${URLS[@]}"; do
    echo "compile-hdf5.sh: trying ${url}"
    if curl -fSsL --retry 3 -o "${TARBALL}" "${url}"; then
        downloaded=true
        break
    fi
done
[ "${downloaded}" = true ] || die "could not download hdf5-${HDF5_VERSION}"

tar -xzf "${TARBALL}"
cd "hdf5-${HDF5_VERSION}"

version_rest="${HDF5_VERSION#*.}"
version_minor="${version_rest%%.*}"

if [ "${BUILD_SYSTEM}" = "cmake" ]; then
    command -v cmake >/dev/null || die "CMake is required for this HDF5 build"
    cmake -S . -B build \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_INSTALL_PREFIX="${PREFIX}" \
        -DBUILD_SHARED_LIBS=ON \
        -DBUILD_STATIC_LIBS=OFF \
        -DHDF5_BUILD_HL_LIB=ON \
        -DHDF5_BUILD_CPP_LIB=OFF \
        -DHDF5_BUILD_EXAMPLES=OFF \
        -DHDF5_BUILD_TESTS=OFF \
        -DHDF5_BUILD_TOOLS=ON \
        -DHDF5_ENABLE_DEPRECATED_SYMBOLS=ON \
        -DHDF5_ENABLE_ZLIB_SUPPORT=ON \
        -DBUILD_TESTING=OFF
    cmake --build build --parallel "${JOBS}"
    DESTDIR="${STAGE}" cmake --install build
else
    # HDF5 1.8 ships obsolete config scripts that do not recognize arm64.
    # Prefer the current system copies when the source tree includes them.
    for config_tool in config.guess config.sub; do
        if [ -f "bin/${config_tool}" ] && [ -f "/usr/share/misc/${config_tool}" ]; then
            cp "/usr/share/misc/${config_tool}" "bin/${config_tool}"
        fi
    done
    configure_flags=("--prefix=${PREFIX}")
    if [ "${version_major}" -gt 1 ] \
        || { [ "${version_major}" -eq 1 ] && [ "${version_minor}" -ge 10 ]; }; then
        configure_flags+=(--enable-build-mode=production)
    else
        configure_flags+=(--enable-production)
        # HDF5 1.8's bundled tools and tests do not build with current GCC.
        configure_flags+=(--disable-tools --disable-tests)
    fi
    ./configure "${configure_flags[@]}"
    make -j"${JOBS}"
    if [ "${version_major}" -eq 1 ] && [ "${version_minor}" -lt 10 ]; then
        # HDF5 1.8's top-level install ignores DESTDIR for examples.
        make DESTDIR="${STAGE}" install-recursive
    else
        make DESTDIR="${STAGE}" install
    fi
fi

STAGED_PREFIX="${STAGE}${PREFIX}"
[ -x "${STAGED_PREFIX}/bin/h5cc" ] || die "build did not install h5cc"
mkdir -p "$(dirname "${PREFIX}")"
mv "${STAGED_PREFIX}" "${PREFIX}"

if ! actual_version="$(installed_version)"; then
    die "installed HDF5 does not provide a working h5cc at ${PREFIX}/bin/h5cc"
fi
[ "${actual_version}" = "${HDF5_VERSION}" ] \
    || die "installed HDF5 reports ${actual_version}, expected ${HDF5_VERSION}"
if "${PREFIX}/bin/h5cc" -show | grep -F "${STAGE}" >/dev/null; then
    die "installed h5cc contains its staging path"
fi
printf '%s\n' "${BUILD_SYSTEM}" > "${MARKER}"

echo "compile-hdf5.sh: HDF5 ${HDF5_VERSION} (${BUILD_SYSTEM}) installed at ${PREFIX}"
