#include "testsuite.h"
#include <blitz/array.h>

BZ_USING_NAMESPACE(blitz)

// Tests that operations on multicomponent arrays work as
// expected. This is a bit tricky because now they involve two
// recursive ET applications.

typedef Array<TinyVector<double, 2>, 1> array_1v;

int main()
{
  // create some arrays to operate on
  const int sz=5;

  array_1v a(sz),b(sz);
  a=1,2,3,4,5;

  cout << a << endl;

  a *= 2;

  cout << a << endl;

  a *= scalar(TinyVector<double, 2>(0.5,-0.5));

  cout << a << endl;

  b = -a;

  cout << b << endl;

    return 0;
}

