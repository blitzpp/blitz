// Where are those pesky math functions?
// BZ_COMPLEX_MATH_IN_NAMESPACE_STD

#include <complex>

namespace blitz {
    using namespace std;

    complex<float> pow(complex<float> x, complex<float> y)
    { return std::pow(x,y); }
};

int main()
{
    using namespace blitz;
    complex<float> x = 1.0, y = 1.0;
    blitz::pow(x,y);
    return 0;
}

