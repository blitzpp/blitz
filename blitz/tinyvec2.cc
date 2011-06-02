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

BZ_NAMESPACE(blitz)

template<typename P_numtype, int N_length>
inline TinyVector<P_numtype, N_length>::TinyVector(const T_numtype initValue) {
    for (int i=0; i < N_length; ++i)
        data_[i] = initValue;
}

template<typename P_numtype, int N_length>
inline TinyVector<P_numtype, N_length>::TinyVector(const TinyVector<T_numtype, N_length>& x) {
    for (int i=0; i < N_length; ++i)
        data_[i] = x.data_[i];
}

template<typename P_numtype, int N_length>
template<typename P_numtype2>
inline TinyVector<P_numtype, N_length>::TinyVector(const TinyVector<P_numtype2, N_length>& x) {
    for (int i=0; i < N_length; ++i)
        data_[i] = static_cast<P_numtype>(x[i]);
}


template<typename P_numtype, int N_length>
template<int N0>
_bz_ArrayExpr<ArrayIndexMapping<FastTV2Iterator<P_numtype, N_length>, N0> >
TinyVector<P_numtype, N_length>::operator()(IndexPlaceholder<N0>) const
{ 
        return _bz_ArrayExpr<ArrayIndexMapping<FastTV2Iterator<T_numtype, N_length>, N0> >
            (noConst());
}



BZ_NAMESPACE_END

#endif // BZ_TINYVEC_CC
