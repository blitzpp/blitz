/*****************************************************************************
 * outer.cpp        Blitz++ outer product (tensor notation) example
 *
 * $Id$
 *
 * $Log$
 * Revision 1.2  2001/01/26 18:30:51  tveldhui
 * More source code reorganization to reduce compile times.
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
    Array<float,1> x(4), y(4);
    Array<float,2> A(4,4);

    x = 1, 2, 3, 4;
    y = 1, 0, 0, 1;

    firstIndex i;
    secondIndex j;

    A = x(i) * y(j);

    cout << A << endl;

    return 0;
}

