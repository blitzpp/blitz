

AC_DEFUN([AC_CXX_EXPLICIT],[AC_MSG_CHECKING([whether $CXX accepts the 'explicit' keyword])
AC_COMPILE_IFELSE(
[AC_LANG_PROGRAM(
[[
// 'explicit' keyword
// BZ_EXPLICIT

class vector {
  public:
    explicit vector(double)
    { }
};
]],[[
    double c = 5.0;
    vector x(c);
    return 0;
]])],
[AC_MSG_RESULT([yes])
AC_DEFINE([BZ_EXPLICIT],[],[How about the 'explicit' keyword?])],
[AC_MSG_RESULT([no])])])

