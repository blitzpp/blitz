#include "testsuite.h"
#include <blitz/array.h>
//#include <blitz/array.cc>
#include <blitz/tinyvec2.cc>
#include <blitz/array/asexpr.cc>
#include <blitz/array/ops.h>
#include <blitz/array/ops.cc>
#include <blitz/array/fastiter.h>
#include <blitz/array/methods.cc>
#include <blitz/array/methods.cc>
#include <blitz/array/io.cc>
#include <blitz/ops.h>

BZ_USING_NAMESPACE(blitz)

// Tests that operations on multicomponent arrays work as
// expected. This is a bit tricky because now they involve two
// recursive ET applications.

typedef Array<TinyVector<TinyVector<double,2>, 2>, 1> array_1vv;
typedef Array<TinyVector<double, 2>, 1> array_1v;
typedef Array<double, 1> array_1;
typedef TinyVector<double, 5> tv;

int main()
{
  // create some arrays to operate on
  const int sz=5;

  array_1vv a(sz),b(sz);
  //array_1v a(sz),b(sz);
  //array_1 a(sz),b(sz);
  //tv a,b;
  //a(0)[0]=TinyVector<double,2>(1,2);
  //,2,3,4,5;

  // cout << a << endl;

  // a *= 2;

  // cout << a << endl;

  // //a *= scalar(TinyVector<double, 2>(0.5,-0.5));

  // cout << a << endl;
  // tv v1(1,1);
  // tv v2;
  //v2 = -v1;
  b= -a;

  cout << b << endl;

    return 0;
}

