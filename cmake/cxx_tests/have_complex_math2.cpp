// DESCRIPTION
//
//   Test to check whether the C++ compiler has the complex math functions
//   acos, asin, atan, atan2 and log10.
//   In sync with AC_CXX_HAVE_COMPLEX_MATH2 (2008-04-12).
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

#include <complex>
using namespace std;

int main() {
    complex<double> x(1.0,1.0),y(1.0,1.0);
    acos(x);
    asin(x);
    atan(x);
    atan2(x,y);
    atan2(x,double(3.0));
    atan2(double(3.0),x);
    log10(x);
    return 0;
}
