

AC_DEFUN([AC_CXX_MEMBER_TEMPLATES],[
AC_MSG_CHECKING([whether $CXX accepts member templates])
AC_COMPILE_IFELSE(
[AC_LANG_PROGRAM([[
// Test member function templates
// BZ_MEMBER_TEMPLATES

template<class T, int N>
class Foo {

public:
    template<int N2>
    Foo<T,N> operator=(const Foo<T,N2>&);
};

template<class T, int N> template<int N2>
Foo<T,N> Foo<T,N>::operator=(const Foo<T,N2>& z)
{
    return Foo<T,N>();
}
]],[[
    Foo<double,4> x;
    Foo<double,7> y;
    x = y;

    return 0;
]])],
[AC_MSG_RESULT([yes])
AC_DEFINE([BZ_MEMBER_TEMPLATES],[],[Member templates?])],
[AC_MSG_RESULT([no])])])

