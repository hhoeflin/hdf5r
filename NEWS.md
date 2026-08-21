# hdf5r 1.3.14

- Fixed installation against 'HDF5' 2.x. The private driver-init symbols
  `H5FD_family_init()`, `H5FD_log_init()`, `H5FD_sec2_init()` and
  `H5FD_stdio_init()` were removed from the public 'HDF5' headers, which broke
  compilation on every platform building against 'HDF5' 2.x. The `R` wrappers
  around them were never reachable from `R` and have been removed.
- Fixed `H5T_ENUM` for enumerations containing negative values on platforms
  where plain `char` is unsigned, such as `AArch64` `Linux`. Such enumerations
  previously failed with a `value redefinition` error from 'HDF5'.
- `ls()`, and therefore `list.datasets()`, `list.groups()` and
  `list.objects()`, now default to `order = h5const$H5_ITER_INC` instead of
  `h5const$H5_ITER_NATIVE`. `H5_ITER_NATIVE` leaves the order unspecified; it
  came out in name order up to 'HDF5' 1.x but is creation order in 'HDF5' 2.x.
  The new default keeps the listing in name order on every 'HDF5' version and
  makes it agree with `names()`. Pass `order = h5const$H5_ITER_NATIVE`
  explicitly to get the previous behaviour.
- Fixed the final link step on platforms whose 'HDF5' serial build is named
  `libhdf5_serial` (such as `Debian` and `Ubuntu` building against 'HDF5' 2.x).
  `configure` now keeps the `-lhdf5*` libraries reported by `h5cc -show` and
  only falls back to the generic `-lhdf5_hl -lhdf5`, which do not exist there,
  when `h5cc` reports no 'HDF5' library itself.
- Fixed unprotected variables in `H5ToR_Post_RComplex()` and `guess_nelem()`
  reported by `rchk`.
- The `R6` class methods are now documented with ordinary `roxygen2` comments
  instead of the experimental in-body string literals that `roxygen2` 8 no
  longer supports, so the manual pages can be regenerated again.
- Removed `formatR` from `Suggests`; it is no longer used.
- The package is now checked and its website built by `GitHub Actions`,
  including jobs for `AArch64` `Linux` and for 'HDF5' 2.x, the two platforms
  behind the failures fixed in this release.

# hdf5r 1.3.12

- Fix compilation warning #232.

# hdf5r 1.3.11

- Fixes a bug, where an HDF5 array of length 0 is returned as NULL instead of an appropriate vector of length 0
- Fixes #223, where an incompatible pointer type occurs during compilation.

# hdf5r 1.3.10

- Fixed warnings related to printf in convert.c on M1Mac
- Fixed broken links to HDF5 docs
- Conform to RTools (PR #218)

# hdf5r 1.3.9

- Fixed issues with string formatting

# hdf5r 1.3.8

- Fixed issue in configue.ac that lead to failing builds.

# hdf5r 1.3.7

- Patched source code for hdf5r 1.10.6 and up

# hdf5r 1.3.6

- Adapted as.charater.factor_ext to be compatible with future changes in R. See issue #190

# hdf5r 1.3.5

- Change AC_HAVE_LIBRARY in inst/m4/ax_lib_hdf5.m4 to squash autoreconf complaint

# hdf5r 1.3.4

- Added installation for MacOS (PR #179 by @dipterix)
- Added szip fix (PR #180 by @jeroen)

# hdf5r 1.3.3

- Bugfix for failing test related to 64-bit support

# hdf5r 1.3.2

- Add support for HDF5 1.12.0 release

# hdf5r 1.3.1

- Add missing formatR dependency to Suggests entry
- Fix bug of multiple inclusion of defined variable in C code that causes error with new gcc version

# hdf5r 1.3.0

- Fixes bug #130. Errors from UBSAN-clang UBSAN-gcc
- Upgrades the windows version of HDF5 to 1.8.16 and ensures compatibility with RTools 4.0

# hdf5r 1.2.0

- Fixes bug #123: inconsistent subsetting, where certain subsets (usually short and one-dimensional) were
  returned incorrectly (offset by 1)

# hdf5r 1.1.1

- Fixes some potential problematic places in code by RCHK
- Update the links to the documentation

# hdf5r 1.0.1

- Updated package to work with version 1.10.2 and 1.10.3 of HDF5
- Fixed issue #84, adding full.names argument in h5-wrapper to list.groups; also added test
- Fixed issue #82, causing the "ls" method to hang for some large datasets;
  this is caused by H5Oget_info being slow
  for such datasets; using the deprecated H5Aget_num_attrs instead where needed

# hdfr 1.0.0

- First release of the hdf5r package
