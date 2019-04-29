// DESCRIPTION
//
//   Test whether the C++ compiler supports "extern template".
//   In sync with AC_CXX_EXTERN_TEMPLATE (2008-04-12).
//
// COPYLEFT
//
//   Copyright (c) 2009 Theo Papadopoulo <Theodore.Papadopoulo@sophia.inria.fr>
//   Copyright (c) 2008 Patrick Mauritz <oxygene@studentenbude.ath.cx>
//
//   Copying and distribution of this file, with or without modification, are
//   permitted in any medium without royalty provided the copyright notice
//   and this notice are preserved.

template <typename T> void foo(T); extern template void foo<int>(int);

int main() { }
