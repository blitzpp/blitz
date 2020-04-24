// DESCRIPTION
//
//   Append to variable CXX-FLAGS the set of compile-time flags that should
//   be passed to the C++ compiler in order to enable use of C++ features as
//   defined in the ANSI C++ standard (eg. use of standard iostream classes
//   in the `std' namespace, etc.). Note that if you use GNU Libtool you may
//   need to prefix each of those flags with `-Xcompiler' so that Libtool
//   doesn't discard them (see Libtool's manual and `AC_LIBTOOLIZE_CFLAGS').
//   In sync with AC_CXX_CXXFLAGS_STD_LANG(CXX-FLAGS) (2008-04-12).
//
// COPYLEFT
//
//   Copyright (c) 2009 Theo Papadopoulo <Theodore.Papadopoulo@sophia.inria.fr>
//   Copyright (c) 2008 Ludovic Courtès <ludo@chbouib.org>
//
//   Copying and distribution of this file, with or without modification, are
//   permitted in any medium without royalty provided the copyright notice
//   and this notice are preserved.

AC_DEFUN([AC_CXX_CXXFLAGS_STD_LANG],
  [AC_REQUIRE([AC_CXX_COMPILER_VENDOR])
   case "$ac_cv_cxx_compiler_vendor" in
     sgi)    $1="$$1 -LANG:std -exceptions";;
     hp)     $1="$$1 -AA";;
   esac])
