/*****************************************************************************
 * array.cpp        Blitz++ Array stencilling example
 *
 * $Id$
 *
 * $Log$
 * Revision 1.3  2001/01/26 18:30:50  tveldhui
 * More source code reorganization to reduce compile times.
 *
 * Revision 1.2  2001/01/24 23:41:53  tveldhui
 * Widespread changes to reduce compile time.  For backwards
 * compatibility, #include <blitz/array.h> enables BZ_GANG_INCLUDE
 * mode which includes all array and vector functionality (about
 * 120000 lines of code).  #include <blitz/Array.h> includes
 * a minimal subset of Array funcitonality; other features must
 * be included explicitly.
 *
 * Revision 1.1.1.1  2000/06/19 12:26:17  tveldhui
 * Imported sources
 *
 * Revision 1.1  1997/07/16 19:38:23  tveldhui
 * Update: Alpha release 0.2 (Arrays)
 *
 *****************************************************************************
 */

#include <blitz/Array.h>   

#ifdef BZ_NAMESPACES
using namespace blitz;
#endif

int main()
{
    int N = 64;

    // Create three-dimensional arrays of float
    Array<float,3> A(N,N,N), B(N,N,N);

    // Set up initial conditions: +30 C over an interior block,
    // and +22 C elsewhere
    A = 22.0;

    Range interior(N/4,3*N/4);
    A(interior,interior,interior) = 30.0;

    int numIters = 301;

    Range I(1,N-2), J(1,N-2), K(1,N-2);

#ifdef BZ_HAVE_STD
#ifdef BZ_ARRAY_SPACE_FILLING_TRAVERSAL
    generateFastTraversalOrder(TinyVector<int,2>(N-2,N-2));
#endif
#endif

    for (int i=0; i < numIters; ++i)
    {
        double c = 1/6.5;
 
        B(I,J,K) = c * (.5 * A(I,J,K) + A(I+1,J,K) + A(I-1,J,K)
            + A(I,J+1,K) + A(I,J-1,K) + A(I,J,K+1) + A(I,J,K-1));

        A(I,J,K) = c * (.5 * B(I,J,K) + B(I+1,J,K) + B(I-1,J,K)
            + B(I,J+1,K) + B(I,J-1,K) + B(I,J,K+1) + B(I,J,K-1));

        // Output the result along a line through the centre
        for (int j=0; j < 8; ++j)
            cout << setprecision(2) << A(N/2,N/2,j*N/8) << " ";

        cout << endl;
        cout.flush();
    }

    return 0;
}

