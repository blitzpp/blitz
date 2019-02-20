// DESCRIPTION
//
//   Test to check whether the C++ compiler handle (int) casts in enum computations.
//   In sync with AC_CXX_ENUM_COMPUTATIONS_WITH_CAST (2008-04-12).
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
    enum { a = ((int)T1::a>(int)T2::a) ? (int)T1::a : (int)T2::b,
           b = (int)T1::b+(int)T2::b,
           c = ((int)T1::c*(int)T2::c+(int)T2::a+(int)T1::a) };
};

int main() {
    return (((int)Z<A,B>::a==5) && ((int)Z<A,B>::b==13) && ((int)Z<A,B>::c==24)) ? 0 : 1;
}
