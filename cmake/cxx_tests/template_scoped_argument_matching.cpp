// DESCRIPTION
//
//   Test to check whether the C++ compiler supports function matching with argument types which are
//   template scope-qualified.
//   In sync with AC_CXX_TEMPLATE_SCOPED_ARGUMENT_MATCHING (2008-04-12).
//
// COPYLEFT
//
//   Copyright (c) 2008 Todd Veldhuizen
//   Copyright (c) 2009 Theo Papadopoulo <Theodore.Papadopoulo@sophia.inria.fr>
//   Copyright (c) 2008 Luc Maisonobe <luc@spaceroots.org>
//
//   Copying and distribution of this file, with or without modification, are
//   permitted in any medium without royalty provided the copyright notice
//   and this notice are preserved.

#ifndef HAVE_TYPENAME
    #define typename
#endif

template<class X> class A { public : typedef X W; };
template<class Y> class B {};
template<class Y> void operator+(B<Y> d1,typename Y::W d2) {}

int main() {
    B<A<float> > z;
    z+0.5f;
    return 0;
}
