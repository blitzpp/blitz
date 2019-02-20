// DESCRIPTION
//
//   Test to check whether the C++ compiler supports member templates outside the class declaration.
//   In sync with AC_CXX_MEMBER_TEMPLATES_OUTSIDE_CLASS (2008-04-12).
//
// COPYLEFT
//
//   Copyright (c) 2008 Todd Veldhuizen
//   Copyright (c) 2009 Theo Papadopoulo <Theodore.Papadopoulo@sophia.inria.fr>
//   Copyright (c) 2008 Luc Maisonobe <luc@spaceroots.org>
//
//   Copying and distribution of this file, with or without modification, are
//   permitted in any medium without royalty provided the copyright notice
//   and this notice are preserved.

template<class T,int N> class A {
public :
    template<int N2> A<T,N> operator=(const A<T,N2>& z);
};

template<class T,int N>
template<int N2>
A<T,N> A<T,N>::operator=(const A<T,N2>& z) { return A<T,N>(); }

int main() {
    A<double,4> x;
    A<double,7> y;
    x = y;
    return 0;
}
