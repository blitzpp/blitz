// -*- C++ -*-
/***************************************************************************
 * blitz/meta/vecassign.h   TinyVector assignment metaprogram
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

#ifndef BZ_META_VECASSIGN_H
#define BZ_META_VECASSIGN_H

#include <blitz/blitz.h>

namespace blitz {

template<int N, int I> 
class _bz_meta_vecAssign {
public:
    static const int loopFlag = (I < N-1) ? 1 : 0;

    template<typename T_data, typename T_expr, typename T_updater>
    static inline void fastAssign(T_data* data, T_expr expr, T_updater u)
    {
      u.update(data[I], expr.fastRead(I));
        _bz_meta_vecAssign<N * loopFlag, (I+1) * loopFlag>
	  ::fastAssign(data,expr,u);
    }

    template<typename T_vector, typename T_expr, typename T_updater>
    static inline void assign(T_vector& vec, T_expr expr, T_updater u)
    {
        u.update(vec[I], expr[I]);
        _bz_meta_vecAssign<N * loopFlag, (I+1) * loopFlag>
           ::assign(vec,expr,u);
    }

    template<typename T_vector, typename T_numtype, typename T_updater>
    static inline void assignWithArgs(T_vector& vec, T_updater u,
        T_numtype x0, T_numtype x1=0, T_numtype x2=0, T_numtype x3=0,
        T_numtype x4=0, T_numtype x5=0, T_numtype x6=0, T_numtype x7=0,
        T_numtype x8=0, T_numtype x9=0)
    {
        u.update(vec[I], x0);
        _bz_meta_vecAssign<N * loopFlag, (I+1) * loopFlag>
            ::assignWithArgs(vec, u, x1, x2, x3, x4, x5, x6, x7, x8, x9);
    }
        
};

template<>
class _bz_meta_vecAssign<0,0> {
public:
    template<typename T_vector, typename T_expr, typename T_updater>
    static inline void fastAssign(T_vector&, T_expr, T_updater)
    { }

    template<typename T_vector, typename T_expr, typename T_updater>
    static inline void assign(T_vector&, T_expr, T_updater)
    { }

    template<typename T_vector, typename T_numtype, typename T_updater>
    static inline void assignWithArgs(T_vector&, T_updater,
        T_numtype, T_numtype =0, T_numtype =0, T_numtype =0,
        T_numtype =0, T_numtype =0, T_numtype =0, T_numtype =0,
        T_numtype =0, T_numtype =0)
    {
    }
};



}

#endif // BZ_META_ASSIGN_H
