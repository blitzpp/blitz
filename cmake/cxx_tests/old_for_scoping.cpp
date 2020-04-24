// DESCRIPTION
//
//   Test to check whether the C++ compiler accepts the old for scoping rules (the scope of a
//   variable declared inside the parentheses extends outside the for-body).
//   Note that some compilers (notably g++ and egcs) support both new and old rules since they
//   accept the old rules and only generate a warning.
//   In sync with AC_CXX_OLD_FOR_SCOPING (2008-04-12).
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
    int z;
    for (int i=0; i < 10; ++i)
        z=z+i;
    z=i;
    return z;
}
