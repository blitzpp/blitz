
AC_DEFUN([AC_FORTRAN_FLAGS_PRESET],[


dnl Set platform-specific fortran compilers and optimization settings

AC_SUBST(CXXFFLAGS)
AC_SUBST(CXXFCFLAG)
AC_SUBST(F77_OPTIMIZE_FLAGS)
AC_SUBST(FC_OPTIMIZE_FLAGS)

AC_ARG_VAR(CXXFFLAGS,[C++ compiler flags to link Fortran 77 subroutines])
AC_ARG_VAR(CXXFCFLAG,[C++ compiler flags to link Fortran 90 subroutines])
AC_ARG_VAR(F77_OPTIMIZE_FLAGS,[Fortran 77 optimization flags])
AC_ARG_VAR(FC_OPTIMIZE_FLAGS,[Fortran 90 optimization flags])

AC_MSG_CHECKING([whether using Fortran preset flags])
AC_ARG_ENABLE(fortran-flags-preset,
AS_HELP_STRING([--enable-fortran-flags-preset],
[Enable Fortran compiler flags preset @<:@default yes@:>@]),[],[enableval='yes'])


if test "$enableval" = yes ; then

	AC_MSG_RESULT([yes])

	case "$target" in
	*aix*)
		case "$F77" in
		*xlf*)  dnl IBM Fortran compiler
			FFLAGS=""
			F77_OPTIMIZE_FLAGS="-O5 -qstrict -qstrict_induction -qnosave -qmaxmem=8192"
		;;
		g77)    dnl GNU Fortran compiler
			FFLAGS="-fno-second-underscore"
			F77_OPTIMIZE_FLAGS="-O2 -funroll-loops"
			CXXFFLAGS="-DBZ_FORTRAN_SYMBOLS_WITH_TRAILING_UNDERSCORES"
		;;
		esac
	;;
	*irix*)
		case "$F77" in
		*f77*)  dnl SGI Fortran compiler
			FFLAGS=""
  			F77_OPTIMIZE_FLAGS="-Ofast"
			CXXFFLAGS="-DBZ_FORTRAN_SYMBOLS_WITH_TRAILING_UNDERSCORES"
		;;
		g77)    dnl GNU Fortran compiler
			FFLAGS="-fno-second-underscore"
			F77_OPTIMIZE_FLAGS="-O2 -funroll-loops"
			CXXFFLAGS="-DBZ_FORTRAN_SYMBOLS_WITH_TRAILING_UNDERSCORES"
		;;
		esac
	;;
	*linux*)
		case "$F77" in
		gfortran) dnl GNU Fortran 95 compiler
			FFLAGS="-fno-second-underscore"
			F77_OPTIMIZE_FLAGS="-O2 -funroll-loops"
			CXXFFLAGS="-DBZ_FORTRAN_SYMBOLS_WITH_TRAILING_UNDERSCORES"
		;;
		g77)    dnl GNU Fortran compiler
			FFLAGS="-fno-second-underscore"
			F77_OPTIMIZE_FLAGS="-O2 -funroll-loops"
			CXXFFLAGS="-DBZ_FORTRAN_SYMBOLS_WITH_TRAILING_UNDERSCORES"
		;;
		ifc)    dnl Intel 7.1 Fortran compiler
			FFLAGS=""
			F77_OPTIMIZE_FLAGS="-O3 -Zp16 -ip -pad -unroll -fno-alias -safe_cray_ptr"
		;;
		ifort)  dnl Intel 8.0 Fortran compiler
			FFLAGS=""
			F77_OPTIMIZE_FLAGS="-O3 -Zp16 -ip -pad -unroll -fno-alias -safe_cray_ptr"
		;;
		pgf77)  dnl PGI Fortran compiler
			FFLAGS=""
			F77_OPTIMIZE_FLAGS="-fastsse -O3 -Minline -Minfo"
			CXXFFLAGS="-DBZ_FORTRAN_SYMBOLS_WITH_TRAILING_UNDERSCORES"
		;;
		f77)
		    if test ".$G77" == .yes; then
			dnl GNU Fortran compiler
			FFLAGS="-fno-second-underscore"
			F77_OPTIMIZE_FLAGS="-O2 -funroll-loops"
			CXXFFLAGS="-DBZ_FORTRAN_SYMBOLS_WITH_TRAILING_UNDERSCORES"
		    else
			dnl Absoft Fortran compiler
			FFLAGS="-B108 -f"
			F77_OPTIMIZE_FLAGS="-O2"
			CXXFFLAGS="-DBZ_FORTRAN_SYMBOLS_WITH_TRAILING_UNDERSCORES"
		    fi
		;;
		esac
	;;
	*solaris*)
		case "$F77" in
		f77)    dnl Sun Fortran compiler
			FFLAGS=""
			F77_OPTIMIZE_FLAGS="-O3"
		;;
		g77)    dnl GNU Fortran compiler
			FFLAGS="-fno-second-underscore"
			F77_OPTIMIZE_FLAGS="-O2 -funroll-loops"
			CXXFFLAGS="-DBZ_FORTRAN_SYMBOLS_WITH_TRAILING_UNDERSCORES"
		;;
		esac
	;;
	*hp-hpux*)
		case "$F77" in
		f90)    dnl HP Fortran compiler
			FFLAGS=""
			F77_OPTIMIZE_FLAGS="-O3"
		;;
		g77)    dnl GNU Fortran compiler
			FFLAGS="-fno-second-underscore"
			F77_OPTIMIZE_FLAGS="-O2 -funroll-loops"
			CXXFFLAGS="-DBZ_FORTRAN_SYMBOLS_WITH_TRAILING_UNDERSCORES"
		;;
		esac
	;;
	*osf*)
		case "$F77" in
		f77)    dnl Compaq Fortran compiler
			FFLAGS=""
			F77_OPTIMIZE_FLAGS="-O4 -tune host"
		;;
		g77)    dnl GNU Fortran compiler
			FFLAGS="-fno-second-underscore"
			F77_OPTIMIZE_FLAGS="-O2 -funroll-loops"
			CXXFFLAGS="-DBZ_FORTRAN_SYMBOLS_WITH_TRAILING_UNDERSCORES"
		;;
		esac
	;;
	alpha-cray-unicos)
		case "$F77" in
		fort77) dnl Cray Fortran compiler
			FFLAGS=""
			F77_OPTIMIZE_FLAGS="-O aggress -O 3 -O unroll2 -O pipeline3"
		;;
		esac
	;;
	*) 
		ac_fortran_flags_preset=no
	;;
	esac

	if test -n "$FC"; then
	case "$target" in
	*aix*)
		case "$FC" in 
		*xlf90*) dnl IBM F90 compiler
			 FCFLAGS=""
			 FC_OPTIMIZE_FLAGS="-O5 -qstrict -qstrict_induction -qnosave -qmaxmem=8192"
		;;
		esac
	;;
	*irix*)
		case "$FC" in
 		*f90*)  dnl SGI F90 compiler
			FCFLAGS=""
			FC_OPTIMIZE_FLAGS="-Ofast"
			CXXFCFLAG="-DBZ_FORTRAN_SYMBOLS_WITH_TRAILING_UNDERSCORES"
		;;
		esac
	;;
	*linux*)
		case "$FC" in
		gfortran) dnl GNU Fortran 95 compiler
			FCFLAGS="-fno-second-underscore"
			FC_OPTIMIZE_FLAGS="-O2 -funroll-loops"
			CXXFCFLAG="-DBZ_FORTRAN_SYMBOLS_WITH_TRAILING_UNDERSCORES"
		;;
		g95)    dnl G95 compiler
			FCFLAGS="-fno-second-underscore"
			FC_OPTIMIZE_FLAGS="-O2 -funroll-loops"
			CXXFCFLAG="-DBZ_FORTRAN_SYMBOLS_WITH_TRAILING_UNDERSCORES"
		;;
		ifc)    dnl Intel 7.1 F90 compiler
			FCFLAGS=""
			FC_OPTIMIZE_FLAGS="-O3 -Zp16 -ip -pad -unroll -fno-alias -safe_cray_ptr"
		;;
		ifort)  dnl Intel 8.0 F90 compiler
			FCFLAGS=""
			FC_OPTIMIZE_FLAGS="-O3 -Zp16 -ip -pad -unroll -fno-alias -safe_cray_ptr"
		;;
		pgf90)  dnl PGI F90 compiler
			FCFLAGS=""
			FC_OPTIMIZE_FLAGS="-fastsse -O3 -Minline -Minfo"
			CXXFCFLAG="-DBZ_FORTRAN_SYMBOLS_WITH_TRAILING_UNDERSCORES"
		;;
		f90)    dnl Absoft F90 compiler
			FCFLAGS="-B108 -YEXT_NAMES=LCS"
			FC_OPTIMIZE_FLAGS="-O3"
			CXXFCFLAG="-DBZ_FORTRAN_SYMBOLS_WITH_TRAILING_UNDERSCORES"
		;;
		esac
	;;
	*solaris*)
		case "$FC" in
		f90)    dnl Sun F90 compiler
			FCFLAGS=""
			FC_OPTIMIZE_FLAGS="-O3"
		;;
		esac
	;;
	*hp-hpux*)
		case "$FC" in
		f90)    dnl HP F90 compiler
			FCFLAGS=""
			FC_OPTIMIZE_FLAGS="-O3"
		;;
		esac
	;;
	*osf*)
		case "$FC" in
		f90)    dnl Compaq F90 compiler
			FCFLAGS=""
			FC_OPTIMIZE_FLAGS="-O4 -tune host"
			CXXFCFLAG="-DBZ_FORTRAN_SYMBOLS_WITH_TRAILING_UNDERSCORES"
		;;
		esac
	;;
	alpha-cray-unicos)
		case "$FC" in
		f90)    dnl Cray F90 compiler
			FCFLAGS=""
			FC_OPTIMIZE_FLAGS="-O 3 -O aggress -O unroll2 -O pipeline3"
			CXXFCFLAG="-DBZ_FORTRAN_SYMBOLS_CAPS"
		;;
		esac
	;;
	*) 
		ac_fortran_flags_preset=no
	;;
	esac
	fi

else

	AC_MSG_RESULT([no])

fi 

if test "$ac_fortran_flags_preset" = no ; then 
	AC_MSG_NOTICE([ 

Blitz++ has not been tuned for this platform.  You may have trouble
building fortran benchmarks, and performance may be unexciting.

	])
fi

if test -n "$FC"; then
	CXXFCFLAG="-DFORTRAN_90 $CXXFCFLAG"
fi
AM_CONDITIONAL(F90_COMPILER, [test -n "$FC"])

])

