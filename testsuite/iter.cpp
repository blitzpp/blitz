#include "testsuite.h"
#include <blitz/array-only.h>
#include <blitz/array/ops.h>
#include <blitz/array/funcs.h>

BZ_USING_NAMESPACE(blitz)

void check(const Array<int,2>& A, const Array<int,1>& b)
{
    int i = 0;
    Array<int,2>::const_iterator iter = A.begin(), end = A.end();
    while (iter != end)
    {
        BZTEST((*iter) == b(i++));
        ++iter;
    }
    BZTEST(i == A.numElements());
}

int main()
{
  {
    Array<int,2> A(2,3);
    A = 0, 1, 2,
        3, 4, 5;
    Array<int,1> b(6);
    b = 0, 1, 2, 3, 4, 5;

    check(A, b);
  }

  {
    Array<int,2> A(2,3,FortranArray<2>());
    A = tensor::i * 3 + tensor::j;
    Array<int,1> b(6);
    b = 4, 7, 5, 8, 6, 9;
    check(A,b);
  }

#if 0
  {
    Array<int,2> B(5,5,FortranArray<2>());
    B = tensor::i + 5 * tensor::j;

    B.reverseSelf(1);
    check(B);
  }
#endif

  {
    Array<int,2> B(6,6,FortranArray<2>());
    B = tensor::i * 6 + tensor::j;
    Array<int,1> b(12);
    b = 7, 13, 19, 8, 14, 20, 9, 15, 21, 10, 16, 22;
    check(B(Range(1,3),Range(1,4)), b);
  }

  {
    Array<int,2> B;
    Array<int,2>::iterator iter = B.begin(), end = B.end();
    BZTEST(iter == end);
  }

}

