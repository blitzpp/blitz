


AC_DEFUN([AC_CXX_TYPE_PROMOTION],[
AC_MSG_CHECKING([whether $CXX will support the vector type promotion mechanism])
AC_COMPILE_IFELSE(
[AC_LANG_PROGRAM([[]], [[return 0;]])],
[AC_MSG_RESULT([yes])
AC_DEFINE([BZ_TYPE_PROMOTION],[],[Will it support the vector type promotion mechanism?])],
[AC_MSG_RESULT([no])])])


