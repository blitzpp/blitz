#include "testsuite.h"

#include <blitz/tinymat.h>

BZ_USING_NAMESPACE(blitz)

int main()
{
    TinyMatrix<int,2,3> A;
    A = 7;
    BZTEST(A(1,2) == 7);
    BZTEST(A(0,0) == 7);

    A = 0, 1, 2,
        2, 3, 4;
    BZTEST(A(0,0) == 0);
    BZTEST(A(1,2) == 4);

    return 0;
}

