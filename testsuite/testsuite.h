#ifndef TESTSUITE_H
#define TESTSUITE_H

#ifdef BZ_DEBUG_H
 #error <testsuite/testsuite.h> must be included before any other header files.
#endif

#define BZ_TESTSUITE

#include <stdlib.h>
#include <blitz/blitz.h>

#define BZTEST(x)    { if(!(x)) { BZ_STD_SCOPE(cout) << "Test failed: " << __FILE__ << " line " << __LINE__ << BZ_STD_SCOPE(endl); exit(1); } }
 
#endif // TESTSUITE_H
