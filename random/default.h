#ifndef BZ_RANDOM_DEFAULT_H
#define BZ_RANDOM_DEFAULT_H

#include <random/mt.h>

BZ_NAMESPACE(ranlib)

// Some terminology:
// IRNG = Integer Random Number Generator.  IRNGs generate random
//        integers, which are used to create floating-point random
//        numbers.
// RNG  = Random Number Generator.  RNGs use IRNGs to create floating-
//        point random numbers following desired distributions.

typedef float defaultType;

// These are type tags.  A RNG with sharedState shares an IRNG
// with other RNGs.  An RNG with independentState
// contains its own IRNG.  Generally, sharedState RNGs should be
// used.

struct sharedState { };
struct independentState { };
typedef sharedState defaultState;

typedef unsigned int IRNG_int;


// IRNGWrapper handles shared and independent state IRNGs.
// If a class inherits from IRNGWrapper<IRNG,sharedState>,
// it gets a static IRNG (i.e. the IRNG state is shared among
// all RNGs); if it inherits from IRNGWrapper<IRNG,independentState>,
// it gets an independent IRNG (the IRNG state is encapsulated
// in the RNG, and is not shared among RNGs).

template<typename IRNG, typename state>
class IRNGWrapper {
};

template<typename IRNG>
class IRNGWrapper<IRNG,sharedState> {

public:
    void seed(IRNG_int x)
    { irng_.seed(x); }

protected:
    static IRNG irng_;
};

template<typename IRNG>
IRNG IRNGWrapper<IRNG,sharedState>::irng_;

template<typename IRNG>
class IRNGWrapper<IRNG,independentState> {

public:
    void seed(IRNG_int x)
    { irng_.seed(x); }

protected:
    IRNG irng_;
};

// defaultIRNG is a type alias for the default Integer Random
// Number Generator (IRNG).

typedef MersenneTwister defaultIRNG;

BZ_NAMESPACE_END

#endif // BZ_RANDOM_DEFAULT_H

