

AC_DEFUN([AC_CXX_HAVE_VALARRAY],[AC_MSG_CHECKING([whether $CXX has valarray<T>])
AC_COMPILE_IFELSE(
[AC_LANG_PROGRAM([[
// valarray<T> class

#include <valarray>

#ifndef BZ_NO_NAMESPACES
using namespace std;
#endif
]],[[
    valarray<float> x(100);
    return 0;
]])],
[AC_MSG_RESULT([yes])
AC_DEFINE([BZ_HAVE_VALARRAY],[],[Does it have valarray<T>?])],
[AC_MSG_RESULT([no])])])



