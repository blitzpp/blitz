dnl @synopsis AC_CXX_LIB_BLITZ([optional-string "required"])
dnl
dnl Check whether Blitz++ is installed.
dnl Blitz++ is available at http://sourceforge.net/projects/blitz
dnl
dnl   Set the path for Blitz++  with the option
dnl      --with-blitz[=DIR]
dnl   Blitz headers should be under DIR/includes
dnl   Blitz library should be under DIR/lib
dnl   Then try to compile and run a simple program with a Blitz Array
dnl   Optional argument `required' triggers an error if Blitz++ not installed
dnl 
dnl @version $Id$
dnl @author Patrick Guio <patrick.guio@matnat.uio.no>
dnl
AC_DEFUN([AC_MSG_ERROR_BLITZ],[
AC_MSG_ERROR([
$PACKAGE_STRING requires the Blitz++ template library
available at http://sourceforge.net/projects/blitz
When installed give the directory of installation with the option
  --with-blitz@<:@=DIR@:>@
])])


AC_DEFUN([AC_CXX_LIB_BLITZ],[

AC_ARG_WITH(blitz,
AS_HELP_STRING([--with-blitz@<:@=DIR@:>@],[Set the path for Blitz++]),
[],[withval='yes'])

if test "$1" = required -a "$withval" = no ; then
	AC_MSG_ERROR_BLITZ
fi

if test "$withval" != no ; then

	saveCPPFLAGS=$CPPFLAGS
	saveLDFLAGS=$LDFLAGS
	saveLIBS=$LIBS

	if test "$withval" != 'yes'; then
		CPPFLAGS="-I$withval/include"
		LDFLAGS="-L$withval/lib"
	fi
	LIBS="-lblitz"

	AC_CACHE_CHECK([whether Blitz++ is installed],ac_cxx_lib_blitz,
	[AC_LANG_SAVE
	AC_LANG_CPLUSPLUS
	AC_RUN_IFELSE(
	[AC_LANG_PROGRAM([[
#include <blitz/array.h>
]],[[
blitz::Array<int,1> x(10);
x = blitz::tensor::i;
	]])],[ac_cxx_lib_blitz=yes],[ac_cxx_lib_blitz=no])
	AC_LANG_RESTORE
	])

	CPPFLAGS=$saveCPPFLAGS
	LDFLAGS=$saveLDFLAGS
	LIBS=$saveLIBS

	if test "$ac_cxx_lib_blitz" = yes ; then
		if test "$withval" != yes ; then
			CPPFLAGS="-I$withval/include $CPPFLAGS"
			LDFLAGS="-L$withval/lib $LDFLAGS"
		fi
		LIBS="-lblitz $LIBS"
	else
		if test "$1" = required ; then
			AC_MSG_ERROR_BLITZ
		fi
	fi

fi

])




