

AC_DEFUN([AC_CXX_TEMPLATE_SCOPED_ARGUMENT_MATCHING],[
AC_MSG_CHECKING([whether $CXX accepts function matching with argument types which are template scope-qualified])
AC_COMPILE_IFELSE(
[AC_LANG_PROGRAM([[
#ifdef BZ_NO_TYPENAME
 #define typename
#endif

// BZ_TEMPLATE_SCOPED_ARGUMENT_MATCHING
template<class X>
class A {
public:
    typedef X W;
};

template<class Y>
class B {

};

template<class Y>
void operator+(B<Y> d1, typename Y::W d2)
{
}
]],[[
    B<A<float> > z;
    z + 0.5f;     //        match +(B<A<float>>, A<float>::W)
                  //              +(B<A<float>>, float)       ...?
    return 0;
]])],
[AC_MSG_RESULT([yes])
AC_DEFINE([BZ_TEMPLATE_SCOPED_ARGUMENT_MATCHING],[],
[Function matching with argument types which are template scope-qualified?])],
[AC_MSG_RESULT([no])])])


