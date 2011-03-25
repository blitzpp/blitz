/***************************************************************************
 * blitz/vecany.cc      Vector any method
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
#ifndef BZ_VECANY_CC
#define BZ_VECANY_CC

#ifndef BZ_VECGLOBS_H
 #error <blitz/vecany.cc> must be included via <blitz/vecglobs.h>
#endif

BZ_NAMESPACE(blitz)

template<typename P_expr>
inline bool _bz_vec_any(P_expr vector)
{
    int length = vector._bz_suggestLength();

    if (vector._bz_hasFastAccess())
    {
        for (int i=0; i < length; ++i)
            if (vector._bz_fastAccess(i))
                return true;
    }
    else {
        for (int i=0; i < length; ++i)
            if (vector[i])
                return true;
    }

    return false;
}

template<typename P_numtype>
inline bool any(const Vector<P_numtype>& x)
{
    return _bz_vec_any(x._bz_asVecExpr());
}

template<typename P_expr>
inline bool any(_bz_VecExpr<P_expr> expr)
{
    return _bz_vec_any(expr);
}

template<typename P_numtype>
inline bool any(const VectorPick<P_numtype>& x)
{
    return _bz_vec_any(x._bz_asVecExpr());
}

template<typename P_numtype, int N_dimensions>
inline bool any(const TinyVector<P_numtype, N_dimensions>& x)
{
    return _bz_vec_any(x._bz_asVecExpr());
}

BZ_NAMESPACE_END

#endif // BZ_VECANY_CC

