//#include <blitz/et-forward.h>
//#include <blitz/array/asexpr.h>
//#include <blitz/prettyprint.h>
//#include <blitz/shapecheck.h>
//#include <blitz/numinquire.h>
//#include <blitz/array/domain.h>
//#include <blitz/array/slice.h>
//#include <blitz/array/expr.h>
//#include <blitz/constpointerstack.h>
//#include <blitz/array/fastiter.h>
#include <blitz/tinyvec2.h>
#include <blitz/tinymat2.h>
#include <blitz/tinymat2.cc>
//#include <blitz/tv2fastiter.h>
//#include <blitz/array/map.h>
//#include <blitz/reduce.h>
//#include <blitz/meta/vecassign.h>
//#include <blitz/array/reduce.h>
//#include <blitz/ops.h>
//#include <blitz/array/ops.h>
//#include <blitz/array/where.h>
#include <blitz/range.h>


#include <blitz/array.h>


#include <blitz/tinyvec2.cc>
//#include <blitz/array.cc>a
#include <blitz/array/stencil-et.h>
#include <blitz/array/stencilops.h>

using namespace blitz;

typedef double numtype;
typedef TinyVector<numtype,2> tv2;
typedef TinyVector<numtype,4> tv3;
typedef TinyVector<int,3> it;
typedef Array<numtype,1> a1;
typedef Array<numtype,2> a2;
typedef Array<TinyVector<numtype,2>,2> atv2;
typedef Array<numtype,3> a3;
typedef Array<TinyVector<numtype,3>,3> atv3;
typedef Array<TinyMatrix<numtype,3,3>,3> atm3;
typedef Array<TinyMatrix<numtype,2,2>,2> atm2;

//tv3 fill() { return tv3(1,3,1,3); }

extern void junk(tv3&, tv3&);
extern void sink();

int main(int, char**)
{
  const int sz=8;
  // tv3 a=fill();
  // tv3 b=fill();
  // tv3 c=fill();
  a1 a(sz),b(sz),c(sz);
  b=1.,2.,3.,4.,5.,6.,7.,8.;
  c=7.,6.,.5,293.,4.,9.,0.,1.0;

  // const int N=100;
  // const numtype x=0.2354;
  // numtype s=0;
  // for(int i=0;i<N;++i) {
  //   asm("nop;nop;nop;");
  //   a= a + x*c;
  //   asm("nop;nop;nop;");
  //   sink();
  // }
  // cout << a << endl;
  // cout << s << endl;

  simdTypes<numtype>::vecType v,w,z;
  w=1,2; z=2,3;
  //v=w*z;
  //v=(b*c).fastRead_tv(0);

  a=2*b+c;
  cout << a << endl;
}
