

AC_DEFUN([AC_CXX_TEMPLATE_QUALIFIED_RETURN_TYPE],[
AC_MSG_CHECKING([whether $CXX accepts template-qualified return types])
AC_COMPILE_IFELSE(
[AC_LANG_PROGRAM([[
#ifdef BZ_NO_TYPENAME
 #define typename
#endif


// Template-qualified return type, necessary for type promotion on vectors
// BZ_TEMPLATE_QUALIFIED_RETURN_TYPE


class base1 {
public:
    int bar() const
    { return 1; }
};

class base2 {
public:
    int bar() const
    { return 0; }
};

template<class X>
struct base_trait {
    typedef base1 base;
};

template<>
struct base_trait<float> {
    typedef base2 base;
};

template<class T>
class weird : public base_trait<T>::base {
public:
    typedef typename base_trait<T>::base base;

    int zowee() const
    { return this->bar(); }
};
]],[[
    weird<float> z;
    return z.zowee();
]])],
[AC_MSG_RESULT([yes])
AC_DEFINE([BZ_TEMPLATE_QUALIFIED_RETURN_TYPE],[],
[Template-qualified return types (necessary for vector type promotion)?])],
[AC_MSG_RESULT([no])])])


