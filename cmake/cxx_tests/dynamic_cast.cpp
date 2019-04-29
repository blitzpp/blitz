// DESCRIPTION
//
//   Test to check whether the C++ compiler supports dynamic_cast<>.
//   In sync with AC_CXX_DYNAMIC_CAST (2008-04-12).
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

#include <typeinfo>

class Base {
public:
    Base () {}
    virtual void f() = 0;
};

class Derived: public Base {
public:
    Derived() {}
    virtual void f() {}
};

int main() {
    Derived d;
    Base& b=d;
    return dynamic_cast<Derived*>(&b) ? 0 : 1;
};
