

AC_DEFUN([AC_CXX_HAVE_COMPLEX],[AC_MSG_CHECKING([whether $CXX has complex<T>])
AC_COMPILE_IFELSE(
[AC_LANG_PROGRAM([[
// complex<T> class

#include <complex>

#ifndef BZ_NO_NAMESPACES
using namespace std;
#endif
]], [[
    complex<float> a;
    complex<double> b;
    return 0;
]])],
[AC_MSG_RESULT([yes])
AC_DEFINE([BZ_HAVE_COMPLEX],[],[Does it have complex<T>?])],
[AC_MSG_RESULT([no])])])



