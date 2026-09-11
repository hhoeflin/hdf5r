#!/usr/bin/env bash
# Build a specific HDF5 version from source on macOS (cached).
#
# usage: build-hdf5.sh <HDF5_VERSION> <build-system>
#
# Installs under harness/installs/hdf5 using the shared HDF5 builder.
set -euo pipefail

HDF5_VERSION="${1:?usage: build-hdf5.sh <HDF5_VERSION>}"
BUILD_SYSTEM="${2:-auto}"

log() { echo "build-hdf5.sh: $*"; }
die() { echo "build-hdf5.sh: ERROR: $*" >&2; exit 1; }

HARNESS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
LOG_DIR="${HARNESS_DIR}/logs"
HDF5_TAG="${HDF5_VERSION}"
if [ "${BUILD_SYSTEM}" = "cmake" ] && [[ "${HDF5_VERSION}" == 1.* ]]; then
    HDF5_TAG="${HDF5_VERSION}-cmake"
fi
LOG_FILE="${LOG_DIR}/build-macos-hdf5v${HDF5_TAG}.log"

if [ -z "${HDF5R_HDF5_BUILD_LOGGING:-}" ]; then
    mkdir -p "${LOG_DIR}"
    set +e
    HDF5R_HDF5_BUILD_LOGGING=1 "${BASH_SOURCE[0]}" "${HDF5_VERSION}" "${BUILD_SYSTEM}" 2>&1 | tee "${LOG_FILE}"
    status="${PIPESTATUS[0]}"
    set -e
    exit "${status}"
fi

command -v brew >/dev/null || die "Homebrew required (see https://brew.sh)"

# HDF5 >= 2.0 and explicit pre-2.0 CMake builds need CMake.
if [ "${BUILD_SYSTEM}" = "cmake" ] || [[ "${HDF5_VERSION}" == 2.* ]]; then
        brew list --formula cmake >/dev/null 2>&1 || brew install cmake
fi

HDF5_PREFIX="${HARNESS_DIR}/installs/hdf5/${HDF5_TAG}"

mkdir -p "$(dirname "${HDF5_PREFIX}")"
"${HARNESS_DIR}/common/compile-hdf5.sh" "${HDF5_VERSION}" "${HDF5_PREFIX}" "$(sysctl -n hw.ncpu)" "${BUILD_SYSTEM}"

log "HDF5 ${HDF5_VERSION} (${BUILD_SYSTEM}) ready at ${HDF5_PREFIX}"
