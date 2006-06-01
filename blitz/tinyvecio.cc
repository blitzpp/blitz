/*
 * $Id$
 *
 * Copyright (C) 1997 Todd Veldhuizen <tveldhui@oonumerics.org>
 * All rights reserved.  Please see <blitz/blitz.h> for terms and
 * conditions of use.
 *
 */

#ifndef BZ_TINYVECIO_CC
#define BZ_TINYVECIO_CC

#ifndef BZ_TINYVEC_H
 #include <blitz/tinyvec.h>
#endif

BZ_NAMESPACE(blitz)

// NEEDS_WORK???
// This version of operator<< is updated on August 2005 
// by Sergei Mingaleev <mingaleev@gmail.com>. The output 
// format for 2D TinyVector is the same as for complex 
// numbers - so that one can read Array of complex numbers 
// into Array of TinyVectors for speed-up of calculations. 
// Also, the corresponding operator>> is updated. 

template<typename P_numtype, int N_length>
ostream& operator<<(ostream& os, const TinyVector<P_numtype, N_length>& x)
{
    os << "(" << x[0];
    for (int i=1; i < N_length; ++i)
    {
        os << "," << x[i];
    }
    os << ")";
    return os;
}

// Input of tinyvec contribute by Adam Levar <adaml@mcneilhouse.com>
// and updated by Sergei Mingaleev <mingaleev@gmail.com>
template <typename T_numtype, int N_length>
istream& operator>>(istream& is, TinyVector<T_numtype, N_length>& x)
{
    char sep;
             
    is >> sep;
    BZPRECHECK(sep == '(', "Format error while scanning input TinyVector"
        << endl << " (expected '(' opening TinyVector)");

    is >> x(0);
    for (int i = 1; i < N_length; ++i)
    {
        is >> sep;
        BZPRECHECK(sep == ',', "Format error while scanning input TinyVector"
             << endl << " (expected ',' between TinyVector components)");
        BZPRECHECK(!is.bad(), "Premature end of input while scanning TinyVector");
        is >> x(i);
    }
    is >> sep;
    BZPRECHECK(sep == ')', "Format error while scanning input TinyVector"
       << endl << " (expected ')' closing TinyVector)");
    
    return is;
}

BZ_NAMESPACE_END

#endif // BZ_TINYVECIO_CC
