


AC_DEFUN([AC_CXX_MATH_FN_IN_NAMESPACE_STD],[
AC_MSG_CHECKING([whether $CXX has C math functions in <cmath> and std::])
AC_COMPILE_IFELSE(
[AC_LANG_PROGRAM([[
// Where are those pesky math functions?
// BZ_MATH_FN_IN_NAMESPACE_STD

#include <cmath>

namespace blitz {
    double pow(double x, double y)
    { return std::pow(x,y); }
};
]],[[
    using namespace blitz;
    double x = 1.0, y = 1.0;
    blitz::pow(x,y);
    return 0;
]])],
[AC_MSG_RESULT([yes])
AC_DEFINE([BZ_MATH_FN_IN_NAMESPACE_STD],[],[Are C math functions in <cmath> and std::])],
[AC_MSG_RESULT([no])])])



