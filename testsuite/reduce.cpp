#include "testsuite.h"
#include <blitz/array.h>
#include <blitz/tinyvec2.h>

BZ_USING_NAMESPACE(blitz)

template<typename T>
void test_1d(T& B)
{
  B = -2, 5, 4, 3, 1, 1;

    BZTEST(sum(B) == 12);
    BZTEST(mean(B) == 2);
    BZTEST(min(B) == -2);
    BZTEST(max(B) == 5);
    BZTEST(product(B) == -120);
    BZTEST(first(B>0) == 1);
    BZTEST(last(B>3) == 2);
    BZTEST(count(B>0) == 5);
    BZTEST(any(B>0));
    BZTEST(!any(B>10));
    BZTEST(!all(B>0));
    BZTEST(all(B>-10));

    BZTEST(all(maxIndex(B)==1));
    BZTEST(all(minIndex(B)==0));
}

int main()
{
    Array<int,2> A(4,3);

    A = 0,  1, 2,
        3,  4, 5,
        6,  7, 8,
        9, 10, 11;

    BZTEST(sum(A) == 11*12/2);
    BZTEST(min(A) == 0);
    BZTEST(max(A) == 11);

    const MinMaxValue<int> mm = minmax(A);
    //std::cerr << mm.min << ' ' << mm.max << std::endl;
    BZTEST(mm.min == 0);
    BZTEST(mm.max == 11);

    BZTEST(product(A) == 0);
    BZTEST(all(A >= 0));
    BZTEST(any(A == 7));
    BZTEST(count(A > 1 && A < 5) == 3);
    BZTEST(sum(pow2(A)) == 506);

    BZ_USING_NAMESPACE(blitz::tensor)

    BZTEST(sum(min(A,j)) == 0+3+6+9);
    BZTEST(sum(max(A(j,i),j)) == 9+10+11);

    Array<int,1> B(6);
    test_1d(B);
    TinyVector<int,6> Bv;
    test_1d(Bv);

    Array<int,3> C(2,2,2);
    C = 0, 1, 2, 3, 4, 5, 6, 7;

    BZTEST(sum(C) == 7*8/2);
    BZTEST(all(C <= 7));
    BZTEST(any(C == 5));
    BZTEST(!any(C == 8));
    BZTEST(sum(C(k,j,i)) == 7*8/2);
    BZTEST(sum(C(j,k,i)) == 7*8/2);
    BZTEST(sum(sum(sum(C,k),j)) == 7*8/2);

    return 0;
}

