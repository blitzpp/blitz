// DESCRIPTION
//
//   Test to check whether the compiler supports explicit template function qualification.
//   In sync with AC_CXX_EXPLICIT_TEMPLATE_FUNCTION_QUALIFICATION (2008-04-12).
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

template<class Z> class A { public : A() {} };

template<class X,class Y>
A<X> to(const A<Y>&) { return A<X>(); }

int main() {
    A<float> x;
    A<double> y = to<double>(x);
    return 0;
}
