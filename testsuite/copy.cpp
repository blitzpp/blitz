#include "testsuite.h"
#include <blitz/Array.h>

BZ_USING_NAMESPACE(blitz)

int main()
{
    Array<int,1> A(1);
    A(0) = 5;
    Array<int,1> B(1);
    B = A;
}

