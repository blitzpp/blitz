/*****************************************************************************
 * simple.cpp        Some simple array operations
 *
 * $Id$
 *
 * $Log$
 * Revision 1.2  2001/01/24 23:41:54  tveldhui
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

#ifdef BZ_NAMESPACES
using namespace blitz;
#endif

int main()
{
    Array<double,1> x(100);
    x = tensor::i;          // x = [ 0, 1, 2, ..., 99 ]

    Array<double,1> z(x + 150);
    Array<double,1> v(z + x * 2);

    cout << v << endl;
}

