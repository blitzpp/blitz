

AC_DEFUN([AC_CXX_REINTERPRET_CAST],[
AC_MSG_CHECKING([whether $CXX accepts 'reinterpret_cast<>' ])
AC_COMPILE_IFELSE(
[AC_LANG_PROGRAM([[
// Reinterpret cast

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

class Unrelated {
public:
    Unrelated() { }

};

void foo(Unrelated&)
{ } 
]],[[
    Dalmation cairo;
    Dog& dog = cairo;
    Unrelated& eek = reinterpret_cast<Unrelated&>(dog);
    foo(eek);
    return 0;
]])],
[AC_MSG_RESULT([yes])
AC_DEFINE([BZ_REINTERPRET_CAST],[],[reinterpret_cast<>?])],
[AC_MSG_RESULT([no])])])

