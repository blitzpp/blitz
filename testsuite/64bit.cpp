#include "testsuite.h"
#include <blitz/array.h>

BZ_USING_NAMESPACE(blitz)

int main()
{
  // test 64-bit compatibility if enabled
  if(sizeof(sizeType)>4) {

    // wrap in try so we can catch allocation failure if test platform
    // has insufficient memory. To minimize memory reqs we use arrays
    // of char, but we still need at least 4GB.
    Array<unsigned char,4> test;
    try {
      test.resize(shape(256,256,256,256));
    }
    catch (std::bad_alloc&) {
      cerr << "Allocation failure - not enough memory to test 64-bit compatibility\n";
      return 0;
    }

    cout << "Testing 64-bit compatibility. Be patient, large operations in progress...\n";
    // these things take forever in debug mode without optimization,
    // so we only do one thing
    test=tensor::i;
    test=1*test;
    BZTEST(all(test==tensor::i));
    test.free();

#ifdef BZ_FULLY64BIT
    // test arrays with long dimensions
    Array<char, 1> test2(1<<32);
    test2 = 1;
    BZTEST(sum(test2)==1<<32);
    test2.free();
#endif
  }
  else {
    cout << "Not a 64-bit machine, can't test 64-bit compatibility.\n";
  }

  return 0;
}

