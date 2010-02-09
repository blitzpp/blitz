#include "testsuite.h"
#include <blitz/array.h>

BZ_USING_NAMESPACE(blitz)

const int N=1000;

// To return an expression that references local arrays, the
// expression has to be wrapped in safeToReturn(), which turns
// FastArrayIterators into FastArrayCopyIterators which keep a copy of
// the arrays instead of referencing them.

// this is safe
_bz_ArrayExpr<blitz::_bz_ArrayExprBinaryOp<blitz::FastArrayCopyIterator<double, 1>, blitz::FastArrayCopyIterator<double, 1>, blitz::Multiply<double, double> > > good()
{
  Array<double,1> a(N);
  a=tensor::i;
  Array<double,1> b(N);
  b=sin(a);
  return safeToReturn(a*b);
}

// this is unsafe
_bz_ArrayExpr<blitz::_bz_ArrayExprBinaryOp<blitz::FastArrayIterator<double, 1>, blitz::FastArrayIterator<double, 1>, blitz::Multiply<double, double> > > bad()
{
  Array<double,1> a(N);
  a=tensor::i;
  Array<double,1> b(N);
  b=sin(a);
  return a*b;
}

int main()
{
  // switch to expr=bad() and it will crash.
  _bz_ArrayExpr<blitz::_bz_ArrayExprBinaryOp<blitz::FastArrayCopyIterator<double, 1>, blitz::FastArrayCopyIterator<double, 1>, blitz::Multiply<double, double> > > expr=good();
  //_bz_ArrayExpr<blitz::_bz_ArrayExprBinaryOp<blitz::FastArrayIterator<double, 1>, blitz::FastArrayIterator<double, 1>, blitz::Multiply<double, double> > > expr=bad();
  Array<double,1> result(N);
  result=expr;
  BZTEST(all(result==tensor::i*sin(1.0*tensor::i)));

    return 0;
}

