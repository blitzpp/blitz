// DESCRIPTION
//
//   Check whether the C++ include <unordered_map> exists and define
//   HAVE_UNORDERED_MAP if it does.
//   In sync with AC_CXX_HEADER_UNORDERED_MAP (2008-04-17).
//
// COPYLEFT
//
//   Copyright (c) 2009 Theo Papadopoulo <Theodore.Papadopoulo@sophia.inria.fr>
//   Copyright (c) 2008 Benjamin Kosnik <bkoz@redhat.com>
//
//   Copying and distribution of this file, with or without modification, are
//   permitted in any medium without royalty provided the copyright notice
//   and this notice are preserved.

#include <unordered_map>;

int main() {
    using std::unordered_map;
}
