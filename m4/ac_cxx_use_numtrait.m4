

AC_DEFUN([AC_CXX_USE_NUMTRAIT],[
AC_MSG_CHECKING([whether $CXX supports numeric traits promotions])
AC_COMPILE_IFELSE(
[AC_LANG_PROGRAM([[
#ifdef BZ_NO_TYPENAME
 #define typename
#endif


// BZ_USE_NUMTRAIT

template<class T_numtype>
class SumType {
public:
    typedef T_numtype T_sumtype;
};

template<>
class SumType<char> {
public:
    typedef int       T_sumtype;
};

template<class T>
class Vector {
};

template<class T>
Vector<typename SumType<T>::T_sumtype>
sum(Vector<T>)
{
    return Vector<typename SumType<T>::T_sumtype>();
}
]],[[
    Vector<float> x;
    sum(x);
    return 0;
]])],
[AC_MSG_RESULT([yes])
AC_DEFINE([BZ_USE_NUMTRAIT],[],[Numeric traits promotions (sum type, etc.)?])],
[AC_MSG_RESULT([no])])])


