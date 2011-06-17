#include "testsuite.h"
#include <blitz/array.h>

BZ_USING_NAMESPACE(blitz)

int main()
{
  const int w = simdTypes<int>::vecWidth;
  if (w>1)
    cerr << "NOTE: This test assumes that a freshly created array is always contiguous, but\nthis is not the case when a simd width is set. The test has been altered to\nnot fail by setting all dimensions to even multiples of the simd width.\n";
  {
    Array<int, 2> A(3*w,6*w);
    BZTEST(A.isStorageContiguous());

    BZTEST(!(A(Range(fromStart, toEnd, 2), 
        Range::all())).isStorageContiguous());
    BZTEST(A.reverse(firstDim).isStorageContiguous());
    BZTEST(A.reverse(secondDim).isStorageContiguous());
    BZTEST(!A(Range::all(), 2*w).isStorageContiguous());
    BZTEST(A(2*w, Range::all()).isStorageContiguous());
  }

  {
    Array<int, 2> A(3*w,6*w,columnMajorArray);
    BZTEST(A.isStorageContiguous());

    BZTEST(!(A(Range(fromStart, toEnd, 2), 
        Range::all())).isStorageContiguous());
    BZTEST(A.reverse(firstDim).isStorageContiguous());
    BZTEST(A.reverse(secondDim).isStorageContiguous());
    BZTEST(A(Range::all(), 2*w).isStorageContiguous());
    BZTEST(!A(2*w, Range::all()).isStorageContiguous());
  }

  {
    Array<int, 2> A(Range(-2*w,4*w-1),Range(2*w,14*w-1));
    BZTEST(A.isStorageContiguous());

    BZTEST(!(A(Range(fromStart, toEnd, 2), 
        Range::all())).isStorageContiguous());
    BZTEST(A.reverse(firstDim).isStorageContiguous());
    BZTEST(A.reverse(secondDim).isStorageContiguous());
    BZTEST(!A(Range::all(), 2*w).isStorageContiguous());
    BZTEST(A(2*w, Range::all()).isStorageContiguous());
  }
}
