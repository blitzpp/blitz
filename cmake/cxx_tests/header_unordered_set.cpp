// DESCRIPTION
//
//   Check whether the C++ include <unordered_set> exists and define
//   HAVE_UNORDERED_SET if it does.
//   In sync with AC_CXX_HEADER_UNORDERED_SET (2008-04-17).
//
// COPYLEFT
//
//   Copyright (c) 2009 Theo Papadopoulo <Theodore.Papadopoulo@sophia.inria.fr>
//   Copyright (c) 2008 Benjamin Kosnik <bkoz@redhat.com>
//
//   Copying and distribution of this file, with or without modification, are
//   permitted in any medium without royalty provided the copyright notice
//   and this notice are preserved.

#include <unordered_set>;

int main() {
    using std::unordered_set;
}
