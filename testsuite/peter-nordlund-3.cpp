#include "testsuite.h"
#include <blitz/array.h>

BZ_USING_NAMESPACE(blitz)

int main()
{
    Array<int,2> A(3,3);
    A = 3, 5, 8,
        2, 4, 9,
        1, 0, 1;

    TinyVector<int,2> minpos = minIndex(A);

    BZTEST(minpos(0) == 2);
    BZTEST(minpos(1) == 1);

    minpos = minIndex(sqr(A));
    BZTEST(minpos(0) == 2);
    BZTEST(minpos(1) == 1);

    TinyVector<int,2> maxpos = maxIndex(A);
    BZTEST(maxpos(0) == 1);
    BZTEST(maxpos(1) == 2);

    maxpos = maxIndex(sqr(A));
    BZTEST(maxpos(0) == 1);
    BZTEST(maxpos(1) == 2);
}

