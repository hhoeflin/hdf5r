#!/usr/bin/env bash
# Check one R/HDF5 combination using native source builds on macOS.
set -euo pipefail

R_VERSION="${1:?usage: run-check.sh <R_VERSION> <HDF5_VERSION> [pkg-dir] [out-dir]}"
HDF5_VERSION="${2:?usage: run-check.sh <R_VERSION> <HDF5_VERSION> [pkg-dir] [out-dir]}"

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
HARNESS_DIR="$(cd "${SCRIPT_DIR}/.." && pwd)"
PKG_DIR="${3:-$(cd "${HARNESS_DIR}/.." && pwd)}"
OUT_DIR="${4:-${HARNESS_DIR}/logs}"
R_PREFIX="${HARNESS_DIR}/installs/R/${R_VERSION}"
R_LIBRARY="${HARNESS_DIR}/installs/R-libs/${R_VERSION}"
HDF5_PREFIX="${HARNESS_DIR}/installs/hdf5/${HDF5_VERSION}"
NAME="macos-r${R_VERSION}-hdf5v${HDF5_VERSION}"
STATUS="${OUT_DIR}/${NAME}.status"

mkdir -p "${OUT_DIR}"
fail() {
    echo FAIL > "${STATUS}"
    echo "run-check.sh: ERROR: $*" >&2
    exit 2
}

[ -x "${R_PREFIX}/bin/R" ] \
    || fail "R ${R_VERSION} is missing; run: gmake build-macos R_VERSION=${R_VERSION} HDF5_VERSION=${HDF5_VERSION}"
[ -f "${HDF5_PREFIX}/.hdf5r-harness-complete" ] \
    || fail "HDF5 ${HDF5_VERSION} is missing; run: gmake build-macos R_VERSION=${R_VERSION} HDF5_VERSION=${HDF5_VERSION}"

export PATH="${R_PREFIX}/bin:${HDF5_PREFIX}/bin:/Library/TeX/texbin:${PATH}"
export R_LIBS_USER="${R_LIBRARY}"
export R_ENVIRON_USER=/dev/null
export R_PROFILE_USER=/dev/null
unset R_LIBS R_LIBS_SITE
export CPPFLAGS="-I${HDF5_PREFIX}/include ${CPPFLAGS:-}"
export LDFLAGS="-L${HDF5_PREFIX}/lib ${LDFLAGS:-}"
export CPATH="${HDF5_PREFIX}/include:${CPATH:-}"
export LIBRARY_PATH="${HDF5_PREFIX}/lib:${LIBRARY_PATH:-}"
export DYLD_LIBRARY_PATH="${HDF5_PREFIX}/lib:${DYLD_LIBRARY_PATH:-}"
export HDF5_ROOT="${HDF5_PREFIX}"
export HDF5_VERSION

# pandoc/pdflatex/qpdf/java are verified by common/run-check.sh.

"${R_PREFIX}/bin/Rscript" "${HARNESS_DIR}/common/install-r-packages.R" --check \
    || fail "R packages are missing; run: gmake build-macos R_VERSION=${R_VERSION} HDF5_VERSION=${HDF5_VERSION}"

"${HARNESS_DIR}/common/run-check.sh" "${PKG_DIR}" "${OUT_DIR}" "${NAME}"
