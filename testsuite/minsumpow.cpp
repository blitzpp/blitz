#include "testsuite.h"
#include <blitz/array-only.h>
#include <blitz/array/ops.h>
#include <blitz/array/funcs.h>

BZ_USING_NAMESPACE(blitz)
BZ_USING_NAMESPACE(blitz::tensor)

int main()
{
    Array<float,2> A(4,4);
    Array<float,1> B(4), C(4);
    A = 0, 1, 2, 3,
        30, 2, 4, 1,
        3, 2, 5, 6,
        12, 9, 0, 0;

    B = sum(pow2(A),j);
    C =  14, 921, 74, 225;
    BZTEST(count(C == B) == 4);

    TinyVector<int,1> N = maxIndex(sum(pow2(A),j));
    BZTEST(N(0) == 1);

    return 0;
}
