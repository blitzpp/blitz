

AC_DEFUN([AC_CXX_STATIC_CAST],[AC_MSG_CHECKING([whether $CXX accepts 'static_cast<>' ])
AC_COMPILE_IFELSE(
[AC_LANG_PROGRAM([[
// static_cast

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

void foo(Dalmation&)
{ }
]],[[
    Dalmation cairo;
    Dog& dog = cairo;

    Dalmation& spotted = static_cast<Dalmation&>(dog);
    foo(spotted);

    return 0;
]])],
[AC_MSG_RESULT([yes])
AC_DEFINE([BZ_STATIC_CAST],[],[static_cast<>?])],
[AC_MSG_RESULT([no])])])


