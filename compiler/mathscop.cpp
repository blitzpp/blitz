// Where are those pesky math functions?
// BZ_MATH_FN_IN_NAMESPACE_STD

#include <cmath>

namespace blitz {
    double pow(double x, double y)
    { return std::pow(x,y); }
};

int main()
{
    using namespace blitz;
    double x = 1.0, y = 1.0;
    blitz::pow(x,y);
    return 0;
}


