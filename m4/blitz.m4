## AC_BZ_SET_COMPILER: Addition by Theodore Papadopoulo
## Patch by Jim McKelvey: change sed -e 's/ /@/g' to sed -e 's/ /@/'
AC_DEFUN([AC_BZ_SET_COMPILER],
  [cxxwith=`echo $1 | sed -e 's/ /@/'`
   case "$cxxwith" in
     *:*@*)                 # Full initialization syntax
       CXX=`echo "$cxxwith" | sed  -n -e 's/.*:\(.*\)@.*/\1/p'`
       CXXFLAGS=`echo "$cxxwith" | sed  -n -e 's/.*:.*@\(.*\)/\1/p'`
     ;;
     *:*)                   # Simple initialization syntax
       CXX=`echo "$cxxwith" | sed  -n -e 's/.*:\(.*\)/\1/p'`
       CXXFLAGS=$3
     ;;
     *)                     # Default values
       CXX=$2
       CXXFLAGS=$3
     ;;
   esac])


# Standard stuff follows

AC_DEFUN([AC_CHECK_COMPILERS],
[
  AC_ARG_ENABLE(debug,[  --enable-debug 	  creates debugging code [default=no]],
  [ 
   if test $enableval = "no"; dnl 
     then ac_use_debug_code="no"
     else ac_use_debug_code="yes"
   fi
  ], [ac_use_debug_code="no"])

dnl this was AC_PROG_CC. I had to include it manualy, since I had to patch it
  AC_MSG_CHECKING(for a C-Compiler)
  dnl if there is one, print out. if not, don't matter
  AC_MSG_RESULT($CC) 
 
  if test -z "$CC"; then AC_CHECK_PROG(CC, gcc, gcc) fi
  if test -z "$CC"; then AC_CHECK_PROG(CC, cc, cc, , , /usr/ucb/cc) fi
  if test -z "$CC"; then AC_CHECK_PROG(CC, xlc, xlc) fi
  test -z "$CC" && AC_MSG_ERROR([no acceptable cc found in \$PATH])

  AC_PROG_CC_WORKS
  AC_PROG_CC_GNU

  if test $ac_cv_prog_gcc = yes; then
    GCC=yes
  else
    GCC=
  fi

  if test -z "$CFLAGS"; then
    if test "$ac_use_debug_code" = "yes"; then
      AC_PROG_CC_G
      if test $ac_cv_prog_cc_g = yes; then
        CFLAGS="-g"
      fi
    else
      if test "$GCC" = "yes"; then
        CFLAGS="-O2"
      else
        CFLAGS=""
      fi
    fi

    if test "$GCC" = "yes"; then
     CFLAGS="$CFLAGS -Wall"
    fi

  fi

  if test -z "$LDLFLAGS" && test "$ac_use_debug_code" = "no" && test "$GCC" = "yes"; then
     LDFLAGS="-s"
  fi




dnl this is AC_PROG_CPP. I had to include it here, since autoconf checks
dnl dependecies between AC_PROG_CPP and AC_PROG_CC (or is it automake?)

  AC_MSG_CHECKING(how to run the C preprocessor)
  # On Suns, sometimes $CPP names a directory.
  if test -n "$CPP" && test -d "$CPP"; then
    CPP=
  fi
  if test -z "$CPP"; then
  AC_CACHE_VAL(ac_cv_prog_CPP,
  [  # This must be in double quotes, not single quotes, because CPP may get
    # substituted into the Makefile and "${CC-cc}" will confuse make.
    CPP="${CC-cc} -E"
    # On the NeXT, cc -E runs the code through the compiler's parser,
    # not just through cpp.
    dnl Use a header file that comes with gcc, so configuring glibc    
    dnl with a fresh cross-compiler works.
    AC_TRY_CPP([#include <assert.h>
    Syntax Error], ,
    CPP="${CC-cc} -E -traditional-cpp"
    AC_TRY_CPP([#include <assert.h>
    Syntax Error], , CPP=/lib/cpp))
    ac_cv_prog_CPP="$CPP"])dnl
    CPP="$ac_cv_prog_CPP"
  else
    ac_cv_prog_CPP="$CPP"
  fi
  AC_MSG_RESULT($CPP)
  AC_SUBST(CPP)dnl


  AC_MSG_CHECKING(for a C++-Compiler)
  dnl if there is one, print out. if not, don't matter
  AC_MSG_RESULT($CXX) 
 
  if test -z "$CXX"; then AC_CHECK_PROG(CXX, g++, g++) fi
  if test -z "$CXX"; then AC_CHECK_PROG(CXX, CC, CC) fi
  if test -z "$CXX"; then AC_CHECK_PROG(CXX, xlC, xlC) fi
  if test -z "$CXX"; then AC_CHECK_PROG(CXX, DCC, DCC) fi
  test -z "$CXX" && AC_MSG_ERROR([no acceptable C++-compiler found in \$PATH])

  AC_PROG_CXX_WORKS
  AC_PROG_CXX_GNU

  if test $ac_cv_prog_gxx = yes; then
    GXX=yes
  else
    AC_MSG_CHECKING(whether we are using SPARC CC)
    GXX=
    cat > conftest.C << EOF
#ifdef __SUNPRO_CC
   yes;
#endif
EOF

    ac_try="$CXX -E conftest.C"
    if { (eval echo configure:__online__: \"$ac_try\") 1>&5; (eval $ac_try) 2>&5; } | egrep yes >/dev/null 2>&1; then
      ac_cv_prog_CC=yes
    else
      ac_cv_prog_CC=no
    fi
    AC_MSG_RESULT($ac_cv_prog_CC)
  fi

  if test -z "$CXXFLAGS"; then 
    if test "$ac_use_debug_code" = "yes"; then
      AC_PROG_CXX_G
      if test $ac_cv_prog_cxx_g = yes; then
        CXXFLAGS="-g"
      fi
      if test "$ac_cv_prog_CC" = "yes"; then
        CXXFLAGS="$CXXFLAGS -pto"
      fi
    else
      if test "$GXX" = "yes"; then
         CXXFLAGS="-O2"
      else
         if test "$ac_cv_prog_CC" = "yes"; then
            CXXFLAGS="-pto -O2"
         else
            CXXFLAGS=""
         fi
      fi
    fi

    if test "$GXX" = "yes"; then
       CXXFLAGS="$CXXFLAGS -Wall"
    fi
  fi  

])

dnl Checking the compiler option which is used to set the
dnl runtime library path.

AC_DEFUN([AC_CHECK_RPATH_OPTION], [
AC_MSG_CHECKING(whether to use '-R' or '-Wl,-rpath')
AC_CACHE_VAL(ac_cv_check_rpath_option,
[
testfile='.ac_cv_check_rpath_option_test_file.c'
echo 'int main() {}' > $testfile
for i in '-R' '-Wl,-rpath,'; do
    if $CC ${i}/lib -o /dev/null $testfile 2> /dev/null;
    then ac_cv_check_rpath_option=$i;
    fi
done
\rm -rf $testfile
])
if test -z "$ac_cv_check_rpath_option"; then
    AC_MSG_WARN(Could not find a compiler option to specify the run time library directory (like '-R' or '-Wl,-rpath ') for the compiler '$CC'. In consequence the variable 'RPATH' will remain unset.)
    RPATH=@RPATH@
else
    RPATH=$ac_cv_check_rpath_option
    AC_MSG_RESULT($RPATH)
fi
AC_SUBST(RPATH)
])

dnl Checking whether the compiler needs the -rdynamic flag
dnl when linking a program using the libdl.
dnl The test is somewhat different from usual tests because
dnl gcc returns an exit code of 0 even if the option does
dnl not exist. So we have to check the output to see whether
dnl the compiler complains... This is ugly and fragile.

AC_DEFUN([AC_CHECK_RDYNAMICFLAG], [
AC_MSG_CHECKING(whether to use '-rdynamic')
AC_CACHE_VAL(ac_cv_check_rdynamic_option,
[
testfile='.ac_cv_check_rdynamic_option_test_file.c'
echo 'int main() {}' > $testfile
if test -z "`$CC -rdynamic -o /dev/null $testfile 2>&1`";
then
    ac_cv_check_rdynamic_option="-rdynamic"
else
    ac_cv_check_rdynamic_option=""
fi
\rm -rf $testfile
])
if test -z "$ac_cv_check_rdynamic_option"; then
    AC_MSG_RESULT(no)
else
    AC_MSG_RESULT(yes)
fi
RDYNAMICFLAG=$ac_cv_check_rdynamic_option
AC_SUBST(RDYNAMICFLAG)
])
