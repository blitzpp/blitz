// DESCRIPTION
//
//   Test to check whether the C++ library has a working stringstream.
//   In sync with AC_CXX_HAVE_SSTREAM (2008-04-12).
//
// COPYLEFT
//
//   Copyright (c) 2009 Theo Papadopoulo <Theodore.Papadopoulo@sophia.inria.fr>
//   Copyright (c) 2008 Ben Stanley <Ben.Stanley@exemail.com.au>
//
//   Copying and distribution of this file, with or without modification, are
//   permitted in any medium without royalty provided the copyright notice
//   and this notice are preserved.

//AC_CACHE_CHECK(whether the compiler has stringstream,

#include <sstream>
using namespace std;

int main() {
    stringstream message;
    message << "Hello";
    return 0;
}
