#include "testsuite.h"
#include <blitz/Array.h>

BZ_USING_NAMESPACE(blitz)

int main()
{
  {
    Array<int, 2> A(7,11);
    BZTEST(A.isStorageContiguous());

    BZTEST(!(A(Range(fromStart, toEnd, 2), 
        Range::all())).isStorageContiguous());
    BZTEST(A.reverse(firstDim).isStorageContiguous());
    BZTEST(A.reverse(secondDim).isStorageContiguous());
    BZTEST(!A(Range::all(), 4).isStorageContiguous());
    BZTEST(A(4, Range::all()).isStorageContiguous());
  }

  {
    Array<int, 2> A(7,11,fortranArray);
    BZTEST(A.isStorageContiguous());

    BZTEST(!(A(Range(fromStart, toEnd, 2), 
        Range::all())).isStorageContiguous());
    BZTEST(A.reverse(firstDim).isStorageContiguous());
    BZTEST(A.reverse(secondDim).isStorageContiguous());
    BZTEST(A(Range::all(), 4).isStorageContiguous());
    BZTEST(!A(4, Range::all()).isStorageContiguous());
  }

  {
    Array<int, 2> A(Range(-4,8),Range(4,27));
    BZTEST(A.isStorageContiguous());

    BZTEST(!(A(Range(fromStart, toEnd, 2), 
        Range::all())).isStorageContiguous());
    BZTEST(A.reverse(firstDim).isStorageContiguous());
    BZTEST(A.reverse(secondDim).isStorageContiguous());
    BZTEST(!A(Range::all(), 4).isStorageContiguous());
    BZTEST(A(4, Range::all()).isStorageContiguous());
  }
}
