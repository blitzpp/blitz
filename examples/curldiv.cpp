// Div, grad, curl and all that

#include <blitz/array.h>
#include <blitz/tinyvec.h>

BZ_USING_NAMESPACE(blitz)
BZ_USING_NAMESPACE(blitz::tensor)

BZ_DECLARE_STENCIL8(test,Ax,Ay,Az,curlA,divA,gradAx,gradAy,gradAz)
    curlA = curl(Ax,Ay,Az);
    divA = div(Ax,Ay,Az);
    gradAx = grad3D(Ax);
    gradAy = grad3D(Ay);
    gradAz = grad3D(Az);
BZ_STENCIL_END

int main()
{
    Array<float,3> Ax, Ay, Az, divA;
    Array<TinyVector<float,3>,3> gradAx, gradAy, gradAz, curlA;
    const int N = 40;
    allocateArrays(shape(N,N,N), Ax, Ay, Az, divA);
    allocateArrays(shape(N,N,N), gradAx, gradAy, gradAz, curlA);

    Array<float,1> cx(N), cy(N), cz(N);
    float h = 1.0 / (N-1);

    cx = h * i;
    cy = h * i;
    cz = h * i;

    Ax = cos(cx(i)) + cos(cy(j)) + cos(cz(k));
    Ay = sin(cx(i)) + sin(cy(j)) + sin(cz(k));
    Az = exp(cx(i)) + exp(cy(j)) + exp(cz(k));

    applyStencil(test(), Ax, Ay, Az, curlA, divA, gradAx, gradAy, gradAz);
}

