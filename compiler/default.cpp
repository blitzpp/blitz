// Default template parameters
// BZ_DEFAULT_TEMPLATE_PARAMETERS

template<class T_type = double, int N = 10>
class foo {
public:
    int bar() const
    { return 0; }
};

int main()
{
    foo<float> z;
    return z.bar();
}

