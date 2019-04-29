// DESCRIPTION
//
//   Test to check whether the compiler supports function templates with non-type parameters.
//   In sync with AC_CXX_FUNCTION_NONTYPE_PARAMETERS (2008-04-12).
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

template<class T,int N> class A {};
template<class T,int N> int f(const A<T,N>& x) { return 0; }

int main() {
    A<double,17> z;
    return f(z);
}
