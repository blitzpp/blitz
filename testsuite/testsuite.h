#ifndef TESTSUITE_H
#define TESTSUITE_H

#ifdef BZ_DEBUG_H
 #error <testsuite/testsuite.h> must be included before any other header files.
#endif

#define BZ_TESTSUITE

#include <blitz/blitz.h>

#define BZTEST(x)    { if(!(x)) { std::cout << "Test failed: " << __FILE__ << " line " << __LINE__ << std::endl; std::exit(1); } }
 
#endif // TESTSUITE_H
