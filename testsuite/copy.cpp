#include "testsuite.h"
#include <blitz/array-only.h>
#include <blitz/array/ops.h>
#include <blitz/array/funcs.h>

BZ_USING_NAMESPACE(blitz)

int main()
{
    Array<int,1> A(1);
    A(0) = 5;
    Array<int,1> B(1);
    B = A;
}

