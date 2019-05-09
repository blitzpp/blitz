// DESCRIPTION
//
//   Test to check whether the compiler supports template-qualified base class specifiers.
//   In sync with AC_CXX_TEMPLATE_QUALIFIED_BASE_CLASS (2008-04-12).
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

class Base1 { public : int f () const { return 1; } };
class Base2 { public : int f () const { return 0; } };

template<class X> struct base_trait        { typedef Base1 base; };

#ifdef HAVE_FULL_SPECIALIZATION_SYNTAX
template<>        struct base_trait<float> { typedef Base2 base; };
#else
                  struct base_trait<float> { typedef Base2 base; };
#endif

template<class T>
class Weird: public base_trait<T>::base {
public :
  typedef typename base_trait<T>::base base;
  int g () const { return base::f (); }
};

int main() {
    Weird<float> z;
    return z.g();
}
