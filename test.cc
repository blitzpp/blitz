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

typedef TinyVector<double,2> tv2;
typedef TinyVector<double,3> tv3;
typedef TinyVector<int,3> it;
typedef Array<double,2> a2;
typedef Array<TinyVector<double,2>,2> atv2;
typedef Array<double,3> a3;
typedef Array<TinyVector<double,3>,3> atv3;
typedef Array<TinyMatrix<double,3,3>,3> atm3;
typedef Array<TinyMatrix<double,2,2>,2> atm2;

int main(int, char**)
{
  atv2 a(5,5);
  a2 b(3,3);
  b=2;
  a=1,2,3,3,3,3,4,3,2,
    1,2,3,2,tv2(-1,-2),3,4,3,2,
    1,2,3,3,3,3,4;//,3,2;
  
  //blitz::_bz_ArrayExpr<blitz::_bz_ArrayExprBinaryOp<blitz::_bz_ArrayExpr<blitz::_bz_ArrayExprConstant<int> >, blitz::_bz_ArrayExpr<blitz::FastArrayIterator<blitz::TinyVector<double, 2>, 2> >, blitz::Multiply<int, double> > > x(2*a);
  //x.shift(1,firstDim);
  //double dd;

  //dd=central12_stencilop(asExpr<atv2>::getExpr(a),firstDim,firstDim);

  //dd=central12_stencilop(2*a, firstDim, firstDim);

  //dd=div2D_stencilop(2*a);
  //dd=div2D_stencilop(asExpr<atv2>::getExpr(a));
  a2 b1(div2D(a));
  a2 b2(div2D(1.0*a));
  
  //b(0,0,0)=(div(a,a))(it(0,0,0));
    //a3 bb(div(a,a));

  cout << a << endl;
  cout << b1 << endl;
  cout << b2 << endl;

}
