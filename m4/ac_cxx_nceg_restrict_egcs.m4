

AC_DEFUN([AC_CXX_NCEG_RESTRICT_EGCS],[
AC_MSG_CHECKING([whether $CXX recognizes the '__restrict__' keyword])
AC_COMPILE_IFELSE(
[AC_LANG_PROGRAM([[
// egcs support for restrict, but as "__restrict__"
// BZ_NCEG_RESTRIC2

void add(int length, double * __restrict__ a, const double * __restrict__ b,
    const double * __restrict__ c)
{
    for (int i=0; i < length; ++i)
        a[i] = b[i] + c[i];
}
]],[[
    double a[10], b[10], c[10];
    for (int i=0; i < 10; ++i)
    {
        a[i] = 0.;
        b[i] = 0.;
        c[i] = 0.;
    }

    add(10,a,b,c);
    return 0;
]])],
[AC_MSG_RESULT([yes])
AC_DEFINE([BZ_NCEG_RESTRICT_EGCS],[],[Maybe it recognizes __restrict__?])],
[AC_MSG_RESULT([no])])])


