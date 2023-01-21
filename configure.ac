AC_INIT([hdf5r],[0.1.0],[hhoeflin@gmail.com])

dnl Grab that macro that checks for HDF5 availability
m4_include([inst/m4/ax_lib_hdf5.m4])
m4_include([inst/m4/ax_compare_version.m4])
m4_include([inst/m4/hh_hdf5rlib.m4])


: ${R_HOME=`R RHOME`}
if test -z "${R_HOME}"; then
  echo "could not determine R_HOME"
  exit 1
fi
if test -z "${CC}"; then
  CC=`"${R_HOME}/bin/R" CMD config CC`
fi
if test -z "${CFLAGS}"; then
  CFLAGS=`"${R_HOME}/bin/R" CMD config CFLAGS`
fi
if test -z "${CPPFLAGS}"; then
  CPPFLAGS=`"${R_HOME}/bin/R" CMD config CPPFLAGS`
fi

AX_LIB_HDF5()

if test "$with_hdf5" = "yes"; then
AC_MSG_RESULT([Found hdf5 with version: $HDF5_VERSION])
AX_COMPARE_VERSION([$HDF5_VERSION], [ge], [1.8.13], [hdf5_version_sufficient="yes"], AC_MSG_ERROR([The version of hdf5 installed on your system is not sufficient. Please ensure that at least version 1.8.13 is installed]))
else
  AC_MSG_ERROR([hdf5 does not seem to be installed on your platform.
  Please install the hdf5 library.
  The required HDF5 library files can be installed as follows:
      - Debian-based (e.g. Debian >= 8.0, Ubuntu >= 15.04): 'sudo apt-get install libhdf5-dev'
        - Old Debian-based (e.g Debian < 8.0, Ubuntu < 15.04): Install from source (see INSTALL)
        - OS X using Homebrew: 'brew install hdf5'
        - RPM-based (e.g Fedora): 'sudo yum install hdf5-devel'])
fi


if test "$hdf5_version_sufficient" = "yes"; then
  AX_COMPARE_VERSION(
	[$HDF5_VERSION],
	[ge],
	[1.8.13],
	[HDF5_VERSION_USE="1_8_14"])

  AX_COMPARE_VERSION(
	[$HDF5_VERSION],
	[ge],
	[1.8.14],
	[HDF5_VERSION_USE="1_8_14"])

  AX_COMPARE_VERSION(
	[$HDF5_VERSION],
	[ge],
	[1.8.16],
	[HDF5_VERSION_USE="1_8_16"])

  AX_COMPARE_VERSION(
	[$HDF5_VERSION],
	[ge],
	[1.10.0],
	[HDF5_VERSION_USE="1_10_0"])

  AX_COMPARE_VERSION(
	[$HDF5_VERSION],
	[ge],
	[1.10.2],
	[HDF5_VERSION_USE="1_10_2"])

  AX_COMPARE_VERSION(
	[$HDF5_VERSION],
	[ge],
	[1.10.3],
	[HDF5_VERSION_USE="1_10_3"])

  AX_COMPARE_VERSION(
	[$HDF5_VERSION],
	[ge],
	[1.10.6],
	[HDF5_VERSION_USE="1_10_3" && HDF5_USE_PATCH="1.10.6"])

  AX_COMPARE_VERSION(
	[$HDF5_VERSION],
	[ge],
	[1.12.0],
	[HDF5_VERSION_USE="1_12_0" && HDF5_USE_PATCH=""])

  AX_COMPARE_VERSION(
	[$HDF5_VERSION],
	[ge],
	[1.12.0],
	[HDF5_API_VERS_USE="-DH5_USE_110_API"],
    [HDF5_API_VERS_USE=""])
fi

AC_SUBST(HDF5_VERSION_USE)
AC_SUBST(HDF5_API_VERS_USE)
AC_SUBST(DEFINE_H5FREE_MEMORY)
AC_SUBST(HDF5_USE_PATCH)


dnl Now find the compiler and compiler flags to use
: ${R_HOME=`R RHOME`}
if test -z "${R_HOME}"; then
  echo "could not determine R_HOME"
  exit 1
fi

####################
# Deterine HDF5_LIBS
####################
dnl prefer ggrep if installed
AC_CHECK_PROG(GREP,ggrep,`which ggrep`, `which grep`)
dnl check if $GREP supports option -o
AC_MSG_CHECKING([whether ${GREP} accepts -o])
if `echo '' | ${GREP} -o '' >/dev/null 2>&1`
then
  AC_MSG_RESULT([yes])
else
  AC_MSG_RESULT([no])
  AC_MSG_ERROR([${GREP} does not support option -o])
fi
[
HDF5_LIBS=`${H5CC} -show | ${GREP} -o " \-[lL][^[:space:]]\+" | tr "\n" " "`
]
dnl Fix for newer Debian versions
HDF5_LIBS="${HDF5_LIBS} -L. -lhdf5_hl -lhdf5 -lz -lm"

#########################
# Determine HDF5_CPPFLAGS
#########################
dnl prefer ggrep if installed
AC_CHECK_PROG(GREP,ggrep,`which ggrep`, `which grep`)

dnl check if $GREP supports option -o
AC_MSG_CHECKING([whether ${GREP} accepts -o])
if `echo '' | ${GREP} -o '' >/dev/null 2>&1`
then
  AC_MSG_RESULT([yes])
else
  AC_MSG_RESULT([no])
  AC_MSG_ERROR([${GREP} does not support option -o])
fi

echo 'int main() { return; }' > myconftest.c
[
HDF5_CPPFLAGS=`${H5CC} -show -c myconftest.c | ${GREP} -o "\-I[^[:space:]]\+" | tr "\n" " "`
]
rm -f myconftest.c


dnl dummy substitute HDF5R_CFLAGS
HDF5_CFLAGS=""

dnl substitute CFLAGS, CPPFLAGS and LIBS
AC_MSG_RESULT([Using variables:])
AC_MSG_RESULT([HDF5_LIBS=${HDF5_LIBS}])
AC_MSG_RESULT([HDF5_CFLAGS=${HDF5_CFLAGS}])
AC_MSG_RESULT([HDF5_CPPFLAGS=${HDF5_CPPFLAGS}])
AC_SUBST(HDF5_CFLAGS)
AC_SUBST(HDF5_CPPFLAGS)
AC_SUBST(HDF5_LIBS)
dnl and do subsitution in the src/Makevars.in
AC_CONFIG_FILES([src/Makevars])
AC_OUTPUT
