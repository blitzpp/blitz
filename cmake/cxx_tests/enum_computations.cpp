// DESCRIPTION
//
//   Test to check whether the C++ compiler handle computations inside an enum.
//   In sync with AC_CXX_ENUM_COMPUTATIONS (2008-04-12).
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

struct A { enum { a = 5, b = 7, c = 2 }; };
struct B { enum { a = 1, b = 6, c = 9 }; };

template<class T1,class T2>
struct Z {
    enum { a = (T1::a>T2::a) ? T1::a : T2::b,
         b = T1::b+T2::b,
         c = (T1::c*T2::c+T2::a+T1::a) };
};

int main() {
    return (((int)Z<A,B>::a==5) && ((int)Z<A,B>::b==13) && ((int)Z<A,B>::c==24)) ? 0 : 1;
}
