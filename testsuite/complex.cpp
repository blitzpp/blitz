// Test real, imag, conj, abs, arg, polar

#define BZ_NEW_EXPRESSION_TEMPLATES

#include "testsuite.h"

#include <blitz/array.h>

BZ_USING_NAMESPACE(blitz)

#ifndef BZ_HAVE_COMPLEX_MATH


int main()
{
    cout << "(Cannot test complex math functions-- not supported on "
            "this platform)" << endl;

    return 0;
}

#else

typedef Array<complex<float>, 1> CArray;

int main()
{
    CArray A(2);
    A(0) = complex<float>(1,2);
    A(1) = complex<float>(3,4);

    Array<float,1> Ar = real(A);
    BZTEST(int(Ar(0)) == 1 && int(Ar(1)) == 3);

    Array<float,1> Ai = imag(A);
    BZTEST(int(Ai(0)) == 2 && int(Ai(1)) == 4);

    CArray Ac(2);
    Ac = conj(A);

    BZTEST(Ac(0) == complex<float>(1,-2));
    BZTEST(Ac(1) == complex<float>(3,-4));

    Array<float,1> Ab(2);
    Ab = abs(A);
    BZTEST(abs(Ab(0) - 2.236068) < 0.0001);
    BZTEST(abs(Ab(1) - 5.0) < 0.0001);

    Ab = arg(A);
    BZTEST(abs(Ab(0) - atan(2.0)) < 0.0001);
    BZTEST(abs(Ab(1) - atan(4.0/3.0)) < 0.0001);

    Array<float,1> r(2), theta(2);
    r(0) = 4.0;
    r(1) = 15.0;
    theta(0) = 3.141592/3.0;
    theta(1) = 3.0*3.141592/2.0;
    Ac = blitz::polar(r,theta);
    BZTEST(abs(real(Ac(0)) - 2) < 0.0001);
    BZTEST(abs(imag(Ac(0)) - 3.4641012) < 0.0001);
    BZTEST(abs(real(Ac(1)) - 0.0) < 0.0001);
    BZTEST(abs(imag(Ac(1)) + 15.0) < 0.0001);

    return 0;
}
#endif

