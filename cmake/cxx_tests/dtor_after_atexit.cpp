// DESCRIPTION
//
//   Test to check whether the C++ compiler calls global destructors after atexit functions,
//   define HAVE_DTOR_AFTER_ATEXIT. WARNING: If cross-compiling, the test
//   cannot be performed, the default action is to define
//   HAVE_DTOR_AFTER_ATEXIT.
//   In sync with AC_CXX_DTOR_AFTER_ATEXIT (2008-04-12).
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

#include <unistd.h>
#include <stdlib.h>

static int dtor_called = 0;
class A { public : ~A () { dtor_called = 1; } };
static A a;

void f() { _exit(dtor_called); }

int main (int , char **)
{
  atexit (f);
  return 0;
}
