


AC_DEFUN([AC_CXX_HAVE_COMPLEX_FCNS],
[AC_CACHE_CHECK(whether the compiler has standard complex<T> functions,
ac_cv_cxx_have_complex_fcns,
[AC_LANG_SAVE
 AC_LANG_CPLUSPLUS
 AC_TRY_COMPILE([#include <complex>
using namespace std;
],[complex<double> x(1.0, 1.0);
real(x); imag(x); abs(x); arg(x); norm(x); conj(x); polar(1.0,1.0);
return 0;],
 ac_cv_cxx_have_complex_fcns=yes, ac_cv_cxx_have_complex_fcns=no)
 AC_LANG_RESTORE
])
if test "$ac_cv_cxx_have_complex_fcns" = yes; then
  AC_DEFINE(HAVE_COMPLEX_FCNS,,[define if the compiler has standard complex<T> functions])
fi
])


