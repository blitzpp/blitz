// Special syntax for full specialization

template<class T>
class foo {
public:
    int bar() const
    { return 1; }
};

template<>
class foo<float> {
public:
    int bar() const
    { return 0; }
};

int main()
{
    foo<float> z;
    return z.bar();
}

