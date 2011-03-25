/***************************************************************************
 * blitz/vecmin.cc      Vector min method
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
#ifndef BZ_VECMIN_CC
#define BZ_VECMIN_CC

#ifndef BZ_VECGLOBS_H
 #error <blitz/vecmin.cc> must be included via <blitz/vecglobs.h>
#endif

BZ_NAMESPACE(blitz)

template<typename P_expr>
inline
Extremum<_bz_typename P_expr::T_numtype, int> _bz_vec_min(P_expr vector)
{
    typedef _bz_typename P_expr::T_numtype T_numtype;

    T_numtype minValue = vector(0);
    int minIndex = 0;
    int length = vector._bz_suggestLength();

    if (vector._bz_hasFastAccess())
    {
        for (int i=1; i < length; ++i)
        {
            T_numtype value = vector._bz_fastAccess(i);
            if (value < minValue)
            {
                minValue = value;
                minIndex = i;
            }
        }
    }
    else {
        for (int i=1; i < length; ++i)
        {
            T_numtype value = vector(i);
            if (value < minValue)
            {
                minValue = value;
                minIndex = i;
            }
        }
    }

    return Extremum<T_numtype, int>(minValue, minIndex);
}

// min(vector)
template<typename P_numtype>
inline
Extremum<P_numtype,int> (min)(const Vector<P_numtype>& x)
{
    return _bz_vec_min(x._bz_asVecExpr());
}

// min(expr)
template<typename P_expr>
inline
Extremum<_bz_typename P_expr::T_numtype,int> (min)(_bz_VecExpr<P_expr> x)
{
    return _bz_vec_min(x);
}

// min(vecpick)
template<typename P_numtype>
inline
Extremum<P_numtype, int> (min)(const VectorPick<P_numtype>& x)
{
    return _bz_vec_min(x._bz_asVecExpr());
}

// min(TinyVector)
template<typename P_numtype, int N_length>
inline
Extremum<P_numtype, int> (min)(const TinyVector<P_numtype, N_length>& x)
{
    return _bz_vec_min(x._bz_asVecExpr());
}

// minIndex(vector)
template<typename P_numtype>
inline
int minIndex(const Vector<P_numtype>& x)
{
    return _bz_vec_min(x._bz_asVecExpr()).index();
}

// maxIndex(expr)
template<typename P_expr>
inline
int minIndex(_bz_VecExpr<P_expr> x)
{
    return _bz_vec_min(x).index();
}

// minIndex(vecpick)
template<typename P_numtype>
int minIndex(const VectorPick<P_numtype>& x)
{
    return _bz_vec_min(x._bz_asVecExpr()).index();
}

// minIndex(TinyVector)
template<typename P_numtype, int N_length>
int minIndex(const TinyVector<P_numtype, N_length>& x)
{
    return _bz_vec_min(x._bz_asVecExpr()).index();
}

// minValue(vector)
template<typename P_numtype>
inline
int minValue(const Vector<P_numtype>& x)
{
    return _bz_vec_min(x._bz_asVecExpr()).value();
}

// minValue(expr)
template<typename P_expr>
inline
int minValue(_bz_VecExpr<P_expr> x)
{
    return _bz_vec_min(x).value();
}

// minValue(vecpick)
template<typename P_numtype>
int minValue(const VectorPick<P_numtype>& x)
{
    return _bz_vec_min(x._bz_asVecExpr()).value();
}

// minValue(TinyVector)
template<typename P_numtype, int N_length>
int minValue(const TinyVector<P_numtype, N_length>& x)
{
    return _bz_vec_min(x._bz_asVecExpr()).value();
}

BZ_NAMESPACE_END

#endif // BZ_VECMIN_CC

