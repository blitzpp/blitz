#include "testsuite.h"
#include <blitz/array.h>

BZ_USING_NAMESPACE(blitz)

// tests that we get the warning message when using preexisting data
// constructors
int main()
{
  const int w=simdTypes<float>::vecWidth;

  if(w==1) return 0;

  const int sz=2*w+1;
  float* p = new float[sz*sz];

#if BZ_PAD_ARRAYS
  cout << "This should give a warning:\n";
  Array<float,2> a(p, shape(sz,sz), neverDeleteData);

  cout << "This should not:\n";
  Array<float,2> b(p, shape(2*w,2*w), neverDeleteData);
#endif

  cout << "Done\n";
  delete[] p;
    
    return 0;
}

