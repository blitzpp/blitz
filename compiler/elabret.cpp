#ifdef BZ_NO_TYPENAME
 #define typename
#endif


// Template-qualified return type, necessary for type promotion on vectors
// BZ_TEMPLATE_QUALIFIED_RETURN_TYPE

template<class X, class Y>
struct promote_trait {
    typedef X T;
};


template<>struct promote_trait<int, float> {
    typedef float T;
};

template<class T>
class Vector {
public:
    Vector() { }
};

template<class X, class Y>
Vector<typename promote_trait<X,Y>::T> operator+(const Vector<X>&, 
    const Vector<Y>&)
{ 
    return Vector<typename promote_trait<X,Y>::T>();
}

int main()
{
    Vector<int> x;
    Vector<float> y;
    Vector<float> z = x + y;
    return 0;
}

