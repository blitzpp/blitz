

AC_DEFUN([AC_CXX_HAVE_IEEE_MATH],[
AC_MSG_CHECKING([whether $CXX has IEEE Math library])
AC_COMPILE_IFELSE(
[AC_LANG_PROGRAM([[
// BZ_HAVE_IEEE_MATH

#if !defined(__GNUC__)
 #ifndef _ALL_SOURCE
  #define _ALL_SOURCE
 #endif

 #ifndef _XOPEN_SOURCE
  #define _XOPEN_SOURCE
 #endif

 #ifndef _XOPEN_SOURCE_EXTENDED
  #define _XOPEN_SOURCE_EXTENDED 1
 #endif
#endif

#include <math.h>

// finite and trunc have been removed:
// blitz-bugs/archive/0189.html
]],[[
    double x = 1.0;
    // double y = 1.0;

    acosh(x);
    asinh(x);
    atanh(x);
    cbrt(x);
    erf(x);
    erfc(x);
    expm1(x);
    // finite(x);
    ilogb(x);
    isnan(x);
    j0(x);
    j1(x);
// lgamma function has different interface under AIX in threaded mode
#if !(defined(_AIX) && defined(_THREAD_SAFE))
    lgamma(x);
#endif
    logb(x);
    log1p(x);
    rint(x);
    // trunc(x);
    y0(x);
    y1(x);

    return 0;
]])],
[AC_MSG_RESULT([yes])
AC_DEFINE([BZ_HAVE_IEEE_MATH],[],[IEEE Math library?])],
[AC_MSG_RESULT([no])])])


