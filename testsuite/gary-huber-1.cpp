#include "testsuite.h"

#include <blitz/array-only.h>
#include <blitz/array/ops.h>
#include <blitz/array/funcs.h>

BZ_USING_NAMESPACE(blitz)

Array< double, 1> a(100); 

int main(){

  BZTEST(a.size() == 100);
  return 0;
}

