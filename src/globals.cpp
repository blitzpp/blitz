#define BZ_GENERATE_GLOBAL_INSTANCES

/*
 * This module contains instances of global variables and objects.
 * The preprocessor symbol _bz_global normally expands to "extern",
 * but the declaration of BZ_GENERATE_GLOBAL_INSTANCES causes it
 * to expand to "" for this source file.  This ensures that globals
 * will have one unique instance, in libblitz.a.
 */

#include <blitz/indexexpr.h>      // Tensor index objects
#include <blitz/bzdebug.h>        // Test suite globals
#include <blitz/array.h>          // Dummy array object (_dummyArray)
#include <blitz/zero.cc>          // static ZeroElement data instances
#include <random/mtparam.cc>      // MT19937 parameter sets

// NEEDS_WORK: after switch from RCS to CVS, get a version identifier.
char _blitz_id[] = "@(#) Blitz++ class library";
