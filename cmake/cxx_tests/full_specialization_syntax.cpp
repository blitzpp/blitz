// DESCRIPTION
//
//   Test to check whether the C++ compiler recognizes the full specialization syntax.
//   In sync with AC_CXX_FULL_SPECIALIZATION_SYNTAX (2008-04-12).
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

template<class T> class A        { public : int f () const { return 1; } };
template<>        class A<float> { public:  int f () const { return 0; } };

int main() {
    A<float> a;
    return a.f();
}
