// 'template' keyword qualifier
// BZ_TEMPLATE_KEYWORD_QUALIFIER

class Foo {
public:
    Foo() { };
    template<class T> static T convert() { return T(); }
};

template <typename T>
double f() {
    return Foo::template convert<double>();
}

int main()
{
    double z = f<double>();
    return 0;
}

