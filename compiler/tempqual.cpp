// Explicit template function qualification
// BZ_EXPLICIT_TEMPLATE_FUNCTION_QUALIFICATION

template<class Z>
class Vector {
public:
    Vector() { }
};


template<class X, class Y>
Vector<X> to(const Vector<Y>&)
{
    return Vector<X>();
}

int main()
{
    Vector<float> x;
    Vector<double> y = to<double>(x);
    return 0;
}

