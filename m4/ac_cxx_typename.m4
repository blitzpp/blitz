

AC_DEFUN([AC_CXX_TYPENAME],[AC_MSG_CHECKING([whether $CXX recognize 'typename'])
AC_COMPILE_IFELSE(
[AC_LANG_PROGRAM([[
template<typename T>
class X {
public:
    X() { }
};
]],[[
    X<float> z;
    return 0;
]])],
[AC_MSG_RESULT([yes])
AC_DEFINE([BZ_TYPENAME],[],[Does your compiler recognize 'typename'?])],
[AC_MSG_RESULT([no])])])


