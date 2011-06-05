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

#ifndef BZ_TINYMAT2_CC
#define BZ_TINYMAT2_CC

#include <blitz/tm2ops.cc>
#include <blitz/tinymat2io.cc>

BZ_NAMESPACE(blitz)

template<typename P_numtype, int N_rows, int N_columns>
inline TinyMatrix<P_numtype, N_rows, N_columns>::TinyMatrix(T_numtype initValue) 
{
  for (int i=0; i < length(); ++i)
    data_[i] = initValue;
}

template<typename P_numtype, int N_rows, int N_columns>
inline TinyMatrix<P_numtype, N_rows, N_columns>::TinyMatrix(const T_matrix& x) 
{
  for (int i=0; i < length(); ++i)
    data_[i] = x.data_[i];
}

template<typename P_numtype, int N_rows, int N_columns>
template<typename P_numtype2>
inline
TinyMatrix<P_numtype, N_rows, N_columns>::TinyMatrix(const TinyMatrix<P_numtype2, N_rows, N_columns>& x)
{
  for (int i=0; i < length(); ++i)
    data_[i] = static_cast<P_numtype>(x.data_[i]);
}


template<typename P_numtype, int N_rows, int N_columns>
template<int N0, int N1>
inline _bz_ArrayExpr<ArrayIndexMapping<FastTM2Iterator<P_numtype, N_rows, N_columns>, N0, N1> >
TinyMatrix<P_numtype, N_rows, N_columns>::operator()(IndexPlaceholder<N0>, IndexPlaceholder<N1>) const
{
  return _bz_ArrayExpr<ArrayIndexMapping<FastTM2Iterator<T_numtype, 
							 N_rows, 
							 N_columns>, 
					 N0, N1> >(noConst());
} 



BZ_NAMESPACE_END

#endif // BZ_TINYVEC_CC
