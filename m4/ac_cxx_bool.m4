

AC_DEFUN([AC_CXX_BOOL],[AC_MSG_CHECKING([whether $CXX recognizes 'bool' as a built-in type])
AC_COMPILE_IFELSE(
[AC_LANG_PROGRAM([[
// bool treated as distinct type
// BZ_BOOL

int foo(int x)
{
    return 1;
}

int foo(char x)
{
    return 1;
}

int foo(bool x)
{
    return 0;
}
]],[[
    bool c = true;
    return foo(c);
]])],
[AC_MSG_RESULT([yes])
AC_DEFINE([BZ_BOOL],[],[Does it recognize bool as a built-in type?])],
[AC_MSG_RESULT([no])])])

