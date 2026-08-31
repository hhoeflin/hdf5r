#!/usr/bin/env bash
# Run `R CMD build --no-build-vignettes` and `R CMD check --as-cran`, recording
# a reliable status.
set -euo pipefail

PKG_SRC="${1:?usage: run-check.sh <pkg-source-dir> <out-dir> <log-name-base>}"
OUT_DIR="${2:?usage: run-check.sh <pkg-source-dir> <out-dir> <log-name-base>}"
NAME="${3:?usage: run-check.sh <pkg-source-dir> <out-dir> <log-name-base>}"

# R CMD build/check invoke make internally; keep outer gmake flags out.
unset MAKEFLAGS MAKEOVERRIDES MFLAGS MAKEFILES GNUMAKEFLAGS

mkdir -p "${OUT_DIR}"
LOG="${OUT_DIR}/${NAME}.log"
STATUS="${OUT_DIR}/${NAME}.status"
WORK=""

: > "${LOG}"
echo RUNNING > "${STATUS}"

on_exit() {
    rc=$?
    [ -z "${WORK}" ] || rm -rf "${WORK}"
    if [ "${rc}" -ne 0 ]; then
        echo FAIL > "${STATUS}"
    fi
}
trap on_exit EXIT

die() {
    echo "run-check.sh: ERROR: $*" | tee -a "${LOG}" >&2
    exit 2
}

command -v R >/dev/null || die "R not found in PATH"
[ -f "${PKG_SRC}/DESCRIPTION" ] || die "${PKG_SRC} is not an R package"

for command in pandoc pdflatex qpdf java; do
    command -v "${command}" >/dev/null \
        || die "${command} is required for R CMD check --as-cran; see harness/README.md"
done
java -version >/dev/null 2>&1 \
    || die "a working Java runtime is required for R CMD check --as-cran; see harness/README.md"

WORK="$(mktemp -d)"
rsync -a \
    --exclude .git \
    --exclude .github \
    --exclude harness \
    --exclude docs \
    --exclude "*.Rcheck" \
    "${PKG_SRC}/" "${WORK}/hdf5r/"
cd "${WORK}/hdf5r"

{
    echo "=== hdf5r check: ${NAME} ==="
    echo "=== R: $(R --version 2>&1 | sed -n '1p')"
    echo "=== HDF5: ${HDF5_VERSION:-system} ==="
    echo "=== started: $(date -u '+%Y-%m-%dT%H:%M:%SZ') ==="
    echo
} >> "${LOG}"

export _R_CHECK_CRAN_INCOMING_="false"

echo "run-check.sh: building package" | tee -a "${LOG}"
if ! R CMD build --no-build-vignettes . >> "${LOG}" 2>&1; then
    die "R CMD build failed"
fi

shopt -s nullglob
tarballs=(hdf5r_*.tar.gz)
[ "${#tarballs[@]}" -eq 1 ] \
    || die "expected one built package tarball, found ${#tarballs[@]}"
tarball="${tarballs[0]}"

echo "run-check.sh: checking ${tarball}" | tee -a "${LOG}"
check_rc=0
R CMD check --as-cran "${tarball}" >> "${LOG}" 2>&1 || check_rc=$?

check_log="hdf5r.Rcheck/00check.log"
if [ ! -f "${check_log}" ]; then
    echo "run-check.sh: 00check.log was not produced" >> "${LOG}"
    check_rc=1
else
    {
        echo
        echo "=== 00check.log (tail) ==="
        tail -n 50 "${check_log}"
    } >> "${LOG}"

    if grep -Eq '^Status:.*(ERROR|WARNING)' "${check_log}"; then
        check_rc=1
    fi
fi

if [ "${check_rc}" -eq 0 ]; then
    echo PASS > "${STATUS}"
else
    echo FAIL > "${STATUS}"
fi

echo "run-check.sh: ${NAME} -> $(cat "${STATUS}") (log: ${LOG})"
exit "${check_rc}"
