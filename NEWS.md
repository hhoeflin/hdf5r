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
