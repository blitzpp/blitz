// blitz-bugs/archive/0163.html

#include "testsuite.h"
#include <blitz/Array.h>

BZ_USING_NAMESPACE(blitz)

struct A {
    Array<double,2> a,b,c;

    A()
      : a(fortranArray)
    {
        a.resize(10,10);

        Array<double,2> d(fortranArray);
        d.resize(10,10);

        Array<double,2> e(0,0,fortranArray);
        e.resize(10,10);

        BZTEST(a.extent(0) == 10 && a.extent(1) == 10);
        BZTEST(a.stride(0) == 1 && a.stride(1) == 10);
        BZTEST(d.extent(0) == 10 && d.extent(1) == 10);
        BZTEST(d.stride(0) == 1 && d.stride(1) == 10);
        BZTEST(e.extent(0) == 10 && e.extent(1) == 10);
        BZTEST(e.stride(0) == 1 && e.stride(1) == 10);
    }
};

int main()
{
    A x;
}

