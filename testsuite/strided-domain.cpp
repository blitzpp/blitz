/*
 * Bug found by Roshan Samuel <roshanj@iitk.ac.in>.
 * Using StridedDomain object without arguments gave a compile-time error
 * since there was no empty constructor for it in ../blitz/array/domain.h
 *
 * The fix is to add an empty constructor for StridedDomain in the above file.
 *
 * If this code compiles without error, the bug is fixed.
 * As such, it doesn't use the testsuite header.
 *
 */

#include <blitz/array.h>

int main() 
{
    blitz::firstIndex i;
    blitz::secondIndex j;

    blitz::StridedDomain<2> testSD;
  
    testSD = blitz::StridedDomain<2>(blitz::TinyVector<int, 2>(0, 0),
                                     blitz::TinyVector<int, 2>(8, 8),
                                     blitz::TinyVector<int, 2>(2, 2));

    blitz::Array<int, 2> A;
    A.resize(9, 9);
    A = i*10 + j;

    // The below line should output 44
    std::cout << A(testSD)(2,2) << std::endl;

    return 0;
}

/*
 * To test this code, a shell script can be written as below:
 *

mkdir install
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=../install/ ../
make install
cd ../testsuite/
g++ -I../install/include/ -L../install/lib/ strided-domain.cpp
./a.out

 *
 * The above script must be run from the root directory of the repo.
 * If the script executes without error, the bug is fixed.
 */
