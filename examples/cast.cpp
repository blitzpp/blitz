/*****************************************************************************
 * cast.cpp        Illustration of the cast() function
 *
 * $Id$
 *
 * $Log$
 * Revision 1.1  2000/06/19 12:26:17  tveldhui
 * Initial revision
 *
 * Revision 1.1  1997/07/16 19:38:23  tveldhui
 * Update: Alpha release 0.2 (Arrays)
 *
 *****************************************************************************
 */

#include <blitz/array.h>

#ifdef BZ_NAMESPACES
using namespace blitz;
#endif

int main()
{
    Array<int,1> A(4), B(4);
    Array<float,1> C(4);

    A = 1, 2, 3, 5;
    B = 2, 2, 2, 7;

    C = A / B;
    cout << C << endl;

    C = A / cast(B, float());
    cout << C << endl;

    return 0;
}

