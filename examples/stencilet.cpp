#include <blitz/array.h>
#include <blitz/array/stencil-et.h>

using namespace blitz;

int main()
{
    Array<float,2> A(Range(-7,7),Range(-7,7)), B(Range(-7,7),Range(-7,7));
    A = 0.0;
    A(0,0) = 1;
    B = 0.0;

    Range I(-5,5), J(-5,5);

    Array<float,2> Ai = A(I,J), Bi = B(I,J);

    Bi = Laplacian2D4n(Ai) * 0.1;

    cout << Bi << endl;
}

