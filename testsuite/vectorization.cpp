#include "testsuite.h"
#include <blitz/array.h>

BZ_USING_NAMESPACE(blitz)

// test that vectorization routines do sensible things in weird situations.

int main()
{
  const int sz=10;
  Array<float,1> a(sz), b(sz);
  Array<double,1> c(sz), d(sz);
  Array<complex<float>,1> ca(sz), cb(sz);
  Array<complex<double>,1> cc(sz), cd(sz);
  /*
  // test simd width calculation for expressions (this depends on the
  // operands in the expression, not the result type)
  BZTEST((2*a).simdWidth==simdTypes<float>::vecWidth);
  BZTEST((2L*a).simdWidth==simdTypes<long int>::vecWidth);
  BZTEST((2.0*a).simdWidth==simdTypes<double>::vecWidth);
  BZTEST((2.0f*a).simdWidth==simdTypes<float>::vecWidth);
  BZTEST((2*c).simdWidth==simdTypes<double>::vecWidth);
  BZTEST((a*c).simdWidth==simdTypes<double>::vecWidth);

  BZTEST((2*ca).simdWidth==simdTypes<complex<float> >::vecWidth);
  BZTEST((2.0*ca).simdWidth==simdTypes<complex<float> >::vecWidth);
  BZTEST((2.0*ca).simdWidth==simdTypes<double>::vecWidth);
  BZTEST((2*cc).simdWidth==simdTypes<complex<double> >::vecWidth);
  BZTEST((ca*cc).simdWidth==simdTypes<complex<double> >::vecWidth);
  BZTEST((a*cc).simdWidth==simdTypes<complex<double> >::vecWidth);
  BZTEST((c*cc).simdWidth==simdTypes<complex<double> >::vecWidth);
  BZTEST((a*c*ca*cc).simdWidth==simdTypes<complex<double> >::vecWidth);
    
  // this expression has complex result type, but all operands are
  // floats, so the *expression* width is still that of a float.
  BZTEST((blitz::polar(a,b)).simdWidth==simdTypes<float>::vecWidth);
  BZTEST(sizeof((blitz::polar(a,b)).fastRead(0))==sizeof(complex<float>));
  */

  a=tensor::i;
  b=2.5*a;

  asm("nop;nop;");
  ca=blitz::polar(a,b);
  asm("nop;nop;");
  
  cout << ca << endl;
  return 0;
}

