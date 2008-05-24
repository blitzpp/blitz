#include "testsuite.h"
#include "blitz/array.h"
using namespace blitz;

class crap {
public:
    double a(const double x) const { return 2*x; }
    BZ_DECLARE_MEMBER_FUNCTION_RET(crap, a, double);
};

int main(int, char**)
{
    crap c;

    Array<double,1> lam(10);
    double l = 0.0;
    for (Array<double,1>::iterator i=lam.begin();i!=lam.end();++i)
        *i = l++;

    Array<double,1> a(c.a(lam));
    for (int i=0;i<10;++i)
        BZTEST(a(i)==2.0*i);

    return 0;
}
