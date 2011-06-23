#include "testsuite.h"
#include <blitz/array.h>

BZ_USING_NAMESPACE(blitz)

// tests that preexisting memory constructors work
int main()
{
  int p[] = {1,2,3,4,5,6,7,8,9};
  Array<int,2> a(p, shape(3,3), neverDeleteData);
  
  Array<int,2> b(3,3);
  b = 1,2,3,4,5,6,7,8,9;
  BZTEST(all(a==b));
    
    return 0;
}

