// 'template' keyword qualifier
// BZ_TEMPLATE_KEYWORD_QUALIFIER

class Foo {
public:
    Foo() { };
    template<class T> static T convert() { return T(); }
};

int main()
{
    double z = Foo::template convert<double>();
    return 0;
}

