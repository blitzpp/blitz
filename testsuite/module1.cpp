/*
 * This test program verifies that multi-module programs will compile
 * and link properly.
 */

#include <blitz/array.h>

using namespace blitz;

int module2();

int main()
{
    using namespace blitz::tensor;

    Array<float,2> A(4,4);
    A = 1.0 / (1 + i + j);

    sum(A);
    return module2();
}

