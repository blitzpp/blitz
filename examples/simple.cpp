/*****************************************************************************
 * simple.cpp        Some simple vector operations
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

#include <blitz/vector.h>

#ifdef BZ_NAMESPACES
using namespace blitz;
#endif

int main()
{
    Vector<double> x = Range(0,100);

    Vector<double> z = x + 150;
    Vector<double> v = z + x * 2;

    cout << v << endl;
}

