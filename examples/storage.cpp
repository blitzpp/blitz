/*****************************************************************************
 * storage.cpp        Blitz++ Array custom storage orders example
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

BZ_USING_NAMESPACE(blitz)

int main()
{
    // 3x3 C-style row major storage, base zero
    Array<int,2> A(3, 3);

    // 3x3 column major storage, base zero
    Array<int,2> B(3, 3, ColumnMajorArray<2>());

    // A custom storage format: 
    // Indices have range 0..3, 0..3
    // Column major ordering
    // Rows are stored ascending, columns stored descending
    GeneralArrayStorage<2> storage;
    storage.ordering() = firstRank, secondRank;
    storage.base() = 0, 0;
    storage.ascendingFlag() = true, false;

    Array<int,2> C(3, 3, storage);

    // Set each array equal to
    // [ 1 2 3 ]
    // [ 4 5 6 ]
    // [ 7 8 9 ]

    A = 1, 2, 3,
        4, 5, 6, 
        7, 8, 9;

    cout << "A = " << A << endl;

    // Comma-delimited lists initialize in memory-storage order only.
    // Hence we list the values in column-major order to initialize B:

    B = 1, 4, 7, 2, 5, 8, 3, 6, 9;

    cout << "B = " << B << endl;

    // Array C is stored in column major, plus the columns are stored
    // in descending order!

    C = 3, 6, 9, 2, 5, 8, 1, 4, 7;

    cout << "C = " << C << endl;

    Array<int,2> D(3,3);
    D = A + B + C;

#ifdef BZ_DEBUG
    A.dumpStructureInformation();
    B.dumpStructureInformation();
    C.dumpStructureInformation();
    D.dumpStructureInformation();
#endif

    cout << "D = " << D << endl;

    return 0;
}

