#!/usr/bin/env bash
# Check one R/HDF5 combination using native source builds on macOS.
set -euo pipefail

R_VERSION="${1:?usage: run-check.sh <R_VERSION> <HDF5_VERSION> [pkg-dir] [out-root]}"
HDF5_VERSION="${2:?usage: run-check.sh <R_VERSION> <HDF5_VERSION> [pkg-dir] [out-root]}"

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
HARNESS_DIR="$(cd "${SCRIPT_DIR}/.." && pwd)"
PKG_DIR="${3:-$(cd "${HARNESS_DIR}/.." && pwd)}"
OUT_ROOT="${4:-${HARNESS_DIR}/logs}"
R_PREFIX="${HARNESS_DIR}/installs/R/${R_VERSION}"
R_LIBRARY="${HARNESS_DIR}/installs/R-libs/${R_VERSION}"
HDF5_PREFIX="${HARNESS_DIR}/installs/hdf5/${HDF5_VERSION}"
NAME="macos-r${R_VERSION}-hdf5v${HDF5_VERSION}"
OUT_DIR="${OUT_ROOT}/check-${NAME}"
STATUS="${OUT_DIR}/status"

case "${R_VERSION}" in
    ''|*[!A-Za-z0-9_.-]*) echo "run-check.sh: ERROR: R_VERSION contains unsafe characters" >&2; exit 2;;
esac
case "${HDF5_VERSION}" in
    ''|*[!A-Za-z0-9_.-]*) echo "run-check.sh: ERROR: HDF5_VERSION contains unsafe characters" >&2; exit 2;;
esac
[ -n "${OUT_ROOT}" ] && [ "${OUT_ROOT}" != "/" ] \
    || { echo "run-check.sh: ERROR: output root must not be empty or /" >&2; exit 2; }

mkdir -p "${OUT_ROOT}"
rm -rf "${OUT_DIR}"
mkdir -p "${OUT_DIR}"
PRECHECK_LOG="${OUT_DIR}/preflight.log"
{
    echo "=== hdf5r preflight: ${NAME} ==="
    echo "=== started: $(date -u '+%Y-%m-%dT%H:%M:%SZ') ==="
    echo
} > "${PRECHECK_LOG}"
exec > >(tee "${OUT_DIR}/runner.log") 2>&1

fail() {
    echo FAIL > "${STATUS}"
    echo "run-check.sh: ERROR: $*" | tee -a "${PRECHECK_LOG}" >&2
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
export HDF5_ROOT="${HDF5_PREFIX}"
export HDF5_VERSION

# pandoc/pdflatex/qpdf/java are verified by common/run-check.sh.

"${R_PREFIX}/bin/Rscript" "${HARNESS_DIR}/common/install-r-packages.R" --check \
    > "${OUT_DIR}/dependencies.log" 2>&1 \
    || fail "R packages are missing; run: gmake build-macos R_VERSION=${R_VERSION} HDF5_VERSION=${HDF5_VERSION}"

"${HARNESS_DIR}/common/run-check.sh" "${PKG_DIR}" "${OUT_DIR}" "${NAME}"
