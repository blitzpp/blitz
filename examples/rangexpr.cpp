/*****************************************************************************
 * rangexpr.cpp        Blitz++ range expression example
 *
 * $Id$
 *
 * $Log$
 * Revision 1.3  2002/07/02 19:49:02  jcumming
 * Updated to use new header file names that avoid capitalization.
 *
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

#include <blitz/vector-et.h>

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

