

AC_DEFUN([AC_CXX_FULL_SPECIALIZATION_SYNTAX],[
AC_MSG_CHECKING([whether $CXX recognizes the full specialization syntax])
AC_COMPILE_IFELSE(
[AC_LANG_PROGRAM([[
// Special syntax for full specialization

template<class T>
class foo {
public:
    int bar() const
    { return 1; }
};

template<>
class foo<float> {
public:
    int bar() const
    { return 0; }
};
]],[[
    foo<float> z;
    return z.bar();
]])],
[AC_MSG_RESULT([yes])
AC_DEFINE([BZ_FULL_SPECIALIZATION_SYNTAX],[],
[Does it recognize the full specialization syntax?])],
[AC_MSG_RESULT([no])])])



