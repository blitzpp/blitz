/*
 * This test program verifies that multi-module programs will compile
 * and link properly.
 */

#include <blitz/array-only.h>
#include <blitz/array/ops.h>

BZ_USING_NAMESPACE(blitz)

int module2();

int main()
{
    BZ_USING_NAMESPACE(blitz::tensor)

    Array<float,2> A(4,4);
    A = 1.0 / (1 + i + j);

    float r = sum(A);
    return module2();
}

