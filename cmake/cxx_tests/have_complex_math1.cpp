// DESCRIPTION
//
//   Test to check whether the C++ compiler has the complex math
//   functions cos, cosh, exp, log, pow, sin, sinh, sqrt, tan and
//   tanh.
//   In sync with AC_CXX_HAVE_COMPLEX_MATH1 (2008-04-12).
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
    complex<double> x(1.0,1.0),y(1.0, 1.0);
    cos(x);
    cosh(x);
    exp(x);
    log(x);
    pow(x,1);
    pow(x,double(2.0));
    pow(x,y);
    pow(double(2.0),x);
    sin(x);
    sinh(x);
    sqrt(x);
    tan(x);
    tanh(x);
    return 0;
}
