/***************************************************************************
 * blitz/vecdelta.cc      Vector delta method
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
#ifndef BZ_VECDELTA_CC
#define BZ_VECDELTA_CC

#ifndef BZ_VECGLOBS_H
 #error <blitz/vecdelta.cc> must be included via <blitz/vecglobs.h>
#endif

BZ_NAMESPACE(blitz)

template<typename P>
inline
Vector<BZ_DIFFTYPE(_bz_typename P::T_numtype)> _bz_vec_delta(P expr)
{
    typedef _bz_typename P::T_numtype   T_numtype;
    typedef BZ_DIFFTYPE(T_numtype)      T_difftype;

    int length = expr._bz_suggestLength();
    Vector<T_difftype> z(length);
    T_numtype currentElement = 0;
    T_numtype previousElement = 0;

    if (expr._bz_hasFastAccess())
    {
        for (int i=0; i < length; ++i)
        {
            currentElement = expr._bz_fastAccess(i);
            z[i] = currentElement - previousElement;
            previousElement = currentElement;
        }
    }
    else {
        for (int i=1; i < length; ++i)
        {
            currentElement = expr(i);
            z[i] = currentElement - previousElement;
            previousElement = currentElement;
        }
    }

    return z;
}

template<typename P_numtype>
Vector<BZ_DIFFTYPE(P_numtype)> delta(const Vector<P_numtype>& x)
{
    return _bz_vec_delta(x);
}

// delta(expr)
template<typename P_expr>
Vector<BZ_DIFFTYPE(_bz_typename P_expr::T_numtype)> delta(_bz_VecExpr<P_expr> x)
{
    return _bz_vec_delta(x);
}

// delta(vecpick)
template<typename P_numtype>
Vector<BZ_DIFFTYPE(P_numtype)> delta(const VectorPick<P_numtype>& x)
{
    return _bz_vec_delta(x);
}

BZ_NAMESPACE_END

#endif // BZ_VECDELTA_CC

