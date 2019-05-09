// DESCRIPTION
//
//   whether the compiler recognizes typename the C++ compiler recognizes the typename keyword.
//   In sync with AC_CXX_TYPENAME (2008-04-12).
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

template<typename T>
class X {
public:
    X(){}
};

int main() {
    X<float> z;
    return 0;
}
