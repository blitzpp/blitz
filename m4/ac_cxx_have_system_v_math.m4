


AC_DEFUN([AC_CXX_HAVE_SYSTEM_V_MATH],[
AC_MSG_CHECKING([whether $CXX has system V Math library])
AC_COMPILE_IFELSE(
[AC_LANG_PROGRAM([[
// BZ_HAVE_SYSTEM_V_MATH

#ifndef _ALL_SOURCE
 #define _ALL_SOURCE
#endif

#ifndef _XOPEN_SOURCE
 #define _XOPEN_SOURCE
#endif

#ifndef _XOPEN_SOURCE_EXTENDED
 #define _XOPEN_SOURCE_EXTENDED 1
#endif

#include <math.h>
]],[[
    double x = 1.0;
    double y = 1.0;

    _class(x);
    itrunc(x);
    nearest(x);
    rsqrt(x);
    uitrunc(x);

    copysign(x,y);
    drem(x,y);
    hypot(x,y);
    nextafter(x,y);
    remainder(x,y);
    scalb(x,y);
    unordered(x,y);

    return 0;
]])],
[AC_MSG_RESULT([yes])
AC_DEFINE([BZ_HAVE_SYSTEM_V_MATH],[],[System V Math library?])],
[AC_MSG_RESULT([no])])])



