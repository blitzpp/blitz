

AC_DEFUN([AC_CXX_HAVE_STD],[AC_MSG_CHECKING([whether $CXX has ISO C++ Standard library])
AC_COMPILE_IFELSE(
[AC_LANG_PROGRAM([[
#include <iostream>
#include <map>
#include <iomanip>

#ifndef BZ_NO_NAMESPACES
using namespace std;
#endif
]],[[
    return 0;
]])],
[AC_MSG_RESULT([yes])
AC_DEFINE([BZ_HAVE_STD],[],[ISO C++ Standard library?])],
[AC_MSG_RESULT([no])])])



