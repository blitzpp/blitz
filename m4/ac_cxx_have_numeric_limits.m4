


AC_DEFUN([AC_CXX_HAVE_NUMERIC_LIMITS],[AC_MSG_CHECKING([whether $CXX has numeric_limits<T>])
AC_COMPILE_IFELSE(
[AC_LANG_PROGRAM([[
// numeric_limits<T> class

#include <limits>

#ifndef BZ_NO_NAMESPACES
using namespace std;
#endif
]],[[
    double e = numeric_limits<double>::epsilon();
    return 0;
]])],
[AC_MSG_RESULT([yes])
AC_DEFINE([BZ_HAVE_NUMERIC_LIMITS],[],[Does it have numeric_limits<T>?])],
[AC_MSG_RESULT([no])])])


