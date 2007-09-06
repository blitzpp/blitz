#include "testsuite.h"
#include <blitz/tinyvec-et.h>

using namespace blitz;

int main()
{
    TinyVector<int,3> A, B;
    A = 1, 2, 3;
    B = 0, 1, 2;

    A += B*B;
//  A = 1, 3, 7

    cout << A << endl;

    A *= 10;
//  A = 10, 30, 70

    cout << A << endl;

    TinyVector<int,3>::iterator it=B.begin(), end=B.end();
    cout << "(" << *it;
    for (it++; it != end; ++it) 
        cout << "," << *it;
    cout << ")" << endl;

// test tinyvector dot(), product(), and sum() functions
    int dotAB = dot(A,B); 
    BZTEST(dotAB==170);
    int dotAB2 = dot(A,B+B);
    BZTEST(dotAB2==2*dotAB);
    int dotA2B = dot(A+A,B);
    BZTEST(dotA2B==2*dotAB);
    int dotA2B2 = dot(A+A,B+B);
    BZTEST(dotA2B2==4*dotAB);
    int prod1 = product(A);
    BZTEST(prod1==21000);
    int prod2 = product(A+B);
    BZTEST(prod2==22320);
    int sum1 = sum(A);
    BZTEST(sum1==110);
    int sum2 = sum(A-B);
    BZTEST(sum2==sum1-sum(B));
}

