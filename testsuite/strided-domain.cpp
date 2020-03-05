/*
 * Bug found by Roshan Samuel <roshanj@iitk.ac.in>.
 * Using StridedDomain object without arguments gave a compile-time error
 * since there was no empty constructor for it in ../blitz/array/domain.h
 *
 * The fix is to add an empty constructor for StridedDomain in the above file.
 *
 */

#include "testsuite.h"
#include <blitz/array.h>

int main() 
{
    blitz::StridedDomain<3> testSD;
  
    testSD = blitz::StridedDomain<3>(blitz::TinyVector<int, 3>(0, 0, 0),
                                     blitz::TinyVector<int, 3>(9, 9, 9),
                                     blitz::TinyVector<int, 3>(2, 2, 2));
    return 0;
}

