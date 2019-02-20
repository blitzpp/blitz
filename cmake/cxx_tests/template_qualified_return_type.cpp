// DESCRIPTION
//
//   Test to check whether the compiler supports template-qualified return types.
//   In sync with AC_CXX_TEMPLATE_QUALIFIED_RETURN_TYPE (2008-04-12).
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

#ifndef HAVE_TYPENAME
    #define typename
#endif

template<class X,class Y> struct promote_trait             { typedef X T;     };
template<>                struct promote_trait<int, float> { typedef float T; };

template<class T> class A { public : A () {} };

template<class X,class Y>
A<typename promote_trait<X,Y>::T> operator+ (const A<X>&, const A<Y>&) { return A<typename promote_trait<X,Y>::T>(); }

int main() {
    A<int> x;
    A<float> y;
    A<float> z = x + y;
    return 0;
}
