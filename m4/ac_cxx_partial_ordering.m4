

AC_DEFUN([AC_CXX_PARTIAL_ORDERING],[
AC_MSG_CHECKING([whether $CXX accepts partial ordering])
AC_COMPILE_IFELSE(
[AC_LANG_PROGRAM([[
// Partial ordering of member templates
// BZ_PARTIAL_ORDERING

template<int N>
struct I {
};

template<class T>
struct A {

  int r;

  template<class T1, class T2>
  void operator()(T1, T2)
  { r = 0; }

  template<int N1, int N2>
  void operator()(I<N1>, I<N2>)
  { r = 1; }
};
]],[[
    A<float> x;
    I<0> a;
    I<1> b;

    x(a,b);
    if (x.r != 1)
        return 1;

    x(float(), double());
    if (x.r != 0)
        return 1;

    return 0;
]])],
[AC_MSG_RESULT([yes])
AC_DEFINE([BZ_PARTIAL_ORDERING],[],[Partial ordering?])],
[AC_MSG_RESULT([no])])])


