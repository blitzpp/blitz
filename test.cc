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
//#include <blitz/tinyvec2.h>
//#include <blitz/tv2fastiter.h>
//#include <blitz/array/map.h>
//#include <blitz/reduce.h>
//#include <blitz/meta/vecassign.h>
//#include <blitz/array/reduce.h>
//#include <blitz/ops.h>
//#include <blitz/array/ops.h>
//#include <blitz/array/where.h>
#include <blitz/range.h>

//#include <blitz/array/stencil-et.h>

#include <blitz/array.h>


#include <blitz/tinyvec2.cc>
#include <blitz/array.cc>
#include <blitz/range.cc>

using namespace blitz;

int main(int, char**)
{
  Array<double,1> a(4);
  a=Range(0,6,2);
  cout << a << endl;
}
