#include "testsuite.h"
#include <blitz/Array.h>

BZ_USING_NAMESPACE(blitz)

int main()
{
    Array<int,1> A(16384);
    int* data = A.data();

    Array<int,1> B(A);
    A.free();
    BZTEST(A.data() == 0);
    BZTEST(A.extent(0) == 0);
    B = 0;   // If A's data was accidentally freed, then will hopefully
             // cause a segment violation
   
    B.free();
    BZTEST(B.data() == 0);
    BZTEST(B.extent(0) == 0);

    return 0;
}

