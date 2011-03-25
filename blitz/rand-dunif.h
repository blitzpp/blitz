// -*- C++ -*-
/***************************************************************************
 * blitz/rand-dunif.h    Discrete uniform generator
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

#ifndef BZ_RAND_DUNIF_H
#define BZ_RAND_DUNIF_H

#ifndef BZ_RANDOM_H
 #include <blitz/random.h>
#endif

#ifndef BZ_RAND_UNIFORM_H
 #include <blitz/rand-uniform.h>
#endif

#include <math.h>

BZ_NAMESPACE(blitz)

template<typename P_uniform BZ_TEMPLATE_DEFAULT(Uniform)>
class DiscreteUniform {

public:
    typedef int T_numtype;
    typedef P_uniform T_uniform;

    DiscreteUniform(int low, int high, double=0)
        : low_(low), range_(high-low+1)
    { 
    }

    void randomize() 
    { 
        uniform_.randomize();
    }
  
    int random()
    { 
        return int(uniform_.random() * range_ + low_);
    } 

private:
    int low_, range_;
    T_uniform uniform_;
};

BZ_NAMESPACE_END

#endif // BZ_RAND_DUNIF_H

