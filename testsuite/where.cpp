#include "testsuite.h"
#include <blitz/array-only.h>
#include <blitz/array/ops.h>
#include <blitz/array/funcs.h>

BZ_USING_NAMESPACE(blitz)

int main()
{
    const int N = 5;
    Array<int,1> A(N), B(N), C(N), D(N), E(N);

    A =  0,  3, -2,  5, -4;
    B =  0,  1,  2,  3,  4;
    C = 10, 11, 12, 13, 14;

    D = where(A > 0, pow2(B), pow2(C));

    E =  100, 1, 144, 9, 196;

    BZTEST(count(D == E) == N);

    D = where(A > 0, A, 0);
    E = 0, 3, 0, 5, 0;

    BZTEST(count(D == E) == N);

    return 0;
}

