// blitz-bugs/archive/0163.html

#include "testsuite.h"
#include <blitz/array.h>

BZ_USING_NAMESPACE(blitz)

struct A {
    Array<double,2> a,b,c;

    A()
      : a(fortranArray)
    {
	const int w=simdTypes<double>::vecWidth;
	if(w>1)
	  cerr << "NOTE:This test makes assumptions about storage that are not true when a SIMD\nwidth is specified. The test has been altered to not fail.\n";

        a.resize(5*w,5*w);

        Array<double,2> d(fortranArray);
        d.resize(5*w,5*w);

        Array<double,2> e(0,0,fortranArray);
        e.resize(5*w,5*w);

        BZTEST(a.extent(0) == 5*w && a.extent(1) == 5*w);
        BZTEST(a.stride(0) == 1 && a.stride(1) == 5*w);
        BZTEST(d.extent(0) == 5*w && d.extent(1) == 5*w);
        BZTEST(d.stride(0) == 1 && d.stride(1) == 5*w);
        BZTEST(e.extent(0) == 5*w && e.extent(1) == 5*w);
        BZTEST(e.stride(0) == 1 && e.stride(1) == 5*w);
    }
};

int main()
{
    A x;
}

