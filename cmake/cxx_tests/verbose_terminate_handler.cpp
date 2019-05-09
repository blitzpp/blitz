// DESCRIPTION
//
//   Test to check whether the compiler does have the verbose terminate handler, define
//   HAVE_VERBOSE_TERMINATE_HANDLER.
//   In sync with AC_CXX_VERBOSE_TERMINATE_HANDLER (2008-04-12).
//
// COPYLEFT
//
//   Copyright (c) 2009 Theo Papadopoulo <Theodore.Papadopoulo@sophia.inria.fr>
//   Copyright (c) 2008 Lapo Luchini <lapo@lapo.it>
//
//   Copying and distribution of this file, with or without modification, are
//   permitted in any medium without royalty provided the copyright notice
//   and this notice are preserved.

#include <exception>;

int main() {
    std::set_terminate(__gnu_cxx::__verbose_terminate_handler);
}
