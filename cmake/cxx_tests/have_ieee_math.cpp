// DESCRIPTION
//
//   Test to check whether the C++ compiler has the double math functions
//   acosh, asinh, atanh, cbrt, expm1, erf, erfc, isnan, j0, j1, jn, gamma,
//   lgamma, ilogb, logb, log1p, rint, y0, y1, yn, hypot, nextafter, remainder
//   and scalb.
//   In sync with AC_CXX_HAVE_IEEE_MATH (2008-04-12).
//
// COPYLEFT
//
//   Copyright (c) 2009 Theo Papadopoulo <Theodore.Papadopoulo@sophia.inria.fr>
//   Copyright (c) 2008 Todd Veldhuizen
//   Copyright (c) 2008 Luc Maisonobe <luc@spaceroots.org>
//
//   Copying and distribution of this file, with or without modification, are
//   permitted in any medium without royalty provided the copyright notice
//   and this notice are preserved.

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

int main() {
    double x = 1.0;
    double y = 1.0;
    int i = 1;
    acosh(x);
    asinh(x);
    atanh(x);
    cbrt(x);
    expm1(x);
    erf(x);
    erfc(x);
    isnan(x);
    j0(x);
    j1(x);
    jn(i,x);
    ilogb(x);
    logb(x);
    log1p(x);
    rint(x);
    y0(x);
    y1(x);
    yn(i,x);
#   ifdef _THREAD_SAFE
    gamma_r(x,&i);
    lgamma_r(x,&i);
#   else
    gamma(x);
    lgamma(x);
#   endif
    hypot(x,y);
    nextafter(x,y);
    remainder(x,y);
    scalb(x,y);
    return 0;
}
