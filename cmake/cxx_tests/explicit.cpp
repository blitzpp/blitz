// DESCRIPTION
//
//   Test to check whether the C++ compiler can be asked to prevent using implicitly one argument
//   constructors as converting constructors with the explicit keyword.
//   In sync with  AC_CXX_EXPLICIT (2008-04-12)
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

class A{
public:
    explicit A(double){}
};

int main() {
    double c = 5.0;
    A x(c);
    return 0;
}
