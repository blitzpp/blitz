

AC_DEFUN([AC_CXX_TEMPLATES],[AC_MSG_CHECKING([whether $CXX handle basic templates ])
AC_COMPILE_IFELSE(
[AC_LANG_PROGRAM([[
// Basic templates

template<class T>
class Vector {
public:
    Vector() { }
};

template<class T>
void foo(const Vector<T>& )
{ }
]],[[
    Vector<float> x;
    Vector<int> z;
    foo(x);
    foo(z);
    return 0;
]])],
[AC_MSG_RESULT([yes])
AC_DEFINE([BZ_TEMPLATES],[],[Will it handle basic templates?])],
[AC_MSG_RESULT([no])
AC_MSG_ERROR([Cannot handle templates, just give up now])
])])


