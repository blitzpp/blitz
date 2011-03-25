/***************************************************************************
 * blitz/vecaccum.cc      Vector accumulate methods
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
#ifndef BZ_VECACCUM_CC
#define BZ_VECACCUM_CC

#ifndef BZ_VECGLOBS_H
 #error <blitz/vecaccum.cc> must be included via <blitz/vecglobs.h>
#endif

BZ_NAMESPACE(blitz)

template<typename P>
inline
Vector<BZ_SUMTYPE(_bz_typename P::T_numtype)> _bz_vec_accumulate(P expr)
{
    typedef BZ_SUMTYPE(_bz_typename P::T_numtype) T_sumtype;
    int length = expr._bz_suggestLength();
    Vector<T_sumtype> z(length);
    T_sumtype sum = 0;

    if (expr._bz_hasFastAccess())
    {
        for (int i=0; i < length; ++i)
        {
            sum += expr._bz_fastAccess(i);
            z[i] = sum;
        }
    }
    else {
        for (int i=0; i < length; ++i)
        {
            sum += expr(i);
            z[i] = sum;
        }
    }

    return z;
}
template<typename P_numtype>
Vector<BZ_SUMTYPE(P_numtype)> accumulate(const Vector<P_numtype>& x)
{
    return _bz_vec_accumulate(x);
}

template<typename P_expr>
Vector<BZ_SUMTYPE(_bz_typename P_expr::T_numtype)>
accumulate(_bz_VecExpr<P_expr> x)
{
    return _bz_vec_accumulate(x);
}

template<typename P_numtype>
Vector<BZ_SUMTYPE(P_numtype)> accumulate(const VectorPick<P_numtype>& x)
{
    return _bz_vec_accumulate(x);
}

BZ_NAMESPACE_END

#endif // BZ_VECACCUM_CC

