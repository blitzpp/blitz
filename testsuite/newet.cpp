#define BZ_NEW_EXPRESSION_TEMPLATES

#include "testsuite.h"
#include <blitz/array.h>

BZ_USING_NAMESPACE(blitz)

int main()
{
    Array<int,1> A(4), B(4), C(4), D(4);
    C = 0, 1, 2, 3;
    B = 5, 6, 7, 8;
    A = B + C;
    D = 5, 7, 9, 11;
    BZTEST(count(D==A)==4);

    A = 3 * tensor::i;
    D = 0, 3, 6, 9;
    BZTEST(count(D==A)==4);

    A = 3.0 * tensor::i;
    D = 0, 3, 6, 9;
    BZTEST(count(D==A)==4);

    A = tensor::i * 3.0;
    BZTEST(count(D==A)==4);

    A = 3;
    BZTEST(count(A==3)==4);

    A = tensor::i;
    BZTEST(count(A==C)==4);
}

