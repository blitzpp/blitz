
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
	KCC) dnl KAI C++  http://www.kai.com/
		CXX_VENDOR="KAI"
  	CXXFLAGS="--restrict --strict_warnings --one_instantiation_per_object"
  	CXX_OPTIMIZE_FLAGS="+K3 -O3"
  	CXX_DEBUG_FLAGS="-g +K0 -DBZ_DEBUG"
  	AR="KCC"
  	AR_FLAGS="-o"
	;;
	CC) 
		case "$target" in
		*sgi*) dnl SGI C++  http://www.sgi.com
			CXX_VENDOR="SGI"
			CXXFLAGS="-LANG:std -LANG:restrict -no_auto_include"
dnl			CXX_OPTIMIZE_FLAGS="-O3"
			CXX_OPTIMIZE_FLAGS="-IPA -mips4 -Ofast=ip35"
			CXX_DEBUG_FLAGS="-g -DBZ_DEBUG"
			LDFLAGS="-lCio"
		;;
		*cray*) dnl Cray C++
			CXX_VENDOR="Cray"
			CXXFLAGS="-h instantiate=used"
			CXX_OPTIMIZE_FLAGS="-O3 -hpipeline3 -hunroll -haggress -hscalar2"
			CXX_DEBUG_FLAGS="-g -DBZ_DEBUG"
		;;
		esac
	;;
	cxx) dnl DEC C++  http://www.digital.com/
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
			CXX_OPTIMIZE_FLAGS="-O2 -funroll-loops"
		fi
		CXX_DEBUG_FLAGS="-g -DBZ_DEBUG"
		CXX_PROFIL_FLAGS="-pg"
	;;
	aCC) dnl aCC http://www.hp.com/go/c++
		CXX_VENDOR="HP"
		CXXFLAGS="-AA"
		CXX_OPTIMIZE_FLAGS="+O2"
		CXX_DEBUG_FLAGS="-g -DBZ_DEBUG"
		CXX_PROFIL_FLAGS="+pal"
	;;
	icc) dnl icc http://www.intel.com/
		CXX_VENDOR="Intel"
		CXXFLAGS=""
		CXX_OPTIMIZE_FLAGS="-O2"
		CXX_DEBUG_FLAGS="-g -O0 -DBZ_DEBUG"
		CXX_PROFIL_FLAGS="-p"
	;;
	xlC) dnl IBM Visual Age C++   http://www.ibm.com/
		CXX_VENDOR="IBM Visual Age"
		CXXFLAGS="-qrtti=all"
dnl		CXX_OPTIMIZE_FLAGS="-O3 -qstrict -Q -qansialias"
		CXX_OPTIMIZE_FLAGS="-O3 -qmaxmem=-1 -qalign=natural -qcache=auto -qansialias -qarch=auto -qtune=auto -qrtti=all"
		CXX_DEBUG_FLAGS="-g -DBZ_DEBUG"
		CXX_PROFIL_FLAGS="-p"
	;;      
	FCC) dnl Fujitsu C++
		CXX_VENDOR="Fujitsu"
		CXXFLAGS=""
		CXX_OPTIMIZE_FLAGS="-K fast"
		CXX_DEBUG_FLAGS="-g -DBZ_DEBUG"
	;;
	pgCC) dnl Portland group   http://www.pgroup.com
		CXX_VENDOR="Portland group"
		CXXFLAGS=""
		CXX_OPTIMIZE_FLAGS="-O4 -Mnoframe -Mnodepchk -Minline=levels:25"
		CXX_DEBUG_FLAGS="-g -O0 -DBZ_DEBUG"
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


