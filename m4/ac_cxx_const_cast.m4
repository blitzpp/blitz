
AC_DEFUN([AC_CXX_CONST_CAST],[AC_MSG_CHECKING([whether $CXX accepts 'const_cast<>'])
AC_COMPILE_IFELSE(
[AC_LANG_PROGRAM([[
// const_cast<T>
]],[[
    int x = 0;
    const int& y = x;

    int& z = const_cast<int&>(y);
    z = 3;
    if (x == 3)
        return 0;

    return 1;
]])],
[AC_MSG_RESULT([yes])
AC_DEFINE([BZ_CONST_CAST],[],[What about const_cast<>?])],
[AC_MSG_RESULT([no])])])


