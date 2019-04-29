// DESCRIPTION
//
//   Test to check whether the C++ compiler supports Run-Time Type
//   Identification (typeinfo header and typeid keyword).
//   In sync with AC_CXX_RTTI (2008-04-12).
//
// Copyright (c) 2009 Theo Papadopoulo <Theodore.Papadopoulo@sophia.inria.fr>
//
// COPYLEFT
//
//   Copyright (c) 2008 Todd Veldhuizen
//   Copyright (c) 2008 Luc Maisonobe <luc@spaceroots.org>
//
//   Copying and distribution of this file, with or without modification, are
//   permitted in any medium without royalty provided the copyright notice
//   and this notice are preserved.

#include <typeinfo>

class Base {
public:
    Base () {}
    virtual int f () { return 0; }
};

class Derived: public Base {
public :
    Derived () {}
    virtual int f () { return 1; }
};

int main() {
    Derived d;
    Base *ptr = &d;
    return typeid (*ptr) == typeid (Derived);
}
