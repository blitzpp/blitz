/*****************************************************************************
 * array.cpp        Blitz++ Array slicing & subarrays example
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

#include <blitz/array.h>

#ifdef BZ_NAMESPACES
using namespace blitz;
#endif

int main()
{
    Array<int,2> A(6,6), B(3,3);
  
    // Set the upper left quadrant of A to 5 
    A(Range(0,2), Range(0,2)) = 5; 

    // Set the upper right quadrant of A to an identity matrix
    B = 1, 0, 0,
        0, 1, 0,
        0, 0, 1;
    A(Range(0,2), Range(3,5)) = B;

    // Set the fourth row to 1

#ifdef BZ_PARTIAL_ORDERING
    A(3, Range::all()) = 1;
#else
    cout << "Warning: your compiler does not support partial ordering of"
         << endl << "member templates; using kludge." << endl;
    A(Range(3,3), Range::all()) = 1;
#endif

    // Set the last two rows to 0
    A(Range(4, toEnd), Range::all()) = 0;

    // Set the bottom right element to 8
    A(5,5) = 8;

    cout << "A = " << A << endl;

    return 0;
}

