// DESCRIPTION
//
//   Test to check whether the C math functions are in the cmath header file and std::
//   namespace, define HAVE_MATH_FN_IN_NAMESPACE_STD.
//   In sync with AC_CXX_COMPLEX_MATH_IN_NAMESPACE_STD (2008-04-12).
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
namespace S {
    using namespace std;
    complex<float> pow(complex<float> x, complex<float> y) { return std::pow(x,y); }
}

int main() {
    using namespace S;
    complex<float> x = 1.0, y = 1.0;
    S::pow(x,y);
    return 0;
}
