// DESCRIPTION
//
//   Test to check whether the isnormal function is provided by the cmath header file in std::
//   namespace, define HAVE_ISNORMAL_IN_NAMESPACE_STD.
//
// COPYLEFT
//
//   Copyright (c) 2011 Theo Papadopoulo <Theodore.Papadopoulo@sophia.inria.fr>
//
//   Copying and distribution of this file, with or without modification, are
//   permitted in any medium without royalty provided the copyright notice
//   and this notice are preserved.

#include <cmath>

namespace S {
    bool isnormal(const double x) { return std::isnormal(x); }
}

int main() {
    double d = 3.0;
    const bool res = S::isnormal(d);
    return 0;
}
