/*****************************************************************************
 * pick.cpp          Blitz++ VectorPick example
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

#include <blitz/Vector.h>
#include <blitz/vecpick.h>

#ifdef BZ_NAMESPACES
using namespace blitz;
#endif

int main()
{                                         //   0  1  2  3        8  9
    Vector<float> x = sqr(Range(0,9));    // [ 0  1  4  9  ...  64 81 ]
    cout << x << endl;

    Vector<int> index(3);   
    index[0] = 2;
    index[1] = 5;  
    index[2] = 7;

    VectorPick<float> y(x, index);        //    2  5  7 
    cout << y << endl;                    // [  4 25 49 ]

    y = 0;                                //    0  1  2  3  4  5  6  7  8  9
    cout << x << endl;                    // [  0  1  0  9 16  0 36  0 64 81 ]

    y += sin(Range(0,2));

    return 0;
}

