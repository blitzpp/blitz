#include "testsuite.h"

#include <blitz/array.h>

using namespace blitz;

Array< double, 1> a(100); 

int main(){

  BZTEST(a.size() == 100);
  return 0;
}

