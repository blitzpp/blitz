

AC_DEFUN([AC_CXX_MEMBER_CONSTANTS],[AC_MSG_CHECKING([whether $CXX supports member constants])
AC_COMPILE_IFELSE(
[AC_LANG_PROGRAM([[
// Member constants

class Foo {
public:
    static const int value = 0;
};

const int Foo::value;
]],[[
    return Foo::value;
]])],
[AC_MSG_RESULT([yes])
AC_DEFINE([BZ_MEMBER_CONSTANTS],[],[Member constants?])],
[AC_MSG_RESULT([no])])])

