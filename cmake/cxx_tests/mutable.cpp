// DESCRIPTION
//
//   Test to check whether the C++ compiler allows modifying class data members flagged with the
//   mutable keyword even in const objects (for example in the body of a const member function).
//   In sync with AC_CXX_MUTABLE (2008-04-12).
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

class A {
    mutable int i;
public:
    int f (int n) const { i = n; return i; }
};

int main() {
    A a;
    return a.f(1);
}
