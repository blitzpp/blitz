#include <blitz/array-only.h>
#include <blitz/array/ops.h>
#include <blitz/array/funcs.h>

BZ_USING_NAMESPACE(blitz)

int main()
{
  Array<double,2> A(0,0);
  Array<double,2> B(0,0);

  firstIndex i;
  secondIndex j;

  B = A(j,i);

  return 0;
}

