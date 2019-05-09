/***************************************************************************
 * blitz/array/complex.cc  Special functions for complex arrays
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
 ****************************************************************************/
#ifndef BZ_ARRAYCOMPLEX_CC
#define BZ_ARRAYCOMPLEX_CC

// Special functions for complex arrays

#ifndef BZ_ARRAY_H
 #error <blitz/array/complex.cc> must be included via <blitz/array/array.h>
#endif

namespace blitz {

#ifdef BZ_HAVE_COMPLEX

template<typename T_numtype, int N_rank>
inline Array<T_numtype, N_rank> real(const Array<complex<T_numtype>,N_rank>& A)
{
    return A.extractComponent(T_numtype(), 0, 2);
}

template<typename T_numtype, int N_rank>
inline Array<T_numtype, N_rank> imag(const Array<complex<T_numtype>,N_rank>& A)
{
    return A.extractComponent(T_numtype(), 1, 2);
}


#endif

}

#endif // BZ_ARRAYCOMPLEX_CC

