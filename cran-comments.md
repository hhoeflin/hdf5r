## Submission

This release restores installation on the CRAN flavours that build against
HDF5 2.x, which currently fail with:

    Wrapper_auto_H5FDfamily.c:23:22: error: implicit declaration of function
    'H5FD_family_init'

HDF5 2.x removed four private driver-init symbols from its public headers. The
wrappers around them were unreachable from R and have been removed.

Once those symbols are gone, systems whose serial HDF5 build is named
`libhdf5_serial` (Debian, Ubuntu) reach the final link step and fail on the
generic `-lhdf5_hl -lhdf5` names that `configure` forced on top of what
`h5cc -show` reports. `configure` now only falls back to the generic names when
`h5cc` reports none.

It also fixes the linux-arm64 test failure, where `H5T_NATIVE_CHAR` resolves to
an unsigned type because plain `char` is unsigned on AArch64, and the
unprotected variable in `H5ToR_Post_RComplex()` reported by `rchk`.

## Test environments

* local macOS 15 (arm64), R 4.6.1, HDF5 2.1.1
* GitHub Actions: macOS, Windows, Ubuntu (R devel / release / oldrel-1)
* GitHub Actions: ubuntu-24.04-arm, to cover the AArch64 `char` signedness
* GitHub Actions: Debian unstable with HDF5 2.x

## R CMD check results

0 errors | 0 warnings | 0 notes

## Reverse dependencies

No reverse dependencies are affected by the source changes. One behavioural
change is documented in NEWS: `ls()` and the `list.*()` helpers now default to
`order = h5const$H5_ITER_INC` rather than `H5_ITER_NATIVE`. `H5_ITER_NATIVE`
leaves the order unspecified and changed from name order to creation order in
HDF5 2.x; the new default keeps the previous ordering on every HDF5 version.
