


AC_DEFUN([AC_CXX_HAVE_RUSAGE],[AC_MSG_CHECKING([whether $CXX has getrusage()])
AC_COMPILE_IFELSE(
[AC_LANG_PROGRAM([[
#include <sys/resource.h>
]],[[
    struct rusage resUsage;
    getrusage(RUSAGE_SELF, &resUsage);
    return 0;
]])],
[AC_MSG_RESULT([yes])
AC_DEFINE([BZ_HAVE_RUSAGE],[],[What about getrusage()?])],
[AC_MSG_RESULT([no])])])


