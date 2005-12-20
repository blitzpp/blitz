dnl @synopsis AC_CHECK_BLITZ([ACTION-IF-FOUND], [ACTION-IF-NOT-FOUND])
dnl
dnl Check whether Blitz++ is installed.
dnl Blitz++ is available at http://sourceforge.net/projects/blitz
dnl
dnl   Set the path for Blitz++  with the option
dnl      --with-blitz[=DIR] | --with-blitz=INCDIR,LIBDIR
dnl 
dnl   Blitz headers should be under DIR/include or INCDIR
dnl   Blitz library should be under DIR/lib or LIBDIR
dnl  
dnl Define and set shell variable ac_cxx_lib_blitz to 'yes' or 'no'
dnl Substitute variables BLITZ_CPPFLAGS, BLITZ_LDFLAGS, BLITZ_LIBS
dnl Define macro HAVE_BLITZ
dnl 
dnl @author Patrick Guio <patrick.guio@matnat.uio.no>
dnl

AC_DEFUN([AC_CHECK_BLITZ],[


AC_ARG_WITH(blitz,
AS_HELP_STRING([--with-blitz@<:@=DIR@:>@], 
               [Set the path for Blitz++ (DIR or INCDIR,LIBDIR)]),
            [dnl action-if-given 
             ],
            [dnl action-if-not-given default is yes
             withval='yes'])

if test "$withval" != no ; then

  saveCPPFLAGS=$CPPFLAGS
  saveLDFLAGS=$LDFLAGS
  saveLIBS=$LIBS

  case "$withval" in
	  *,*)
		  blitz_incdir="`echo $withval | cut -f1 -d,`"
			blitz_libdir="`echo $withval | cut -f2 -d, -s`"
			;;
		*)
		  if test -n "$withval" -a "$withval" != yes ; then
			  blitz_incdir="$withval/include"
				blitz_libdir="$withval/lib"
			fi
			;;
	esac

  if test -n "$blitz_incdir"; then CPPFLAGS="-I$blitz_incdir"; fi
  if test -n "$blitz_libdir"; then LDFLAGS="-L$blitz_libdir" ; fi
	LIBS="-lblitz"

	AC_CACHE_CHECK([whether Blitz++ is installed],[ac_cxx_lib_blitz],
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
		AC_DEFINE([HAVE_BLITZ], [1],[Define Blitz support])
		if test -n "$blitz_incdir"; then BLITZ_CPPFLAGS="-I$blitz_incdir"; fi
		if test -n "$blitz_libdir"; then BLITZ_LDFLAGS="-L$blitz_libdir" ; fi
		BLITZ_LIBS="-lblitz"
	fi

else dnl $withval = no

  ac_cxx_lib_blitz='no' 

fi

AC_SUBST(BLITZ_CPPFLAGS)
AC_SUBST(BLITZ_LDFLAGS)
AC_SUBST(BLITZ_LIBS)

AS_IF([test "$ac_cxx_lib_blitz" = no], [$2], [$1])

])

AC_DEFUN([AC_MSG_ERROR_BLITZ],[
AC_MSG_ERROR([
$PACKAGE_STRING requires the Blitz++ template library
available at http://sourceforge.net/projects/blitz
])])

