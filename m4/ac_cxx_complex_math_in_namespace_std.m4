


AC_DEFUN([AC_CXX_COMPLEX_MATH_IN_NAMESPACE_STD],[
AC_MSG_CHECKING([whether $CXX has complex math functions in std::])
AC_COMPILE_IFELSE(
[AC_LANG_PROGRAM([[
// Where are those pesky math functions?
// BZ_COMPLEX_MATH_IN_NAMESPACE_STD

#include <complex>

namespace blitz {
    using namespace std;

    complex<float> pow(complex<float> x, complex<float> y)
    { return std::pow(x,y); }
};
]],[[
    using namespace blitz;
    complex<float> x = 1.0, y = 1.0;
    blitz::pow(x,y);
    return 0;
]])],
[AC_MSG_RESULT([yes])
AC_DEFINE([BZ_COMPLEX_MATH_IN_NAMESPACE_STD],[],[Are complex math functions in std::?])],
[AC_MSG_RESULT([no])])])



