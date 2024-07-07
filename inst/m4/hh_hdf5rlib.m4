
#############################################################################
##
## Copyright 2016 Novartis Institutes for BioMedical Research Inc.
## Licensed under the Apache License, Version 2.0 (the "License");
## you may not use this file except in compliance with the License.
## You may obtain a copy of the License at
##
## http://www.apache.org/licenses/LICENSE-2.0
##
## Unless required by applicable law or agreed to in writing, software
## distributed under the License is distributed on an "AS IS" BASIS,
## WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
## See the License for the specific language governing permissions and
## limitations under the License.
##
#############################################################################

AC_DEFUN([HH_HDF5RLIB], [

AC_REQUIRE([AC_PROG_SED])
AC_REQUIRE([AC_PROG_AWK])
AC_REQUIRE([AC_PROG_GREP])

HDF5RLIB_INSTALLED=$(echo 'cat(suppressWarnings(require(hdf5rLib, quietly=TRUE, character.only=FALSE, warn.conflicts=FALSE)))' |\
"${R_HOME}/bin/R" --vanilla --slave)


if test "$HDF5RLIB_INSTALLED" != "TRUE"; then
   with_hdf5rLib="no"
else
   with_hdf5rLib="yes"
   ## get the relevant variables so that headers can be found and static library can be linked
   HDF5RLIB_LIBPATH=$(echo 'cat(hdf5rLib:::.pkgLibPath())' | "${R_HOME}/bin/R" --vanilla --slave)
   HDF5RLIB_INCLUDEPATH=$(echo 'cat(hdf5rLib:::.pkgIncludePath())' | "${R_HOME}/bin/R" --vanilla --slave)

   HDF5_MAJOR_VERSION=$(echo 'cat(hdf5rLib:::.pkgMajorVersion())' | "${R_HOME}/bin/R" --vanilla --slave)
   HDF5_MINOR_VERSION=$(echo 'cat(hdf5rLib:::.pkgMinorVersion())' | "${R_HOME}/bin/R" --vanilla --slave)

   HDF5_LIBS='-L"'${HDF5RLIB_LIBPATH}'" -lhdf5_hl-static -lhdf5-static -lz -lm'
   HDF5_CPPFLAGS='-I'"${HDF5RLIB_INCLUDEPATH}"' -DWINDOWS'

   AC_SUBST([HDF5_LIBS])
   AC_SUBST([HDF5_CPPFLAGS])
   AC_SUBST([HDF5_MAJOR_VERSION])
   AC_SUBST([HDF5_MINOR_VERSION])
fi



])
