

AC_DEFUN([AC_CXX_DEFAULT_TEMPLATE_PARAMETERS],[
AC_MSG_CHECKING([whether $CXX accepts default template parameters])
AC_COMPILE_IFELSE(
[AC_LANG_PROGRAM([[
// Default template parameters
// BZ_DEFAULT_TEMPLATE_PARAMETERS

template<class T_type = double, int N = 10>
class foo {
public:
    int bar() const
    { return 0; }
};
]],[[
    foo<float> z;
    return z.bar();
]])],
[AC_MSG_RESULT([yes])
AC_DEFINE([BZ_DEFAULT_TEMPLATE_PARAMETERS],[],[Default template parameters?])],
[AC_MSG_RESULT([no])])])


