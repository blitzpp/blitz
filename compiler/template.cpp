// Basic templates

template<class T>
class Vector {
public:
    Vector() { }
};

template<class T>
void foo(const Vector<T>& )
{ }

int main()
{
    Vector<float> x;
    Vector<int> z;
    foo(x);
    foo(z);
    return 0;
}

