
AC_DEFUN([AC_CXX_RTTI],[AC_MSG_CHECKING([whether $CXX has run-time type identification])
AC_COMPILE_IFELSE(
[AC_LANG_PROGRAM([[
#include <typeinfo>

class Dog {
public:
    Dog() { }
    virtual void fetch() = 0;
};

class Dalmation : public Dog {
public:
    Dalmation() { }
    virtual void fetch();
};

void Dalmation::fetch()
{
}
]],[[
    Dalmation z;
    Dog* y = &z;

    if (typeid(*y) == typeid(Dalmation))
    {
        return 0;
    }

    return 1;
]])],
[AC_MSG_RESULT([yes])
AC_DEFINE([BZ_RTTI],[],[Run-Time Type Identification ?])],
[AC_MSG_RESULT([no])])])


