// numeric_limits<T> class

#include <limits>

#ifndef BZ_NO_NAMESPACES
using namespace std;
#endif

int main()
{
    double e = numeric_limits<double>::epsilon();
    return 0;
}

