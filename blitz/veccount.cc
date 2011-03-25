/***************************************************************************
 * blitz/veccount.cc      Vector count method
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
#ifndef BZ_VECCOUNT_CC
#define BZ_VECCOUNT_CC

#ifndef BZ_VECGLOBS_H
 #error <blitz/veccount.cc> must be included via <blitz/vecglobs.h>
#endif

BZ_NAMESPACE(blitz)

template<typename P_expr>
inline int _bz_vec_count(P_expr vector)
{
    int length = vector._bz_suggestLength();
    int count = 0;

    if (vector._bz_hasFastAccess())
    {
        for (int i=0; i < length; ++i)
            if (vector._bz_fastAccess(i))
                ++count;
    }
    else {
        for (int i=0; i < length; ++i)
            if (vector[i])
                ++count;
    }

    return count;
}

template<typename P_numtype>
inline int count(const Vector<P_numtype>& x)
{
    return _bz_vec_count(x._bz_asVecExpr());
}

template<typename P_expr>
inline int count(_bz_VecExpr<P_expr> expr)
{
    return _bz_vec_count(expr);
}

template<typename P_numtype>
inline int count(const VectorPick<P_numtype>& x)
{
    return _bz_vec_count(x._bz_asVecExpr());
}

template<typename P_numtype, int N_dimensions>
inline int count(const TinyVector<P_numtype, N_dimensions>& x)
{
    return _bz_vec_count(x._bz_asVecExpr());
}

BZ_NAMESPACE_END

#endif // BZ_VECCOUNT_CC

