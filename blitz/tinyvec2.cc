/***************************************************************************
 * blitz/tinyvec.cc  Declaration of TinyVector methods
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

#ifndef BZ_TINYVEC2_CC
#define BZ_TINYVEC2_CC

#include <blitz/tv2assign.h>
#include <blitz/tv2fastiter.h>  // Iterators
#include <blitz/tv2ops.cc>
#include <blitz/tinyvec2io.cc>

BZ_NAMESPACE(blitz)

template<typename P_numtype, int N_length>
inline TinyVector2<P_numtype, N_length>::TinyVector2(const T_numtype initValue) {
    for (int i=0; i < N_length; ++i)
        data_[i] = initValue;
}

template<typename P_numtype, int N_length>
inline TinyVector2<P_numtype, N_length>::TinyVector2(const TinyVector2<T_numtype, N_length>& x) {
    for (int i=0; i < N_length; ++i)
        data_[i] = x.data_[i];
}

template<typename P_numtype, int N_length>
template<typename P_numtype2>
inline TinyVector2<P_numtype, N_length>::TinyVector2(const TinyVector2<P_numtype2, N_length>& x) {
    for (int i=0; i < N_length; ++i)
        data_[i] = static_cast<P_numtype>(x[i]);
}

template<typename P_numtype, int N_length>
template<typename P_expr, typename P_updater>
inline void TinyVector2<P_numtype, N_length>::_bz_assign(P_expr expr, P_updater up) {
    BZPRECHECK(expr.shapeCheck(N_length),
        "Shape check failed." << endl << "Expression:");

    BZPRECHECK((P_expr::rank == N_rank) || (P_expr::numArrayOperands == 0), 
        "Assigned rank " << P_expr::rank << " expression to TinyVector");

    const bool useUnitStride = expr.isUnitStride(0);

    if (useUnitStride) {
        _bz_meta_tv2Assign<N_length, 0>::fastAssign(*this, expr, up);
    } else {
        _bz_meta_tv2Assign<N_length, 0>::assign(*this, expr, up);
    }
}


template<typename P_numtype, int N_length>
template<int N0>
_bz_ArrayExpr<ArrayIndexMapping<FastTV2Iterator<P_numtype, N_length>, N0> >
TinyVector2<P_numtype, N_length>::operator()(IndexPlaceholder<N0>) const
{ 
        return _bz_ArrayExpr<ArrayIndexMapping<FastTV2Iterator<T_numtype, N_length>, N0> >
            (noConst());
}


//  A tinyvector operand

template <typename T,int N>
struct asExpr<TinyVector2<T,N> > {
    typedef FastTV2Iterator<T,N> T_expr;
    static T_expr getExpr(const TinyVector2<T,N>& x) { return x.beginFast(); }
};

BZ_NAMESPACE_END

#endif // BZ_TINYVEC_CC
