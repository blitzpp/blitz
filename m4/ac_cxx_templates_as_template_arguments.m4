

AC_DEFUN([AC_CXX_TEMPLATES_AS_TEMPLATE_ARGUMENTS],[
AC_MSG_CHECKING([whether $CXX accepts templates as template arguments])
AC_COMPILE_IFELSE(
[AC_LANG_PROGRAM([[
// Templates as template arguments
// BZ_TEMPLATES_AS_TEMPLATE_ARGUMENTS

template<class T>
class allocator {
public:
    allocator() { };
};

template<class X, template<class Y> class T_alloc>
class foo {
public:
   foo() { }

private:
   T_alloc<X> alloc_;
};
]],[[
    foo<double, allocator> x;
    return 0;
]])],
[AC_MSG_RESULT([yes])
AC_DEFINE([BZ_TEMPLATES_AS_TEMPLATE_ARGUMENTS],[],[Templates as template arguments?])],
[AC_MSG_RESULT([no])])])


