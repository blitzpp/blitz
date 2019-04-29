// DESCRIPTION
//
//   Test to check whether the C++ compiler supports use of the template keyword as a qualifier.
//   In sync with AC_CXX_TEMPLATE_KEYWORD_QUALIFIER (2008-04-12).
//
// COPYLEFT
//
//   Copyright (c) 2008 Todd Veldhuizen
//   Copyright (c) 2009 Theo Papadopoulo <Theodore.Papadopoulo@sophia.inria.fr>
//   Copyright (c) 2008 Bernardo Innocenti
//   Copyright (c) 2008 Luc Maisonobe <luc@spaceroots.org>
//
//   Copying and distribution of this file, with or without modification, are
//   permitted in any medium without royalty provided the copyright notice
//   and this notice are preserved.

class X {
public:
    template<int> void member() {}
    template<int> static void static_member() {}
};

template<class T> void f(T* p) {
    p->template member<200>(); // OK: < starts template argument
    T::template static_member<100>(); // OK: < starts explicit qualification
}

int main() {
    X x;
    f(&x);
    return 0;
}
