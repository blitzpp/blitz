


AC_DEFUN([AC_CXX_TEMPLATE_KEYWORD_QUALIFIER],[
AC_MSG_CHECKING([whether $CXX accepts use of the template keyword as a qualifier])
AC_COMPILE_IFELSE(
[AC_LANG_PROGRAM([[
// 'template' keyword qualifier
// BZ_TEMPLATE_KEYWORD_QUALIFIER

class Foo {
public:
    Foo() { };
    template<class T> static T convert() { return T(); }
};

template <typename T>
double f() {
    return Foo::template convert<double>();
}
]],[[
    double z = f<double>();
    return 0;
]])],
[AC_MSG_RESULT([yes])
AC_DEFINE([BZ_TEMPLATE_KEYWORD_QUALIFIER],[],[Use of the template keyword as a qualifier?])],
[AC_MSG_RESULT([no])])])


