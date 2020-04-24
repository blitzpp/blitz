#include <blitz/array.h>

using namespace blitz;

int main()
{
}

void foo()
{
    const int N = 10;
    Array<float,1> A(N), B(N), C(N), D(N), E(N);
    A = B*C + D*E;
    A = B+C + D*cos(E);
    A = B*sin(C) + D*sin(E);
    B = C + D;
    A = A+B+C+D;
    A = B*pow2(C) + D*E;
    A = B-C + log(D)*cos(E);
    A = B*sin(C) + tan(D)/E;
    B = C - D;
    A = A+B*C+D;
}

