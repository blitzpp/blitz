// DESCRIPTION
//
//   Test to check whether the C++ compiler supports the Standard Template
//   Library.
//   In sync with AC_CXX_HAVE_STL (2008-04-12).
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

#include <list>
#include <deque>
using namespace std;

int main() {
    list<int> x;
    x.push_back(5);
    list<int>::iterator iter = x.begin();
    if (iter!=x.end()) ++iter;
    return 0;
}
