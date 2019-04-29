// DESCRIPTION
//
//   Test to check whether the C++ compiler supports numeric traits promotions.
//   In sync with AC_CXX_USE_NUMTRAIT (2008-04-12).
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

template<class T_numtype> class SumType       { public: typedef T_numtype T_sumtype; };
template<>                class SumType<char> { public: typedef int T_sumtype;       };

template<class T> class A {};
template<class T> A<typename SumType<T>::T_sumtype> sum(A<T>) {
    return A<typename SumType<T>::T_sumtype>();
}

int main() {
    A<float> x;
    sum(x);
    return 0;
}
