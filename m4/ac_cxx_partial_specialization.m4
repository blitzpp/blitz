

AC_DEFUN([AC_CXX_PARTIAL_SPECIALIZATION],[
AC_MSG_CHECKING([whether $CXX accepts partial specialization])
AC_COMPILE_IFELSE(
[AC_LANG_PROGRAM([[
// Partial specialization
// BZ_PARTIAL_SPECIALIZATION

template<class T_type, int N>
class foo {
public:
  enum bar { z = 0 };
};

template<int N>
class foo<double, N> {
public:
  enum bar { z = 1 };
};

template<class T_type>
class foo<T_type, 2> {
public:
  enum bar { z = 2 };
};
]],[[
    if ((foo<int,3>::z == 0) && (foo<double,3>::z == 1)
       && (foo<float,2>::z == 2))
           return 0;
    else
        return 1;
]])],
[AC_MSG_RESULT([yes])
AC_DEFINE([BZ_PARTIAL_SPECIALIZATION],[],[Partial specialization?])],
[AC_MSG_RESULT([no])])])


