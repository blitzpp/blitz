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

int main()
{
    keyboard x;
    int z = x.getkey();

    music::keyboard y;
    y.playNote(z);

    using namespace music::foo;
    Xeg(z);

    return 0;
}

