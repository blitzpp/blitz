#include "testsuite.h"
#include <blitz/array.h>
//#include <blitz/array.cc>
#include <blitz/tinyvec2.cc>
#include <blitz/tinymat2.h>
#include <blitz/tinymat2io.cc>
#include <blitz/tm2ops.cc>
#include <blitz/array/asexpr.cc>
#include <blitz/array/ops.h>
#include <blitz/array/ops.cc>
#include <blitz/array/fastiter.h>
#include <blitz/array/methods.cc>
#include <blitz/array/methods.cc>
#include <blitz/array/io.cc>
#include <blitz/ops.h>
#include <blitz/array/funcs.h>

BZ_USING_NAMESPACE(blitz)

// Tests that operations on multicomponent arrays work as
// expected. This is a bit tricky because now they involve two
// recursive ET applications.

typedef Array<TinyVector<TinyVector<double,2>, 2>, 1> array_1vv;
typedef Array<TinyVector<double, 2>, 1> array_1v;
typedef Array<TinyMatrix<double, 2,2>, 1> array_1m;
typedef Array<double, 1> array_1;
typedef TinyVector<TinyVector<double,2>, 5> tv;

int main()
{
  // create some arrays to operate on
  const int sz=5;

  //array_1vv a(sz),b(sz);
  //array_1v a(sz),b(sz);
  array_1m a(sz),b(sz);
  array_1 aa(sz),bb(sz);
  //tv a,b;
  
  a=1,2,3,4,5;
  //a(0)=1;
  //  a(1)=TinyVector<double,2>(2,3);
  aa=1,2,3,4,5;
  // cout << a << endl;

  // a *= 2;

  // cout << a << endl;

  // //a *= scalar(TinyVector<double, 2>(0.5,-0.5));

  // cout << a << endl;
  // tv v1(1,1);
  // tv v2;
  //v2 = -v1;
  //(-a).fastRead(1);//.fastRead(1).fastRead(1);
  b= 2*(-a);//* scalar(TinyVector<double, 2>(0.5,-0.5));
  bb=aa;
  //bb= sqrt(aa)*aa/(-aa);

  TinyMatrix<double,2,2> m;
  cout << m;
  //cout << a << "\n" << b << endl;
  cout << bb << endl;

    return 0;
}

