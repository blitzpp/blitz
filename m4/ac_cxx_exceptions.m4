

AC_DEFUN([AC_CXX_EXCEPTIONS],[AC_MSG_CHECKING([whether $CXX support exceptions])
AC_COMPILE_IFELSE(
[AC_LANG_PROGRAM([[
// Exceptions
// BZ_EXCEPTIONS

#include <typeinfo>

class foo { };

int divide(int a, int b)
{
    if (b == 0)
        throw foo();

    return a / b;
}
]],[[
    try {
        divide(5,0);
    }
    catch(foo x) {
        return 0;
    }

    return 1;
]])],
[AC_MSG_RESULT([yes])
AC_DEFINE([BZ_EXCEPTIONS],[],[What about exceptions?])],
[AC_MSG_RESULT([no])])])


