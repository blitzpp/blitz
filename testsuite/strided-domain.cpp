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

using namespace blitz;

int main() 
{
    blitz::StridedDomain<3> testSD;
  
    testSD = blitz::StridedDomain<3>(blitz::TinyVector<int, 3>(0, 0, 0),
                                     blitz::TinyVector<int, 3>(9, 9, 9),
                                     blitz::TinyVector<int, 3>(2, 2, 2));
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
