/***************************************************************************
 * blitz/array/convolve.cc  One-dimensional convolution
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

#ifndef BZ_ARRAY_CONVOLVE_CC
#define BZ_ARRAY_CONVOLVE_CC

BZ_NAMESPACE(blitz)

template<class T>
Array<T,1> convolve(const Array<T,1>& B, const Array<T,1>& C)
{
    int Bl = B.lbound(0), Bh = B.ubound(0);
    int Cl = C.lbound(0), Ch = C.ubound(0);

    int lbound = Bl + Cl;
    int ubound = Bh + Ch;
    
    Array<T,1> A(Range(lbound,ubound));

    for (int i=lbound; i <= ubound; ++i)
    {
        int jl = i - Ch;
        if (jl < Bl)
            jl = Bl;

        int jh = i - Cl;
        if (jh > Bh)
            jh = Bh;

        T result = 0;
        for (int j=jl; j <= jh; ++j)
            result += B(j) * C(i-j);

        A(i) = result;
    }

    return A;
}

BZ_NAMESPACE_END

#endif // BZ_ARRAY_CONVOLVE_CC

