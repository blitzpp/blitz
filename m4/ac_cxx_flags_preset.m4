
dnl Compiler flags preset
AC_DEFUN([AC_CXX_FLAGS_PRESET],[

dnl Declare variables which we want substituted in the Makefile.in's

dnl AC_SUBST(CXXFLAGS)
AC_SUBST(CXX_OPTIMIZE_FLAGS)
AC_SUBST(CXX_DEBUG_FLAGS)
AC_SUBST(CXX_PROFIL_FLAGS)
AC_SUBST(CXX_LIBS)
AC_SUBST(AR)
AC_SUBST(AR_FLAGS)
AC_SUBST(LDFLAGS)
AC_SUBST(RANLIB)

dnl Set default values
AR_FLAGS="-cru"
LDFLAGS=


AC_MSG_CHECKING([whether using $CXX preset flags])
AC_ARG_ENABLE(cxx-flags-preset,
AS_HELP_STRING([--enable-cxx-flags-preset],
[Enable C++ compiler flags preset @<:@default yes@:>@]),[],[enableval='yes'])

if test "$enableval" = yes ; then

	ac_cxx_flags_preset=yes

	case "$CXX" in
	*KCC) dnl KAI C++  http://www.kai.com/
		CXX_VENDOR="KAI"
		CXXFLAGS="--restrict"
		CXX_OPTIMIZE_FLAGS="+K3"
		CXX_DEBUG_FLAGS="+K0 -g -DBZ_DEBUG"
		AR="$CXX"
		AR_FLAGS="-o"
		case "$target" in
		*sgi*) dnl SGI C backend compiler
			CXX_OPTIMIZE_FLAGS="$CXX_OPTIMIZE_FLAGS --backend -Ofast"
		;;
		*ibm*) dnl IBM xlC backend compiler
			CXX_OPTIMIZE_FLAGS="$CXX_OPTIMIZE_FLAGS -O5 --backend -qstrict --backend -qstrict_induction"
		;;
		*) dnl other C backend compiler
			CXX_OPTIMIZE_FLAGS="$CXX_OPTIMIZE_FLAGS -O"
		;;
		esac
	;;
	cxx) dnl Compaq C++  http://www.compaq.com/
		CXX_VENDOR="Compaq"
		CXX_V=`cxx -V`
		cxx_version=`expr "$CXX_V" : '.*\(@<:@0-9@:>@\)\..*'`
		cxx_release=`expr "$CXX_V" : '.*@<:@0-9@:>@\.\(@<:@0-9@:>@\).*'`
		if test $cxx_version -eq "6" -a $cxx_release -lt "3" ; then
			CXXFLAGS="-std ansi -D__USE_STD_IOSTREAM -DBZ_ENABLE_XOPEN_SOURCE -ieee -model ansi -accept restrict_keyword -nousing_std"
		else
			CXXFLAGS="-std ansi -D__USE_STD_IOSTREAM -DBZ_ENABLE_XOPEN_SOURCE -D_OSF_SOURCE -ieee -model ansi -accept restrict_keyword -nousing_std"
		fi
		CXX_OPTIMIZE_FLAGS="-fast -inline speed -nocleanup"
		CXX_DEBUG_FLAGS="-g -msg_display_tag -DBZ_DEBUG"
		CXX_PROFIL_FLAGS="-pg -g1"
		AR="ar"
		AR_FLAGS="-rv"
		RANLIB="ar ts"
	;;
	g++) dnl GNU C++  http://gcc.gnu.org/
		CXX_VENDOR="GNU" 
		GCC_V=`g++ --version`
		gcc_version=`expr "$GCC_V" : '.* \(@<:@0-9@:>@\)\..*'`
		gcc_release=`expr "$GCC_V" : '.* @<:@0-9@:>@\.\(@<:@0-9@:>@\).*'`
		if test $gcc_version -lt "3" ; then
			CXXFLAGS="-ftemplate-depth-40"
			CXX_OPTIMIZE_FLAGS="-O2 -funroll-loops -fstrict-aliasing -fno-gcse"
		else
			CXXFLAGS=""
			CXX_OPTIMIZE_FLAGS="-O3 -funroll-loops -fomit-frame-pointer -ffast-math"
		fi
		CXX_DEBUG_FLAGS="-g -DBZ_DEBUG"
		CXX_PROFIL_FLAGS="-pg"
	;;
	aCC) dnl HP aCC http://www.hp.com/go/c++
		CXX_VENDOR="HP"
		CXXFLAGS="-AA"
		CXX_OPTIMIZE_FLAGS="+O2"
		CXX_DEBUG_FLAGS="-g -DBZ_DEBUG"
		CXX_PROFIL_FLAGS="+pal"
	;;
	icpc|icc) dnl Intel icc http://www.intel.com/
		CXX_VENDOR="Intel"
		CXXFLAGS="-strict_ansi"
		CXX_OPTIMIZE_FLAGS="-O3 -Zp16 -ip -ansi_alias"
		CXX_DEBUG_FLAGS="-g -O0 -C -DBZ_DEBUG"
		CXX_PROFIL_FLAGS="-p"
	;;
	xlc++*) dnl IBM C++ compiler for Darwin
		CXX_VENDOR="IBM"
		CXXFLAGS="-qrtti -D__APPLE"
		CXX_OPTIMIZE_FLAGS="-O5 -qstrict -qstrict_induction -qmaxmem=8192 -qansialias"
		CXX_DEBUG_FLAGS="-g -DBZ_DEBUG"
		CXX_PROFIL_FLAGS="-p"
	;;      
	*xlC*) dnl IBM Visual Age C++   http://www.ibm.com/
		CXX_VENDOR="IBM"
		CXXFLAGS="-qrtti=all -D__IBM"
		CXX_OPTIMIZE_FLAGS="-O5 -qstrict -qstrict_induction -qmaxmem=8192 -qansialias"
		CXX_DEBUG_FLAGS="-g -DBZ_DEBUG"
		CXX_PROFIL_FLAGS="-p"
	;;      
	FCC) dnl Fujitsu C++
		CXX_VENDOR="Fujitsu"
		CXXFLAGS="-D__FUJITSU"
		CXX_OPTIMIZE_FLAGS="-K fast"
		CXX_DEBUG_FLAGS="-g -DBZ_DEBUG"
	;;
	pgCC) dnl Portland Group   http://www.pgroup.com
		CXX_VENDOR="PGI"
		CXXFLAGS=""
		CXX_OPTIMIZE_FLAGS="-O4 -Mnoframe -Mnodepchk -Minline=levels:25"
		CXX_DEBUG_FLAGS="-g -O0 -DBZ_DEBUG"
	;;
	*CC*) 
		case "$target" in
		*sgi*) dnl SGI C++  http://www.sgi.com
			CXX_VENDOR="SGI"
			CXXFLAGS="-LANG:std -LANG:restrict -no_auto_include"
			CXX_OPTIMIZE_FLAGS="-O3 -IPA -OPT:Olimit=0:alias=typed:swp=ON"
			CXX_DEBUG_FLAGS="-g -DBZ_DEBUG"
			AR="$CXX"
			AR_FLAGS="-ar -o"
		;;
		*cray*) dnl Cray C++
			CXX_VENDOR="Cray"
			CXXFLAGS="-h instantiate=used"
			CXX_OPTIMIZE_FLAGS="-O3 -hpipeline3 -hunroll -haggress -hscalar2"
			CXX_DEBUG_FLAGS="-g -DBZ_DEBUG"
		;;
		esac
	;;
	*) 
		ac_cxx_flags_preset=no
	;;
	esac
	AC_MSG_RESULT([yes])
else
	AC_MSG_RESULT([no])
fi

if test "$ac_cxx_flags_preset" = yes ; then
	if test "$CXX_VENDOR" = GNU ; then
		AC_MSG_NOTICE([Setting compiler flags for $CXX_VENDOR $CXX (wahoo!)])
	else
		AC_MSG_NOTICE([Setting compiler flags for $CXX_VENDOR $CXX])
	fi
else

	AC_MSG_NOTICE([No flags preset found for $CXX])
fi

])


