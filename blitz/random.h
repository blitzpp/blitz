// -*- C++ -*-
/***************************************************************************
 * blitz/random.h       Random number generator wrapper class
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

#ifndef BZ_RANDOM_H
#define BZ_RANDOM_H

#ifndef BZ_BLITZ_H
 #include <blitz/blitz.h>
#endif

BZ_NAMESPACE(blitz)

template<typename P_distribution>
class Random {

public:
    typedef P_distribution T_distribution;
    typedef _bz_typename T_distribution::T_numtype T_numtype;

    Random(double parm1=0.0, double parm2=1.0, double parm3=0.0)
        : generator_(parm1, parm2, parm3)
    { }

    void randomize()
    { generator_.randomize(); }
   
    T_numtype random()
    { return generator_.random(); }

    operator T_numtype()
    { return generator_.random(); }

protected: 
    T_distribution generator_;
};

BZ_NAMESPACE_END

#include <blitz/randref.h>

#endif // BZ_RANDOM_H

