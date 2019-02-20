// DESCRIPTION
//
//   Test to check whether the isnan function is provided by the cmath header file in std::
//   namespace, define HAVE_ISNAN_IN_NAMESPACE_STD.
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
    bool isnan(const float x) { return std::isnan(x); }
}

int main() {
    using namespace S;
    float x = 1.0;
    S::isnan(x);
    return 0;
}
