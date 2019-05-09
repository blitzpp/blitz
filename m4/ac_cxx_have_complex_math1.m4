dnl Available from the GNU Autoconf Macro Archive at:
dnl http://www.gnu.org/software/ac-archive/htmldoc/ac_cxx_have_complex_math1.html
dnl
AC_DEFUN([AC_CXX_HAVE_COMPLEX_MATH1],
[AC_CACHE_CHECK(whether the compiler has complex math functions,
ac_cv_cxx_have_complex_math1,
[AC_LANG_SAVE
 AC_LANG_CPLUSPLUS
 ac_save_LIBS="$LIBS"
 LIBS="$LIBS -lm"
 AC_TRY_LINK([#include <complex>
using namespace std;
],[complex<double> x(1.0, 1.0), y(1.0, 1.0);
cos(x); cosh(x); exp(x); log(x); pow(x,1); pow(x,double(2.0));
pow(x, y); pow(double(2.0), x); sin(x); sinh(x); sqrt(x); tan(x); tanh(x);
return 0;],
 ac_cv_cxx_have_complex_math1=yes, ac_cv_cxx_have_complex_math1=no)
 LIBS="$ac_save_LIBS"
 AC_LANG_RESTORE
])
if test "$ac_cv_cxx_have_complex_math1" = yes; then
  AC_DEFINE(HAVE_COMPLEX_MATH1,,[define if the compiler has complex math functions])
fi
])
