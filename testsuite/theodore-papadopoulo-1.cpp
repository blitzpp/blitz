#include "testsuite.h"
#include <blitz/array-only.h>
#include <blitz/array/ops.h>
#include <blitz/array/funcs.h>

BZ_USING_NAMESPACE(blitz)

int main()
{
    Array<double,1> F(4);

    F = -1.0, -2.0, -3.0, -4.0;

    TinyVector<int,1> i = maxIndex(F);
    float f = max(F);

    BZTEST(i[0] == 0);
    BZTEST(f == -1.0);
    return 0;
}

