


AC_DEFUN([AC_CXX_NAMESPACE],[AC_MSG_CHECKING([whether $CXX implement namespaces])
AC_COMPILE_IFELSE(
[AC_LANG_PROGRAM([[
// BZ_NAMESPACES

namespace computers {

class keyboard {
  public:
    int getkey() const;
};

int keyboard::getkey() const
{
    return 0;
}

}

namespace music {

class keyboard {
  public:
    void playNote(int note);
};

}

namespace music {

void keyboard::playNote(int note)
{
}

namespace foo {
  template<class T> void Xeg(T) { }
}

}

using namespace computers;
]], [[
    keyboard x;
    int z = x.getkey();

    music::keyboard y;
    y.playNote(z);

    using namespace music::foo;
    Xeg(z);

    return 0;
]])],
[AC_MSG_RESULT([yes])
AC_DEFINE([BZ_NAMESPACES],[],[Does your compiler implement namespaces?])],
[AC_MSG_RESULT([no])])])


