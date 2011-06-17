#include "testsuite.h"
#include <blitz/array.h>

BZ_USING_NAMESPACE(blitz)

// test that TinyVector and TinyMatrix are aligned properly.
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

  return 0;
}

