

AC_DEFUN([AC_CXX_OLD_FOR_SCOPING],[
AC_MSG_CHECKING([whether $CXX cling to the old 'for' scoping rule])
AC_COMPILE_IFELSE(
[AC_LANG_PROGRAM([[
// Old 'for' scoping rules
]], [[
    long z = 0;
    for (int i=0; i < 10; ++i)
    {
        z = z + i;
    }
    z = i;
    return 0;
]])],
[AC_MSG_RESULT([yes])
AC_DEFINE([BZ_OLD_FOR_SCOPING],[],[Does your compiler cling to the old 'for' scoping rule?])],
[AC_MSG_RESULT([no])])])


