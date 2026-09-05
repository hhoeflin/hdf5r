#!/usr/bin/env bash
# Build R from source on macOS and install its hdf5r check dependencies.
set -euo pipefail

R_VERSION="${1:?usage: build-r.sh <R_VERSION>}"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
HARNESS_DIR="$(cd "${SCRIPT_DIR}/.." && pwd)"
R_PREFIX="${HARNESS_DIR}/installs/R/${R_VERSION}"
R_LIBRARY="${HARNESS_DIR}/installs/R-libs/${R_VERSION}"
JOBS="$(sysctl -n hw.ncpu)"
DEVEL_MARKER="${R_PREFIX}/.hdf5r-devel-date"

# R's build system defines its own make variables (e.g. R); never let
# MAKEFLAGS from an outer gmake invocation leak into it.
unset MAKEFLAGS MAKEOVERRIDES MFLAGS MAKEFILES GNUMAKEFLAGS

log() { echo "build-r.sh: $*"; }
die() { echo "build-r.sh: ERROR: $*" >&2; exit 1; }

xcode-select -p >/dev/null 2>&1 \
    || die "Xcode Command Line Tools required (run: xcode-select --install)"
command -v brew >/dev/null || die "Homebrew required (see https://brew.sh)"

brew_packages=(gcc pcre2 xz pkgconf autoconf automake checkbashisms freetype harfbuzz fribidi)
if [ "${R_VERSION}" = "devel" ]; then
    brew_packages+=(subversion)
fi
for package in "${brew_packages[@]}"; do
    brew list --formula "${package}" >/dev/null 2>&1 || brew install "${package}"
done

GCC_PREFIX="$(brew --prefix gcc)"
PCRE2_PREFIX="$(brew --prefix pcre2)"
XZ_PREFIX="$(brew --prefix xz)"
PKGCONF_PREFIX="$(brew --prefix pkgconf)"
FREETYPE_PREFIX="$(brew --prefix freetype)"
HARFBUZZ_PREFIX="$(brew --prefix harfbuzz)"
FRIBIDI_PREFIX="$(brew --prefix fribidi)"
export PATH="${GCC_PREFIX}/bin:${PATH}"
export PATH="${PKGCONF_PREFIX}/bin:${PATH}"
export CPPFLAGS="-I${PCRE2_PREFIX}/include -I${XZ_PREFIX}/include -I${FREETYPE_PREFIX}/include -I${HARFBUZZ_PREFIX}/include -I${FRIBIDI_PREFIX}/include ${CPPFLAGS:-}"
export LDFLAGS="-L${PCRE2_PREFIX}/lib -L${XZ_PREFIX}/lib -L${FREETYPE_PREFIX}/lib -L${HARFBUZZ_PREFIX}/lib -L${FRIBIDI_PREFIX}/lib ${LDFLAGS:-}"
export PKG_CONFIG_PATH="${PCRE2_PREFIX}/lib/pkgconfig:${XZ_PREFIX}/lib/pkgconfig:${FREETYPE_PREFIX}/lib/pkgconfig:${HARFBUZZ_PREFIX}/lib/pkgconfig:${FRIBIDI_PREFIX}/lib/pkgconfig:${PKG_CONFIG_PATH:-}"

gfortran=""
for candidate in "${GCC_PREFIX}/bin/gfortran" "${GCC_PREFIX}"/bin/gfortran-*; do
    if [ -x "${candidate}" ]; then
        gfortran="${candidate}"
        break
    fi
done
[ -n "${gfortran}" ] || die "gfortran not found after installing Homebrew gcc"
export FC="${gfortran}"
export F77="${gfortran}"

if [ "${R_VERSION}" = "devel" ] && [ -x "${R_PREFIX}/bin/R" ]; then
    today="$(date -u +%Y-%m-%d)"
    built_date="$(cat "${DEVEL_MARKER}" 2>/dev/null || true)"
    if [ "${built_date}" != "${today}" ]; then
        log "refreshing the daily R-devel build"
        rm -rf "${R_PREFIX}" "${R_LIBRARY}"
    fi
fi

if [ -e "${R_PREFIX}" ] && [ ! -x "${R_PREFIX}/bin/R" ]; then
    log "removing incomplete R install at ${R_PREFIX}"
    rm -rf "${R_PREFIX}"
fi

if [ -x "${R_PREFIX}/bin/R" ]; then
    log "R ${R_VERSION} already present at ${R_PREFIX}"
else
    WORK="$(mktemp -d)"
    trap 'rm -rf "${WORK}"' EXIT
    cd "${WORK}"

    if [ "${R_VERSION}" = "devel" ]; then
        log "checking out R-devel from SVN trunk"
        svn co https://svn.r-project.org/R/trunk R-src
        cd R-src
        ./tools/rsync-recommended
    else
        R_MAJOR="${R_VERSION%%.*}"
        log "downloading R ${R_VERSION} from CRAN"
        curl -fSsL --retry 3 \
            -o "R-${R_VERSION}.tar.gz" \
            "https://cran.r-project.org/src/base/R-${R_MAJOR}/R-${R_VERSION}.tar.gz"
        tar -xzf "R-${R_VERSION}.tar.gz"
        cd "R-${R_VERSION}"
    fi

    log "configuring R ${R_VERSION} at ${R_PREFIX}"
    ./configure \
        --prefix="${R_PREFIX}" \
        --enable-R-shlib \
        --with-x=no \
        --with-recommended-packages
    make -j"${JOBS}"
    make install
    if [ "${R_VERSION}" = "devel" ]; then
        date -u +%Y-%m-%d > "${DEVEL_MARKER}"
    fi
fi

mkdir -p "${R_LIBRARY}"
export R_LIBS_USER="${R_LIBRARY}"
export CRAN_REPO="${CRAN_REPO:-https://cloud.r-project.org}"
export R_ENVIRON_USER=/dev/null
export R_PROFILE_USER=/dev/null
unset R_LIBS R_LIBS_SITE
log "installing check dependencies into ${R_LIBRARY}"
"${R_PREFIX}/bin/Rscript" "${SCRIPT_DIR}/../common/install-r-packages.R"

log "R ${R_VERSION} is ready at ${R_PREFIX}"
