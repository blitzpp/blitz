

AC_DEFUN([AC_CXX_EXPLICIT_TEMPLATE_FUNCTION_QUALIFICATION],[
AC_MSG_CHECKING([whether $CXX accepts explicit template function qualification])
AC_COMPILE_IFELSE(
[AC_LANG_PROGRAM([[
// Explicit template function qualification
// BZ_EXPLICIT_TEMPLATE_FUNCTION_QUALIFICATION

template<class Z>
class Vector {
public:
    Vector() { }
};


template<class X, class Y>
Vector<X> to(const Vector<Y>&)
{
    return Vector<X>();
}
]],[[
    Vector<float> x;
    Vector<double> y = to<double>(x);
    return 0;
]])],
[AC_MSG_RESULT([yes])
AC_DEFINE([BZ_EXPLICIT_TEMPLATE_FUNCTION_QUALIFICATION],[],
[Explicit template function qualification?])],
[AC_MSG_RESULT([no])])])


