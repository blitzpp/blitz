// Test member function templates #2: declaration of member templates outside
// the class.
// BZ_MEMBER_TEMPLATES_OUTSIDE_CLASS

template<class T, int N>
class Foo {

public:
    template<int N2>
    Foo<T,N> operator=(const Foo<T,N2>& z);
};

template<class T, int N> template<int N2>
Foo<T,N> Foo<T,N>::operator=(const Foo<T,N2>& z)
{
    return Foo<T,N>();
}

int main()
{
    Foo<double,4> x;
    Foo<double,7> y;
    x = y;

    return 0;
}

