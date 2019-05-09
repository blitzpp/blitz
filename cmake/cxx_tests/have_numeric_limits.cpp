// DESCRIPTION
//
//   Test to check whether the C++ compiler has numeric_limits<T>.
//   In sync with AC_CXX_HAVE_NUMERIC_LIMITS (2008-04-12).
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

#include <limits>
using namespace std;

int main() {
    double e = numeric_limits<double>::epsilon();
    return 0;
}
