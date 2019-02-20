// DESCRIPTION
//
//   Test to check whether the compiler accepts the new for scoping rules (the scope of a
//   variable declared inside the parentheses is restricted to the for-body),
//   define HAVE_NEW_FOR_SCOPING.
//   In sync with AC_CXX_NEW_FOR_SCOPING (2008-04-12).
//
// COPYLEFT
//
//   Copyright (c) 2008 Todd Veldhuizen
//   Copyright (c) 2009 Theo Papadopoulo <Theodore.Papadopoulo@sophia.inria.fr>
//   Copyright (c) 2008 Luc Maisonobe <luc@spaceroots.org>
//
//   Copying and distribution of this file, with or without modification, are
//   permitted in any medium without royalty provided the copyright notice
//   and this notice are preserved.

int main() {
    int z = 0;
    for (int i = 0; i < 10; ++i)
    z = z + i;
    for (int i = 0; i < 10; ++i)
    z = z - i;
    return z;
}
