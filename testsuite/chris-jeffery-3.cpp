#include "testsuite.h"
#include <blitz/Array.h>


BZ_USING_NAMESPACE(blitz)

int main()
{
Array<float,2> test(8,8), test2(5,5) ;

test = 5;

Range I(2,6) ;
Range J(3,7) ;

test2 = where(test(I,J) > test(I-1,J), 0, test(I,J));

BZTEST(test2(3,3) == 5);

cout << test2 << endl ;

}


