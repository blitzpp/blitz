// -*- C++ -*-
/***************************************************************************
 * blitz/randref.h      Random number generators, expression templates
 *                      wrapper
 *
 * $Id$
 *
 * Copyright (C) 1997-2011 Todd Veldhuizen <tveldhui@acm.org>
 *
 * This file is a part of Blitz.
 *
 * Blitz is free software: you can redistribute it and/or modify 
 * it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3
 * of the License, or (at your option) any later version.
 *
 * Blitz is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public 
 * License along with Blitz.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * Suggestions:          blitz-devel@lists.sourceforge.net
 * Bugs:                 blitz-support@lists.sourceforge.net    
 *
 * For more information, please see the Blitz++ Home Page:
 *    https://sourceforge.net/projects/blitz/
 *
 ***************************************************************************/

#ifndef BZ_RANDREF_H
#define BZ_RANDREF_H

#ifndef BZ_RANDOM_H
 #error <blitz/randref.h> must be included via <blitz/random.h>
#endif // BZ_RANDOM_H

BZ_NAMESPACE(blitz)

template<typename P_distribution>
class _bz_VecExprRandom {

public:
    typedef _bz_typename Random<P_distribution>::T_numtype T_numtype;

    _bz_VecExprRandom(Random<P_distribution>& random)
        : random_(random)
    { }

#ifdef BZ_MANUAL_VECEXPR_COPY_CONSTRUCTOR
    _bz_VecExprRandom(_bz_VecExprRandom<P_distribution>& x)
        : random_(x.random_)
    { }
#endif

    T_numtype operator[](unsigned) const
    { return random_.random(); }

    T_numtype operator()(unsigned) const
    { return random_.random(); }

    unsigned length(unsigned recommendedLength) const
    { return recommendedLength; }

    unsigned _bz_suggestLength() const
    { return 0; }

    bool _bz_hasFastAccess() const
    { return 1; }

    T_numtype _bz_fastAccess(unsigned) const
    { return random_.random(); }

private:
    _bz_VecExprRandom() : random_( Random<P_distribution>() ) { }

    Random<P_distribution>& random_;
};

BZ_NAMESPACE_END

#endif // BZ_RANDREF_H

