// Div, grad, curl and all that

#include <blitz/array-only.h>
#include <blitz/array/ops.h>
#include <blitz/array/funcs.h>
#include <blitz/array/stencils.h>

BZ_USING_NAMESPACE(blitz)
BZ_USING_NAMESPACE(blitz::tensor)

BZ_DECLARE_STENCIL6(test,Ax,Ay,Az,R1,R2,R3)
    TinyVector<float,3> curlA = curl(Ax,Ay,Az);
    float divA = div(Ax,Ay,Az);
    TinyVector<float,3> gradAx = grad3D(Ax);
    TinyVector<float,3> gradAy = grad3D(Ay);
    TinyVector<float,3> gradAz = grad3D(Az);
BZ_STENCIL_END

int main()
{
    Array<float,3> Ax, Ay, Az, R1, R2, R3;
    const int N = 40;
    allocateArrays(shape(N,N,N), Ax, Ay, Az, R1, R2, R3);

    Array<float,1> cx(N), cy(N), cz(N);
    float h = 1.0 / (N-1);

    cx = h * i;
    cy = h * i;
    cz = h * i;

    Ax = cos(cx(i)) + cos(cy(j)) + cos(cz(k));
    Ay = sin(cx(i)) + sin(cy(j)) + sin(cz(k));
    Az = exp(cx(i)) + exp(cy(j)) + exp(cz(k));

    applyStencil(test(), Ax, Ay, Az, R1, R2, R3);
}

