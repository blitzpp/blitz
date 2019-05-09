// DESCRIPTION
//
//   Test to check whether the compiler supports partial ordering.
//   In sync with AC_CXX_PARTIAL_ORDERING (2008-04-12).
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

template<int N> struct I {};
template<class T> struct A {
    int r;
    template<class T1,class T2> int operator()(T1,T2)        { r = 0; return r; }
    template<int N1,int N2>     int operator()(I<N1>, I<N2>) { r = 1; return r; }
};

int main() {
    A<float> x,y;
    I<0> a;
    I<1> b;
    return x(a,b)+y(float(),double());
}
