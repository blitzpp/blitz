#include <blitz/Array.h>
#include <blitz/array/stencil-et.h>

BZ_USING_NAMESPACE(blitz)
BZ_USING_NAMESPACE(blitz::tensor)

typedef Array<float,2> Array2D;

int main()
{
    // We'll work on arrays which are (2N+1) x (2N+1)
    const int N = 5;
    Range D(-N,+N);

    // Spatial domain is [-L,+L]
    double L = 1.0;

    // Resolution of grid: points are spaced at distance h
    double h = L / N;

    Array2D F(D,D), Lapl2(D,D), Lapl4(D,D), LaplExact(D,D);

    // Sample the function cos(x+y) on the grid

    F = cos((i+j) * h);

    // We'll use 4th order accurate stencils, which are
    // 5x5 stencils.  This means we need to leave a border
    // of 2 around the interior.  We can just make Fi an
    // alias for the interior of F, etc.
    Range Di(-N+2,N-2);
    Array2D Fi = F(Di,Di), Lapl2i = Lapl2(Di,Di),
      Lapl4i = Lapl4(Di,Di), LaplExacti = LaplExact(Di,Di);

    // Now we can apply the Laplacian2D4n stencil, which 
    // is a 4th-order accurate approximation to the Laplacian.
    // The "n" means "normalized", so the factor is h^2
    // instead of 12h^2.
    Lapl4i = Laplacian2D4n(Fi) / (h*h);

    // For comparison, we'll also do a 2nd-order accurate 
    // approximation.
    Lapl2i = Laplacian2D(Fi) / (h*h);

    // Compare to the exact Laplacian, which is -2 cos(x+y)
    LaplExact = -2 * cos((i+j) * h);

    cout << "Approximate O(h^2): " << Lapl2i << endl
         << "Approximate O(h^4): " << Lapl4i << endl
         << "Exact: " << LaplExacti << endl;

    cout << "Root-mean-square errors:" << endl
         << "2nd order approximation: " << sqrt(mean(sqr(LaplExacti-Lapl2i)))
         << endl
         << "4th order approximation: " << sqrt(mean(sqr(LaplExacti-Lapl4i)))
         << endl;

    return 0;
}

