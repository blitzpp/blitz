// Member constants

class Foo {
public:
    static const int value = 0;
};

const int Foo::value;

int main()
{
    return Foo::value;
}

