// Check blitz/minmax.h, which provides a templated, type-promoting
// version of min(a,b) and max(a,b).

#include "testsuite.h"
#include <blitz/minmax.h>

BZ_USING_NAMESPACE(blitz)
BZ_USING_NAMESPACE(blitz::minmax)

int main()
{
    double a = 1.0;
    float b = 2.0;
    int c = 3;

    BZTEST(int(min(a,b)) == 1);
    BZTEST(int(max(a,b)) == 2);
    BZTEST(int(min(a,c)) == 1);
    BZTEST(int(min(b,c)) == 2);
    BZTEST(int(max(b,c)) == 3);
    BZTEST(int(max(a,c)) == 3);

    return 0;
}

