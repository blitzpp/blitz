/***************************************************************************
 * blitz/array/complex.cc  Special functions for complex arrays
 *
 * $Id$
 *
 * Copyright (C) 1997-2001 Todd Veldhuizen <tveldhui@oonumerics.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * Suggestions:          blitz-dev@oonumerics.org
 * Bugs:                 blitz-bugs@oonumerics.org
 *
 * For more information, please see the Blitz++ Home Page:
 *    http://oonumerics.org/blitz/
 *
 ***************************************************************************
 * $Log$
 * Revision 1.2  2001/01/25 00:25:55  tveldhui
 * Ensured that source files have cvs logs.
 *
 */

// Special functions for complex arrays

#ifndef BZ_ARRAYCOMPLEX_CC
#define BZ_ARRAYCOMPLEX_CC

#ifndef BZ_ARRAY_H
 #error <blitz/array/complex.cc> must be included via <blitz/array/array.h>
#endif

BZ_NAMESPACE(blitz)

#ifdef BZ_HAVE_COMPLEX

template<class T_numtype, int N_rank>
inline Array<T_numtype, N_rank> real(const Array<complex<T_numtype>,N_rank>& A)
{
    return A.extractComponent(T_numtype(), 0, 2);
}

template<class T_numtype, int N_rank>
inline Array<T_numtype, N_rank> imag(const Array<complex<T_numtype>,N_rank>& A)
{
    return A.extractComponent(T_numtype(), 1, 2);
}


#endif

BZ_NAMESPACE_END

#endif // BZ_ARRAYCOMPLEX_CC

