#ifdef BZ_NO_TYPENAME
 #define typename
#endif


// BZ_USE_NUMTRAIT

template<class T_numtype>
class SumType {
public:
    typedef T_numtype T_sumtype;
};

template<>
class SumType<char> {
public:
    typedef int       T_sumtype;
};

template<class T>
class Vector {
};

template<class T>
Vector<typename SumType<T>::T_sumtype>
sum(Vector<T>)
{
    return Vector<typename SumType<T>::T_sumtype>();
}

int main()
{
    Vector<float> x;
    sum(x);
    return 0;
}

