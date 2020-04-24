// DESCRIPTION
//
//   Test to check whether the implementation of the C++ library provides the method
//   std::string::push_back (char), define HAVE_STRING_PUSH_BACK.
//   In sync with AC_CXX_HAVE_STRING_PUSH_BACK (2008-04-12).
//
// COPYLEFT
//
//   Copyright (c) 2009 Theo Papadopoulo <Theodore.Papadopoulo@sophia.inria.fr>
//   Copyright (c) 2008 Jan Langer <jan@langernetz.de>
//
//   Copying and distribution of this file, with or without modification, are
//   permitted in any medium without royalty provided the copyright notice
//   and this notice are preserved.

#include <string>
using namespace std;

int main() {
    string message;
    message.push_back('a');
    return 0;
}
