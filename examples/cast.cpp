/*****************************************************************************
 * cast.cpp        Illustration of the cast() function
 *
 * $Id$
 *
 * $Log$
 * Revision 1.2  2001/01/24 23:41:53  tveldhui
 * Widespread changes to reduce compile time.  For backwards
 * compatibility, #include <blitz/array.h> enables BZ_GANG_INCLUDE
 * mode which includes all array and vector functionality (about
 * 120000 lines of code).  #include <blitz/array-only.h> includes
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

#include <blitz/array-only.h>
#include <blitz/array/ops.h>
#include <blitz/array/funcs.h>

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

