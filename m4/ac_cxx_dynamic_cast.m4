

AC_DEFUN([AC_CXX_DYNAMIC_CAST],[AC_MSG_CHECKING([whether $CXX accepts 'dynamic_cast<>'])
AC_COMPILE_IFELSE(
[AC_LANG_PROGRAM([[
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
    Dalmation cairo;
    Dog& doggie = cairo;

    if (dynamic_cast<Dalmation*>(&doggie))
    {
        return 0;
    }

    return 1;
]])],
[AC_MSG_RESULT([yes])
AC_DEFINE([BZ_DYNAMIC_CAST],[],[dynamic_cast<>?])],
[AC_MSG_RESULT([no])])])


