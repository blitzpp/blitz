// DESCRIPTION
//
//   Test to check whether the C++ compiler recognizes bool as a separate built-in type.
//   Note that a typedef is not a separate type since you cannot overload a function such
//   that it accepts either the basic type or the typedef.
//   In sync with AC_CXX_BOOL (2008-04-12).
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

int f(int  x) { return 1; }
int f(char x) { return 1; }
int f(bool x) { return 1; }

int main() {
    bool b = true;
    return f(b);
}
