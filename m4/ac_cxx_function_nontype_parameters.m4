

AC_DEFUN([AC_CXX_FUNCTION_NONTYPE_PARAMETERS],[
AC_MSG_CHECKING([whether $CXX accepts function templates with non-type parameters])
AC_COMPILE_IFELSE(
[AC_LANG_PROGRAM([[
// Test function templates with non-type parameters
// BZ_FUNCTION_NONTYPE_PARAMETERS

template<class T, int N>
class Foo {
};

template<class T, int N>
void showFoo(const Foo<T,N>& x)
{
}
]],[[
    Foo<double, 17> z;
    showFoo(z);
    return 0;
]])],
[AC_MSG_RESULT([yes])
AC_DEFINE([BZ_FUNCTION_NONTYPE_PARAMETERS],[],
[Function templates with non-type parameters?])],
[AC_MSG_RESULT([no])])])



