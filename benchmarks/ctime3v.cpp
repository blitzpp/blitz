#include <valarray>

using namespace std;

int main()
{
}

void foo()
{
    const int N = 10;
    valarray<float> A(N), B(N), C(N), D(N), E(N);
    A = B*C + D*E;
    A = B+C + D*cos(E);
    A = B*sin(C) + D*sin(E);
    B = C + D;
    A = A+B+C+D;
}

