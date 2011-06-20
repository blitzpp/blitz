#include "testsuite.h"
#include <blitz/array.h>

BZ_USING_NAMESPACE(blitz)

template<typename T_numtype, int N, int M>
void testalign() {
  BZTEST(__alignof__(TinyVector<T_numtype,N>)==simdTypes<T_numtype>::byteWidth);
  BZTEST(__alignof__(TinyMatrix<T_numtype,N,M>)==simdTypes<T_numtype>::byteWidth);

  const int w=simdTypes<T_numtype>::vecWidth;
  BZTEST(sizeof(TinyVector<T_numtype,N>)==(N/w + (N%w?1:0))*w*sizeof(T_numtype));
  BZTEST(sizeof(TinyMatrix<T_numtype,N,M>)==(N*M/w + (N*M%w?1:0))*w*sizeof(T_numtype));
}

int main()
{
// test that TinyVector and TinyMatrix are aligned properly.
  testalign<int,1,1>();
  testalign<int,2,2>();
  testalign<int,3,2>();
  testalign<int,4,2>();
  testalign<int,5,2>();
  testalign<int,6,2>();
  testalign<int,7,2>();

  testalign<float,1,2>();
  testalign<float,2,2>();
  testalign<float,3,2>();
  testalign<float,4,2>();
  testalign<float,5,2>();
  testalign<float,6,2>();
  testalign<float,7,2>();

  testalign<double,1,2>();
  testalign<double,2,2>();
  testalign<double,3,2>();
  testalign<double,4,2>();
  testalign<double,5,2>();
  testalign<double,6,2>();
  testalign<double,7,2>();

  const int w=simdTypes<float>::vecWidth;
  if(w>1) {
    // test that arrays correctly report as being aligned or not.
    Array<float, 2> A(3*w,3*w);
    BZTEST(A.isVectorAligned(0));
    Array<float,1> B(A(1,Range::all()));
    BZTEST(B.isVectorAligned(0));
    BZTEST(!A(Range::all(),1).isVectorAligned(0));
    BZTEST(B(Range(w,2*w-1)).isVectorAligned(0));
    BZTEST(!B(Range(1,2*w-1)).isVectorAligned(0));
    BZTEST(B(Range(1,2*w-1)).isVectorAligned(w-1));

    // test that expressions correctly report as being aligned or not
    BZTEST((A(1,Range::all())*B).isVectorAligned(0));
    BZTEST(!(A(Range::all(),1)*B).isVectorAligned(0));
    BZTEST((A(Range::all(),1)*B(Range(1,2*w-1))).isVectorAligned(w-1));

    // test that we don't overwrite the end of aligned but uneven-length arrays
    B=0;
    B(Range(0,0))=1;
    BZTEST(sum(B)==1);
    B(Range(0,w))=1;
    BZTEST(sum(B)==w+1);
  }
    

  return 0;
}

