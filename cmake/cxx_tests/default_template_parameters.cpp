// DESCRIPTION
//
//   Test to check whether the C++ compiler supports default template parameters.
//   In sync with AC_CXX_DEFAULT_TEMPLATE_PARAMETERS (2008-04-12).
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

template<class T=double,int N=10>
class A {
public:
    int f() {return 0;}
};

int main() {
    A<float> a;
    return a.f();
}
