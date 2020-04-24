// DESCRIPTION
//
//   Test to check whether the C++ compiler has the double math functions
//   _class, trunc, itrunc, nearest, rsqrt, uitrunc, copysign, drem, finite,
//   and unordered.
//   In sync with AC_CXX_HAVE_SYSTEM_V_MATH (2008-04-12).
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
    _class(x);
    trunc(x);
    finite(x);
    itrunc(x);
    nearest(x);
    rsqrt(x);
    uitrunc(x);
    copysign(x,y);
    drem(x,y);
    unordered(x,y);
    return 0;
}
