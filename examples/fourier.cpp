#include <blitz/array.h>

BZ_USING_NAMESPACE(blitz)

int main()
{
    int N = 16, M = 16;

    BZ_USING_NAMESPACE(blitz::tensor);

    Array<complex<float>,2> A(N,M);
    A = cexpi((2*M_PI/N) * i) * cexpi((2*M_PI/M) * j);

    cout << A << endl;
}

