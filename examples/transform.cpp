#include <blitz/TinyMat.h>
#include <blitz/TinyVec.h>

#ifdef BZ_NAMESPACES
using namespace blitz;
#endif

int main()
{
    cout << "This example is interesting only for the code generated."
         << endl;
    return 0;
}

/*
 * Blitz++ version
 */
void transform(double alpha, TinyVector<double,3>& x, 
    const TinyVector<double,3>& y)
{
    TinyMatrix<double,3,3> C;

    double cosa = cos(alpha),
           sina = sin(alpha);

    // Create the principal rotation matrix C_3(alpha)
    C = cosa, -sina,   0.0,
        sina,  cosa,   0.0,
         0.0,   0.0,   1.0;

    x = product(C,y);
}

/*
 * Low level version
 */
void transform2(double alpha, double* x, double* y)
{
    double c = cos(alpha),
           s = sin(alpha);

    x[0] = c * y[0] - s * y[1];
    x[1] = s * y[0] + c * y[1];
    x[2] = y[2];
}

