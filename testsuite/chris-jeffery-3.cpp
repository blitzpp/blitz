#include "testsuite.h"
#include <blitz/array.h>


BZ_USING_NAMESPACE(blitz)

int main()
{
Array<float,2> test(8,8), test2(5,5) ;

test = 5;

Range I(2,6) ;
Range J(3,7) ;

// Next line should be test(I,J) > test(I-1,J) but this causes a
// conflict with std::relops; is there a less ugly workaround?
test2 = where(blitz::operator> (test(I,J), test(I-1,J)), 0, test(I,J));

BZTEST(test2(3,3) == 5);

cout << test2 << endl ;

}


