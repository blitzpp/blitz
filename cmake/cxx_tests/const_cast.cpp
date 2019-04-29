// DESCRIPTION
//
//   Test to check whether the C++ compiler supports const_cast<>.
//   In sync with AC_CXX_CONST_CAST (2008-04-12)
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

int main() {
    int x = 0;
    const int& y = x;
    int& z = const_cast<int&>(y);
    return z;
}
