#ifdef BZ_NO_TYPENAME
 #define typename
#endif

// BZ_TEMPLATE_SCOPED_ARGUMENT_MATCHING
template<class X>
class A {
public:
    typedef X W;
};

template<class Y>
class B {

};

template<class Y>
void operator+(B<Y> d1, typename Y::W d2)
{
}

int main()
{
    B<A<float> > z;
    z + 0.5f;     //        match +(B<A<float>>, A<float>::W)
                  //              +(B<A<float>>, float)       ...?
    return 0;
}

