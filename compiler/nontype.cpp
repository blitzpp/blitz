// Test function templates with non-type parameters
// BZ_FUNCTION_NONTYPE_PARAMETERS

template<class T, int N>
class Foo {
};

template<class T, int N>
void showFoo(const Foo<T,N>& x)
{
}

int main()
{
    Foo<double, 17> z;
    showFoo(z);
    return 0;
}


