/*****************************************************************************
 * rangexpr.cpp        Blitz++ range expression example
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

#ifndef M_PI
 #define M_PI   3.14159265358979323846
#endif

int main()
{
    Vector<float> x = cos(Range(0,7) * (2.0 * M_PI / 8));

    cout << x << endl;

    return 0;
}

