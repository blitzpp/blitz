

AC_DEFUN([AC_CXX_HAVE_CLIMITS],[AC_MSG_CHECKING([whether $CXX has <climits>])
AC_COMPILE_IFELSE(
[AC_LANG_PROGRAM([[
// has the <climits> header?

#include <climits>

]],[[
    int i = INT_MIN;
    return 0;
]])],
[AC_MSG_RESULT([yes])
AC_DEFINE([BZ_HAVE_CLIMITS],[],[Does it have <climits>?])],
[AC_MSG_RESULT([no])])])


