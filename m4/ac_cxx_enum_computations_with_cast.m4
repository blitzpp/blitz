


AC_DEFUN([AC_CXX_ENUM_COMPUTATIONS_WITH_CAST],[
AC_MSG_CHECKING([whether $CXX handle (int) casts in enum computations])
AC_COMPILE_IFELSE(
[AC_LANG_PROGRAM([[
// BZ_ENUM_COMPUTATIONS_WITH_CAST

struct foo {
    enum { a = 5, b = 7, c = 2 };
};

struct bar {
    enum { a = 1, b = 6, c = 9 };
};

template<class T1, class T2>
struct Z {
    enum { a = ((int)T1::a > (int)T2::a) ? (int)T1::a : (int)T2::b,
           b = (int)T1::b + (int)T2::b,
           c = ((int)T1::c * (int)T2::c + (int)T2::a + (int)T1::a)
    };
};
]],[[
    if (((int)Z<foo,bar>::a == 5) && ((int)Z<foo,bar>::b == 13)
      && ((int)Z<foo,bar>::c == 24))
        return 0;
    else
        return 1;
]])],
[AC_MSG_RESULT([yes])
AC_DEFINE([BZ_ENUM_COMPUTATIONS_WITH_CAST],[],
[Does it handle (int) casts in enum computations?])],
[AC_MSG_RESULT([no])])])


