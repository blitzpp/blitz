#include "testsuite.h"
#include <blitz/array.h>

BZ_USING_NAMESPACE(blitz)

int main()
{
  const int w=simdTypes<double>::vecWidth;
  if(w>1)
    cerr << "NOTE:This test makes assumptions about storage that are not true when a SIMD\nwidth is specified. The test has been altered to not fail.\n";

    Array<int,3> A(2*w,3*w,4*w);

//    A.dumpStructureInformation();

    A.transposeSelf(secondDim, thirdDim, firstDim);

    BZTEST(A.ordering(0) == 1 && A.ordering(1) == 0 && A.ordering(2) == 2);
    BZTEST(A.length(0) == 3*w && A.length(1) == 4*w && A.length(2) == 2*w);
    BZTEST(A.stride(0) == 4*w && A.stride(1) == 1 && A.stride(2) == 12*w*w);

//    A.dumpStructureInformation();

    Array<int,2> B(3,3);
    B = 0, 1, 2,
        3, 4, 5,
        6, 7, 8;

//    cout << B << endl;

    B.transposeSelf(secondDim, firstDim);
    Array<int,2> C(3,3);
    C = 0, 3, 6,
        1, 4, 7,
        2, 5, 8;
    BZTEST(count(B==C) == 9);

//    cout << B << endl;

    Array<int,2> D(3,3,FortranArray<2>());
    D = 0, 1, 2,
        3, 4, 5,
        6, 7, 8;
    D.transposeSelf(secondDim, firstDim);
    Array<int,2> E(3,3,FortranArray<2>());
    E = 0, 3, 6,
        1, 4, 7,
        2, 5, 8;
    BZTEST(count(D==E) == 9);

    return 0;
}

