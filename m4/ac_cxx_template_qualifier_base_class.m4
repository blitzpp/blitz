

AC_DEFUN([AC_CXX_TEMPLATE_QUALIFIED_BASE_CLASS],[
AC_MSG_CHECKING([whether $CXX accepts template-qualified base class specifiers?])
AC_COMPILE_IFELSE(
[AC_LANG_PROGRAM([[
#ifdef BZ_NO_TYPENAME
 #define typename
#endif

// Template-qualified base class specifier
// BZ_TEMPLATE_QUALIFIED_BASE_CLASS

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
AC_DEFINE([BZ_TEMPLATE_QUALIFIED_BASE_CLASS],[],[Template-qualified base class specifiers?])],
[AC_MSG_RESULT([no])])])


