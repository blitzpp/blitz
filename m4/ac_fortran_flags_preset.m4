
AC_DEFUN([AC_FORTRAN_FLAGS_PRESET],[


dnl Set platform-specific fortran compilers and optimization settings

AC_SUBST(CXXFFLAGS)
AC_SUBST(CXXFCFLAG)
AC_SUBST(F77_OPTIMIZE_FLAGS)
AC_SUBST(FC_OPTIMIZE_FLAGS)
AC_SUBST(FORTLIBS)

AC_ARG_VAR(CXXFFLAGS,[C++ compiler flags to link Fortran 77 subroutines])
AC_ARG_VAR(CXXFCFLAG,[C++ compiler flags to link Fortran 90 subroutines])
AC_ARG_VAR(F77_OPTIMIZE_FLAGS,[Fortran 77 optimization flags])
AC_ARG_VAR(FC_OPTIMIZE_FLAGS,[Fortran 90 optimization flags])
AC_ARG_VAR(FORTLIBS,[Libraries to link Fortran 77/90 subroutines together with C++ code])

AC_MSG_CHECKING([whether using $F77 and $FC preset flags])
AC_ARG_ENABLE(fortran-flags-preset,
AS_HELP_STRING([--enable-fortran-flags-preset],
[Enable Fortran compiler flags preset @<:@default yes@:>@]),[],[enableval='yes'])


if test "$enableval" = yes ; then

	case "$target" in
	*aix*)
		case "$F77" in
		*xlf) dnl IBM Fortran compiler
			F77_OPTIMIZE_FLAGS="-O5 -qstrict -qstrict_induction -qnosave -qmaxmem=8192"
		;;
		esac
		case $FC in 
		*xlf90) dnl IBM F90 compiler
			FCFLAGS="-qsuffix=f=f90"
			FC_OPTIMIZE_FLAGS="-O5 -qstrict -qstrict_induction -qnosave -qmaxmem=8192"
			FORTLIBS="-lxlf90"
		;;
		esac
	;;
	*irix*)
		case "$F77" in
		*f77) dnl SGI Fortran compiler
  			F77_OPTIMIZE_FLAGS="-Ofast"
			CXXFFLAGS="-DBZ_FORTRAN_SYMBOLS_WITH_TRAILING_UNDERSCORES"
			FORTLIBS="-lfortran -lffio -lftn"
		;;
		esac
		case "$FC" in
 		*f90) dnl SGI F90 compiler
			FC_OPTIMIZE_FLAGS="-Ofast"
			CXXFCFLAG="-DBZ_FORTRAN_SYMBOLS_WITH_TRAILING_UNDERSCORES"
			FORTLIBS="-lfortran -lffio -lftn"
		;;
		esac
	;;
	*linux*)
		case "$F77" in
		g77) dnl GNU Fortran compiler
			FFLAGS="-fno-second-underscore"
			F77_OPTIMIZE_FLAGS="-O2 -funroll-loops"
			CXXFFLAGS="-DBZ_FORTRAN_SYMBOLS_WITH_TRAILING_UNDERSCORES"
			FORTLIBS="-lg2c"
		;;
		ifc) dnl Intel 7.1 Fortran compiler
			FCFLAGS=""
			FC_OPTIMIZE_FLAGS="-O3 -Zp16 -ip -pad -unroll -fno-alias -safe_cray_ptr"
			FORTLIBS="-lF90 -lIEPCF90 -lintrins $FORTLIBS"
		;;
		ifort) dnl Intel 8.0 Fortran compiler
			FCFLAGS=""
			FC_OPTIMIZE_FLAGS="-O3 -Zp16 -ip -pad -unroll -fno-alias -safe_cray_ptr"
			FORTLIBS="-lifport -lifcore $FORTLIBS"
		;;
		f77) dnl Absoft Fortran compiler
			FFLAGS="-B108 -f"
			F77_OPTIMIZE_FLAGS="-O2"
			CXXFFLAGS="-DBZ_FORTRAN_SYMBOLS_WITH_TRAILING_UNDERSCORES"
			FORTLIBS="-L$ABSOFT/lib -lfio -lU77 -lf77math"
		;;
		esac
		case "$FC" in
		ifc) dnl Intel 7.1 F90 compiler
			FCFLAGS="-FR"
			FC_OPTIMIZE_FLAGS="-O3 -Zp16 -ip -pad -unroll -fno-alias -safe_cray_ptr"
			FORTLIBS="-lF90 -lIEPCF90 -lintrins $FORTLIBS"
		;;
		ifort) dnl Intel 8.0 F90 compiler
			FCFLAGS="-FR"
			FC_OPTIMIZE_FLAGS="-O3 -Zp16 -ip -pad -unroll -fno-alias -safe_cray_ptr"
			FORTLIBS="-lifport -lifcore $FORTLIBS"
		;;
		f90) dnl Absoft F90 compiler
			FCFLAGS="-B108 -YEXT_NAMES=LCS"
			FC_OPTIMIZE_FLAGS="-O3"
			CXXFCFLAG="-DBZ_FORTRAN_SYMBOLS_WITH_TRAILING_UNDERSCORES"
			FORTLIBS="-L$ABSOFT/lib -lfio -lf90math -lU77 -lf77math"
		;;
		esac
	;;
	*solaris*)
		case "$F77" in
		f77) dnl Sun Fortran compiler
			F77_OPTIMIZE_FLAGS="-O3"
		;;
		esac
		case "$FC" in
		f90) dnl Sun F90 compiler
			FC_OPTIMIZE_FLAGS="-O3"
		;;
		esac
	;;
	*hp-hpux*)
		case "$F77" in
		f90) dnl HP Fortran compiler
			F77_OPTIMIZE_FLAGS="-O3"
		;;
		esac
		case "$FC" in
		f90) dnl HP F90 compiler
			FC_OPTIMIZE_FLAGS="-O3"
			FORTLIBS="-lc -lF90"
		;;
		esac
	;;
	*osf*)
		case "$F77" in
		f77) dnl Compaq Fortran compiler
			F77_OPTIMIZE_FLAGS="-O4 -tune host"
			FORTLIBS="-lUfor -lfor -lFutil"
		;;
		esac
		case "$FC" in
		f90) dnl Compaq F90 compiler
			FC_OPTIMIZE_FLAGS="-O4 -tune host"
			CXXFCFLAG="-DBZ_FORTRAN_SYMBOLS_WITH_TRAILING_UNDERSCORES"
			FORTLIBS="-lUfor -lfor -lFutil"
		;;
		esac
	;;
	alpha-cray-unicos)
		case "$F77" in
		fort77) dnl Cray Fortran compiler
			F77_OPTIMIZE_FLAGS="-O aggress -O 3 -O unroll2 -O pipeline3"
		;;
		esac
		case "$FC" in
		f90) dnl Cray F90 compiler
			FC_OPTIMIZE_FLAGS="-O 3 -O aggress -O unroll2 -O pipeline3"
			CXXFCFLAG="-DBZ_FORTRAN_SYMBOLS_CAPS"
		;;
		esac
	;;
	*) 
		ac_fortran_flags_preset=no
	;;
	esac

	AC_MSG_RESULT([yes])

else

	AC_MSG_RESULT([no])

fi 

if test "$ac_fortran_flags_preset" = no ; then 
	AC_MSG_NOTICE([ 

Blitz++ has not been tuned for this platform.  You may have trouble
building fortran benchmarks, and performance may be unexciting.

	])
fi

if [test ! x"$FC" = x]; then
	CXXFCFLAG="-DFORTRAN_90 $CXXFCFLAG"
fi
AM_CONDITIONAL(F90_COMPILER, [test ! x"$FC" = x])

])

