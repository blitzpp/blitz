

AC_DEFUN([AC_CXX_NCEG_RESTRICT],[
AC_MSG_CHECKING([whether $CXX recognizes the NCEG 'restrict' keyword])
AC_COMPILE_IFELSE(
[AC_LANG_PROGRAM([[
// Numerical C Extensions Group (NCEG) keyword 'restrict'
// BZ_NCEG_RESTRICT

void add(int length, double * restrict a, const double * restrict b,
    const double * restrict c)
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
AC_DEFINE([BZ_NCEG_RESTRICT],[],[Just on the off chance... the NCEG 'restrict' keyword?])],
[AC_MSG_RESULT([no])])])


