#include <blitz/Array.h>

BZ_USING_NAMESPACE(blitz)

/*
 * This example program illustrates the "stencil objects", which provide
 * a cleaner notation for finite differencing.  The example is solving
 * the 3D acoustic wave propagation problem.  Three arrays (P1,P2,P3)
 * contain the pressure field at three consecutive time steps.  The
 * c array contains the conduction velocity.
 *
 * Without stencil objects, the stencil would be implemented like this:
 *
 *    Range I(1,N-2), J(1,N-2), K(1,N-2);
 *
 *    P3(I,J,K) = (2-6*c(I,J,K)) * P2(I,J,K)
 *      + c(I,J,K)*(P2(I-1,J,K) + P2(I+1,J,K) + P2(I,J-1,K) + P2(I,J+1,K)
 *      + P2(I,J,K-1) + P2(I,J,K+1)) - P1(I,J,K);
 */

/*
 * To declare a stencil object, we use the macro BZ_DECLARE_STENCIL?,
 * where in this case ? is set to 4 (there are 4 arrays involved in the
 * stencil).  The notation is greatly simplified by using the
 * Laplacian3D stencil operator, which is provided by Blitz++.
 */

BZ_DECLARE_STENCIL4(acoustic3D_stencil,P1,P2,P3,c)
  P3 = 2 * P2 + c * Laplacian3D(P2) - P1;
BZ_END_STENCIL

/*
 * The above stencil is very simple.  In general, a stencil object
 * can contain multiple assignment statements, and call other functions.
 * For example, here is a more complicated version of the above stencil,
 * which simulates acoustic waves propagating through a medium whose
 * density is gradually decreasing in response to pressure (but only where 
 * the conduction velocity is less than 0.5).  This is completely
 * nonsensical, but illustrates what you can do in a stencil:
 *
 * BZ_DECLARE_STENCIL4(myStencil, P1,P2,P3,c)
 *   P3 = 2 * P2 + c * Laplacian3D(P2) - P1;
 *   if (c < 0.5)
 *      c = c * (1.0 - exp(- abs(P3)))
 * BZ_END_STENCIL
 */

int main()
{
    Array<float,3> P1, P2, P3, c;
    const int N = 64;
    allocateArrays(shape(N,N,N), P1, P2, P3, c);

    // Initial conditions: obviously in a real application these
    // wouldn't be zeroed...
    P1 = 0;
    P2 = 0;
    P3 = 0;
    c = 0;

    const int nIterations = 10;

    for (int i=0; i < nIterations; ++i)
    {
        // Apply the stencil object to the arrays
        applyStencil(acoustic3D_stencil(), P1, P2, P3, c);

        // Set [P1,P2,P3] <- [P2,P3,P1] to set up for the next
        // time step
        cycleArrays(P1,P2,P3);
    }

    return 0;
}

