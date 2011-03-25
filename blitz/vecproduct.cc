/***************************************************************************
 * blitz/vecproduct.cc      Vector product method
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
#ifndef BZ_VECPRODUCT_CC
#define BZ_VECPRODUCT_CC

#ifndef BZ_VECGLOBS_H
 #error <blitz/vecproduct.cc> must be included via <blitz/vecglobs.h>
#endif

BZ_NAMESPACE(blitz)

template<typename P_expr>
inline
BZ_SUMTYPE(_bz_typename P_expr::T_numtype)
_bz_vec_product(P_expr vector)
{
    typedef _bz_typename P_expr::T_numtype T_numtype;
    typedef BZ_SUMTYPE(T_numtype)          T_sumtype;

    T_sumtype product = vector(0);
    int length = vector._bz_suggestLength();

    if (vector._bz_hasFastAccess())
    {
        for (int i=1; i < length; ++i)
            product *= vector._bz_fastAccess(i);
    }
    else {
        for (int i=1; i < length; ++i)
            product *= vector(i);
    }

    return product;
}

template<typename P_numtype>
inline
BZ_SUMTYPE(P_numtype) product(const Vector<P_numtype>& x)
{
    return _bz_vec_product(x._bz_asVecExpr());
}

// product(expr)
template<typename P_expr>
inline
BZ_SUMTYPE(_bz_typename P_expr::T_numtype)
product(_bz_VecExpr<P_expr> expr)
{
    return _bz_vec_product(expr);
}

// product(vecpick)
template<typename P_numtype>
inline
BZ_SUMTYPE(P_numtype)
product(const VectorPick<P_numtype>& x)
{
    return _bz_vec_product(x._bz_asVecExpr());
}

BZ_NAMESPACE_END

#endif // BZ_VECPRODUCT_CC

