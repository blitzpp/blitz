#include <blitz/array-only.h>
#include <blitz/array/ops.h>
#include <blitz/array/funcs.h>

BZ_USING_NAMESPACE(blitz)

int module2()
{
    BZ_USING_NAMESPACE(blitz::tensor)

    Array<int,1> A(4);
    A = pow2(i);
    return 0;
}

