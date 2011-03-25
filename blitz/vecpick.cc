/***************************************************************************
 * blitz/vecpick.cc      VectorPick methods
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
#ifndef BZ_VECPICK_CC
#define BZ_VECPICK_CC

#include <blitz/vecpick.h>
#include <blitz/update.h>
#include <blitz/random.h>
#include <blitz/vecexpr.h>

BZ_NAMESPACE(blitz)

/*****************************************************************************
 * Assignment operators with vector expression operand
 */

template<typename P_numtype> template<typename P_expr, typename P_updater>
inline
void VectorPick<P_numtype>::_bz_assign(P_expr expr, P_updater)
{
    BZPRECONDITION(expr.length(length()) == length());

    // If all vectors in the expression, plus the vector to which the
    // result is being assigned have unit stride, then avoid stride
    // calculations.
    if (_bz_hasFastAccess() && expr._bz_hasFastAccess())
    {
#ifndef BZ_PARTIAL_LOOP_UNROLL
        for (int i=0; i < length(); ++i)
            P_updater::update(vector_(index_(i)), expr._bz_fastAccess(i));
#else
        // Unwind the inner loop, five elements at a time.
        int leftover = length() % 5;

        int i=0;
        for (; i < leftover; ++i)
            P_updater::update(vector_(index_(i)), expr._bz_fastAccess(i));

        for (; i < length(); i += 5)
        {
            P_updater::update(vector_(index_(i)), expr._bz_fastAccess(i));
            P_updater::update(vector_(index_(i+1)), expr._bz_fastAccess(i+1));
            P_updater::update(vector_(index_(i+2)), expr._bz_fastAccess(i+2));
            P_updater::update(vector_(index_(i+3)), expr._bz_fastAccess(i+3));
            P_updater::update(vector_(index_(i+4)), expr._bz_fastAccess(i+4));
        }
#endif
    }
    else {
        // Not all unit strides -- have to access all the vector elements
        // as data_[i*stride_], which is slower.
        for (int i=0; i < length(); ++i)
            P_updater::update(vector_[index_[i]], expr[i]);
    }
}

template<typename P_numtype> template<typename P_expr>
inline VectorPick<P_numtype>& 
VectorPick<P_numtype>::operator=(_bz_VecExpr<P_expr> expr)
{
    BZPRECONDITION(expr.length(length()) == length());

    // If all vectors in the expression, plus the vector to which the
    // result is being assigned have unit stride, then avoid stride
    // calculations.
    if (_bz_hasFastAccess() && expr._bz_hasFastAccess())
    {
#ifndef BZ_PARTIAL_LOOP_UNROLL
        for (int i=0; i < length(); ++i)
            (*this)(i) = expr._bz_fastAccess(i);
#else
        // Unwind the inner loop, five elements at a time.
        int leftover = length() % 5;

        int i=0;
        for (; i < leftover; ++i)
            (*this)(i) = expr._bz_fastAccess(i);

        for (; i < length(); i += 5)
        {
            (*this)(i) = expr._bz_fastAccess(i);
            (*this)(i+1) = expr._bz_fastAccess(i+1);
            (*this)(i+2) = expr._bz_fastAccess(i+2);
            (*this)(i+3) = expr._bz_fastAccess(i+3);
            (*this)(i+4) = expr._bz_fastAccess(i+4);
        }
#endif
    }
    else {
        // Not all unit strides -- have to access all the vector elements
        // as data_[i*stride_], which is slower.
        for (int i=0; i < length(); ++i)
            (*this)[i] = expr[i];
    }
    return *this;
}


template<typename P_numtype> template<typename P_expr>
inline VectorPick<P_numtype>& 
VectorPick<P_numtype>::operator+=(_bz_VecExpr<P_expr> expr)
{
    _bz_assign(expr, _bz_plus_update<P_numtype,
        _bz_typename P_expr::T_numtype>());
    return *this;
}

template<typename P_numtype> template<typename P_expr>
inline VectorPick<P_numtype>& 
VectorPick<P_numtype>::operator-=(_bz_VecExpr<P_expr> expr)
{
    _bz_assign(expr, _bz_minus_update<P_numtype,
        _bz_typename P_expr::T_numtype>());
    return *this;
}

template<typename P_numtype> template<typename P_expr>
inline VectorPick<P_numtype>& 
VectorPick<P_numtype>::operator*=(_bz_VecExpr<P_expr> expr)
{
    _bz_assign(expr, _bz_multiply_update<P_numtype,
        _bz_typename P_expr::T_numtype>());
    return *this;
}

template<typename P_numtype> template<typename P_expr>
inline VectorPick<P_numtype>& 
VectorPick<P_numtype>::operator/=(_bz_VecExpr<P_expr> expr)
{
    _bz_assign(expr, _bz_divide_update<P_numtype,
        _bz_typename P_expr::T_numtype>());
    return *this;
}

template<typename P_numtype> template<typename P_expr>
inline VectorPick<P_numtype>& 
VectorPick<P_numtype>::operator%=(_bz_VecExpr<P_expr> expr)
{
    _bz_assign(expr, _bz_mod_update<P_numtype,
        _bz_typename P_expr::T_numtype>());
    return *this;
}

template<typename P_numtype> template<typename P_expr>
inline VectorPick<P_numtype>& 
VectorPick<P_numtype>::operator^=(_bz_VecExpr<P_expr> expr)
{
    _bz_assign(expr, _bz_xor_update<P_numtype,
        _bz_typename P_expr::T_numtype>());
    return *this;
}

template<typename P_numtype> template<typename P_expr>
inline VectorPick<P_numtype>& 
VectorPick<P_numtype>::operator&=(_bz_VecExpr<P_expr> expr)
{
    _bz_assign(expr, _bz_bitand_update<P_numtype,
        _bz_typename P_expr::T_numtype>());
    return *this;
}

template<typename P_numtype> template<typename P_expr>
inline VectorPick<P_numtype>& 
VectorPick<P_numtype>::operator|=(_bz_VecExpr<P_expr> expr)
{
    _bz_assign(expr, _bz_bitor_update<P_numtype,
        _bz_typename P_expr::T_numtype>());
    return *this;
}

template<typename P_numtype> template<typename P_expr>
inline VectorPick<P_numtype>& 
VectorPick<P_numtype>::operator>>=(_bz_VecExpr<P_expr> expr)
{
    _bz_assign(expr, _bz_shiftr_update<P_numtype,
        _bz_typename P_expr::T_numtype>());
    return *this;
}

template<typename P_numtype> template<typename P_expr>
inline VectorPick<P_numtype>& 
VectorPick<P_numtype>::operator<<=(_bz_VecExpr<P_expr> expr)
{
    _bz_assign(expr, _bz_shiftl_update<P_numtype,
        _bz_typename P_expr::T_numtype>());
    return *this;
}

/*****************************************************************************
 * Assignment operators with scalar operand
 */

template<typename P_numtype>
inline VectorPick<P_numtype>& VectorPick<P_numtype>::operator=(P_numtype x)
{
    typedef _bz_VecExprConstant<P_numtype> T_expr;
    (*this) = _bz_VecExpr<T_expr>(T_expr(x));
    return *this;
}

template<typename P_numtype>
inline VectorPick<P_numtype>& VectorPick<P_numtype>::operator+=(P_numtype x)
{
    typedef _bz_VecExprConstant<P_numtype> T_expr;
    (*this) += _bz_VecExpr<T_expr>(T_expr(x));
    return *this;
}

template<typename P_numtype>
inline VectorPick<P_numtype>& VectorPick<P_numtype>::operator-=(P_numtype x)
{
    typedef _bz_VecExprConstant<P_numtype> T_expr;
    (*this) -= _bz_VecExpr<T_expr>(T_expr(x));
    return *this;
}

template<typename P_numtype>
inline VectorPick<P_numtype>& VectorPick<P_numtype>::operator*=(P_numtype x)
{
    typedef _bz_VecExprConstant<P_numtype> T_expr;
    (*this) *= _bz_VecExpr<T_expr>(T_expr(x));
    return *this;
}

template<typename P_numtype>
inline VectorPick<P_numtype>& VectorPick<P_numtype>::operator/=(P_numtype x)
{
    typedef _bz_VecExprConstant<P_numtype> T_expr;
    (*this) /= _bz_VecExpr<T_expr>(T_expr(x));
    return *this;
}

template<typename P_numtype>
inline VectorPick<P_numtype>& VectorPick<P_numtype>::operator%=(P_numtype x)
{
    typedef _bz_VecExprConstant<P_numtype> T_expr;
    (*this) %= _bz_VecExpr<T_expr>(T_expr(x));
    return *this;
}

template<typename P_numtype>
inline VectorPick<P_numtype>& VectorPick<P_numtype>::operator^=(P_numtype x)
{
    typedef _bz_VecExprConstant<P_numtype> T_expr;
    (*this) ^= _bz_VecExpr<T_expr>(T_expr(x));
    return *this;
}

template<typename P_numtype>
inline VectorPick<P_numtype>& VectorPick<P_numtype>::operator&=(P_numtype x)
{
    typedef _bz_VecExprConstant<P_numtype> T_expr;
    (*this) &= _bz_VecExpr<T_expr>(T_expr(x));
    return *this;
}

template<typename P_numtype>
inline VectorPick<P_numtype>& VectorPick<P_numtype>::operator|=(P_numtype x)
{
    typedef _bz_VecExprConstant<P_numtype> T_expr;
    (*this) |= _bz_VecExpr<T_expr>(T_expr(x));
    return *this;
}

template<typename P_numtype>
inline VectorPick<P_numtype>& VectorPick<P_numtype>::operator>>=(int x)
{
    typedef _bz_VecExprConstant<int> T_expr;
    (*this) >>= _bz_VecExpr<T_expr>(T_expr(x));
    return *this;
}

template<typename P_numtype>
inline VectorPick<P_numtype>& VectorPick<P_numtype>::operator<<=(int x)
{
    typedef _bz_VecExprConstant<P_numtype> T_expr;
    (*this) <<= _bz_VecExpr<T_expr>(T_expr(x));
    return *this;
}

/*****************************************************************************
 * Assignment operators with vector operand
 */

template<typename P_numtype> template<typename P_numtype2>
inline VectorPick<P_numtype>& 
VectorPick<P_numtype>::operator=(const Vector<P_numtype2>& x)
{
    (*this) = _bz_VecExpr<VectorIterConst<P_numtype2> >(x.beginFast());
    return *this;
}

template<typename P_numtype> template<typename P_numtype2>
inline VectorPick<P_numtype>&
VectorPick<P_numtype>::operator+=(const Vector<P_numtype2>& x)
{
    (*this) += _bz_VecExpr<VectorIterConst<P_numtype2> >(x.beginFast());
    return *this;
}

template<typename P_numtype> template<typename P_numtype2>
inline VectorPick<P_numtype>&
VectorPick<P_numtype>::operator-=(const Vector<P_numtype2>& x)
{
    (*this) -= _bz_VecExpr<VectorIterConst<P_numtype2> >(x.beginFast());
    return *this;
}

template<typename P_numtype> template<typename P_numtype2>
inline VectorPick<P_numtype>&
VectorPick<P_numtype>::operator*=(const Vector<P_numtype2>& x)
{
    (*this) *= _bz_VecExpr<VectorIterConst<P_numtype2> >(x.beginFast());
    return *this;
}

template<typename P_numtype> template<typename P_numtype2>
inline VectorPick<P_numtype>&
VectorPick<P_numtype>::operator/=(const Vector<P_numtype2>& x)
{
    (*this) /= _bz_VecExpr<VectorIterConst<P_numtype2> >(x.beginFast());
    return *this;
}

template<typename P_numtype> template<typename P_numtype2>
inline VectorPick<P_numtype>&
VectorPick<P_numtype>::operator%=(const Vector<P_numtype2>& x)
{
    (*this) %= _bz_VecExpr<VectorIterConst<P_numtype2> >(x.beginFast());
    return *this;
}

template<typename P_numtype> template<typename P_numtype2>
inline VectorPick<P_numtype>&
VectorPick<P_numtype>::operator^=(const Vector<P_numtype2>& x)
{
    (*this) ^= _bz_VecExpr<VectorIterConst<P_numtype2> >(x.beginFast());
    return *this;
}

template<typename P_numtype> template<typename P_numtype2>
inline VectorPick<P_numtype>&
VectorPick<P_numtype>::operator&=(const Vector<P_numtype2>& x)
{
    (*this) &= _bz_VecExpr<VectorIterConst<P_numtype2> >(x.beginFast());
    return *this;
}

template<typename P_numtype> template<typename P_numtype2>
inline VectorPick<P_numtype>&
VectorPick<P_numtype>::operator|=(const Vector<P_numtype2>& x)
{
    (*this) |= _bz_VecExpr<VectorIterConst<P_numtype2> >(x.beginFast());
    return *this;
}

template<typename P_numtype> template<typename P_numtype2>
inline VectorPick<P_numtype>&
VectorPick<P_numtype>::operator<<=(const Vector<P_numtype2>& x)
{
    (*this) <<= _bz_VecExpr<VectorIterConst<P_numtype2> >(x.beginFast());
    return *this;
}

template<typename P_numtype> template<typename P_numtype2>
inline VectorPick<P_numtype>&
VectorPick<P_numtype>::operator>>=(const Vector<P_numtype2>& x)
{
    (*this) >>= _bz_VecExpr<VectorIterConst<P_numtype2> >(x.beginFast());
    return *this;
}

/*****************************************************************************
 * Assignment operators with Range operand
 */

template<typename P_numtype>
inline VectorPick<P_numtype>& VectorPick<P_numtype>::operator=(Range r)
{
    (*this) = _bz_VecExpr<Range>(r);
    return *this;
}

template<typename P_numtype>
inline VectorPick<P_numtype>& VectorPick<P_numtype>::operator+=(Range r)
{
    (*this) += _bz_VecExpr<Range>(r);
    return *this;
}

template<typename P_numtype>
inline VectorPick<P_numtype>& VectorPick<P_numtype>::operator-=(Range r)
{
    (*this) -= _bz_VecExpr<Range>(r);
    return *this;
}

template<typename P_numtype>
inline VectorPick<P_numtype>& VectorPick<P_numtype>::operator*=(Range r)
{
    (*this) *= _bz_VecExpr<Range>(r);
    return *this;
}

template<typename P_numtype>
inline VectorPick<P_numtype>& VectorPick<P_numtype>::operator/=(Range r)
{
    (*this) /= _bz_VecExpr<Range>(r);
    return *this;
}

template<typename P_numtype>
inline VectorPick<P_numtype>& VectorPick<P_numtype>::operator%=(Range r)
{
    (*this) %= _bz_VecExpr<Range>(r);
    return *this;
}

template<typename P_numtype>
inline VectorPick<P_numtype>& VectorPick<P_numtype>::operator^=(Range r)
{
    (*this) ^= _bz_VecExpr<Range>(r);
    return *this;
}

template<typename P_numtype>
inline VectorPick<P_numtype>& VectorPick<P_numtype>::operator&=(Range r)
{
    (*this) &= _bz_VecExpr<Range>(r);
    return *this;
}

template<typename P_numtype>
inline VectorPick<P_numtype>& VectorPick<P_numtype>::operator|=(Range r)
{
    (*this) |= _bz_VecExpr<Range>(r);
    return *this;
}

template<typename P_numtype>
inline VectorPick<P_numtype>& VectorPick<P_numtype>::operator>>=(Range r)
{
    (*this) >>= _bz_VecExpr<Range>(r);
    return *this;
}

template<typename P_numtype>
inline VectorPick<P_numtype>& VectorPick<P_numtype>::operator<<=(Range r)
{
    (*this) <<= _bz_VecExpr<Range>(r);
    return *this;
}

/*****************************************************************************
 * Assignment operators with VectorPick operand
 */

template<typename P_numtype> template<typename P_numtype2>
inline VectorPick<P_numtype>& VectorPick<P_numtype>::operator=(const 
    VectorPick<P_numtype2>& x)
{
    typedef VectorPickIterConst<P_numtype2> T_expr;
    (*this) = _bz_VecExpr<T_expr>(x.beginFast());
    return *this;
}

template<typename P_numtype> template<typename P_numtype2>
inline VectorPick<P_numtype>& VectorPick<P_numtype>::operator+=(const
    VectorPick<P_numtype2>& x)
{
    typedef VectorPickIterConst<P_numtype2> T_expr;
    (*this) += _bz_VecExpr<T_expr>(x.beginFast());
    return *this;
}


template<typename P_numtype> template<typename P_numtype2>
inline VectorPick<P_numtype>& VectorPick<P_numtype>::operator-=(const
    VectorPick<P_numtype2>& x)
{
    typedef VectorPickIterConst<P_numtype2> T_expr;
    (*this) -= _bz_VecExpr<T_expr>(x.beginFast());
    return *this;
}

template<typename P_numtype> template<typename P_numtype2>
inline VectorPick<P_numtype>& VectorPick<P_numtype>::operator*=(const
    VectorPick<P_numtype2>& x)
{
    typedef VectorPickIterConst<P_numtype2> T_expr;
    (*this) *= _bz_VecExpr<T_expr>(x.beginFast());
    return *this;
}

template<typename P_numtype> template<typename P_numtype2>
inline VectorPick<P_numtype>& VectorPick<P_numtype>::operator/=(const
    VectorPick<P_numtype2>& x)
{
    typedef VectorPickIterConst<P_numtype2> T_expr;
    (*this) /= _bz_VecExpr<T_expr>(x.beginFast());
    return *this;
}

template<typename P_numtype> template<typename P_numtype2>
inline VectorPick<P_numtype>& VectorPick<P_numtype>::operator%=(const
    VectorPick<P_numtype2>& x)
{
    typedef VectorPickIterConst<P_numtype2> T_expr;
    (*this) %= _bz_VecExpr<T_expr>(x.beginFast());
    return *this;
}

template<typename P_numtype> template<typename P_numtype2>
inline VectorPick<P_numtype>& VectorPick<P_numtype>::operator^=(const
    VectorPick<P_numtype2>& x)
{
    typedef VectorPickIterConst<P_numtype2> T_expr;
    (*this) ^= _bz_VecExpr<T_expr>(x.beginFast());
    return *this;
}

template<typename P_numtype> template<typename P_numtype2>
inline VectorPick<P_numtype>& VectorPick<P_numtype>::operator&=(const
    VectorPick<P_numtype2>& x)
{
    typedef VectorPickIterConst<P_numtype2> T_expr;
    (*this) &= _bz_VecExpr<T_expr>(x.beginFast());
    return *this;
}

template<typename P_numtype> template<typename P_numtype2>
inline VectorPick<P_numtype>& VectorPick<P_numtype>::operator|=(const
    VectorPick<P_numtype2>& x)
{
    typedef VectorPickIterConst<P_numtype2> T_expr;
    (*this) |= _bz_VecExpr<T_expr>(x.beginFast());
    return *this;
}

/*****************************************************************************
 * Assignment operators with Random operand
 */

template<typename P_numtype> template<typename P_distribution>
VectorPick<P_numtype>& 
VectorPick<P_numtype>::operator=(Random<P_distribution>& rand)
{
    (*this) = _bz_VecExpr<_bz_VecExprRandom<P_distribution> > 
        (_bz_VecExprRandom<P_distribution>(rand));
    return *this;
}

template<typename P_numtype> template<typename P_distribution>
VectorPick<P_numtype>& 
VectorPick<P_numtype>::operator+=(Random<P_distribution>& rand)
{
    (*this) += _bz_VecExpr<_bz_VecExprRandom<P_distribution> >
        (_bz_VecExprRandom<P_distribution>(rand));
    return *this;
}

template<typename P_numtype> template<typename P_distribution>
VectorPick<P_numtype>& 
VectorPick<P_numtype>::operator-=(Random<P_distribution>& rand)
{
    (*this) -= _bz_VecExpr<_bz_VecExprRandom<P_distribution> >
        (_bz_VecExprRandom<P_distribution>(rand));
    return *this;
}

template<typename P_numtype> template<typename P_distribution>
VectorPick<P_numtype>& 
VectorPick<P_numtype>::operator*=(Random<P_distribution>& rand)
{
    (*this) *= _bz_VecExpr<_bz_VecExprRandom<P_distribution> >
        (_bz_VecExprRandom<P_distribution>(rand));
    return *this;
}

template<typename P_numtype> template<typename P_distribution>
VectorPick<P_numtype>& 
VectorPick<P_numtype>::operator/=(Random<P_distribution>& rand)
{
    (*this) /= _bz_VecExpr<_bz_VecExprRandom<P_distribution> >
        (_bz_VecExprRandom<P_distribution>(rand));
    return *this;
}

template<typename P_numtype> template<typename P_distribution>
VectorPick<P_numtype>& 
VectorPick<P_numtype>::operator%=(Random<P_distribution>& rand)
{
    (*this) %= _bz_VecExpr<_bz_VecExprRandom<P_distribution> >
        (_bz_VecExprRandom<P_distribution>(rand));
    return *this;
}

template<typename P_numtype> template<typename P_distribution>
VectorPick<P_numtype>& 
VectorPick<P_numtype>::operator^=(Random<P_distribution>& rand)
{
    (*this) ^= _bz_VecExpr<_bz_VecExprRandom<P_distribution> >
        (_bz_VecExprRandom<P_distribution>(rand));
    return *this;
}

template<typename P_numtype> template<typename P_distribution>
VectorPick<P_numtype>& 
VectorPick<P_numtype>::operator&=(Random<P_distribution>& rand)
{
    (*this) &= _bz_VecExpr<_bz_VecExprRandom<P_distribution> >
        (_bz_VecExprRandom<P_distribution>(rand));
    return *this;
}

template<typename P_numtype> template<typename P_distribution>
VectorPick<P_numtype>& 
VectorPick<P_numtype>::operator|=(Random<P_distribution>& rand)
{
    (*this) |= _bz_VecExpr<_bz_VecExprRandom<P_distribution> >
        (_bz_VecExprRandom<P_distribution>(rand));
    return *this;
}

BZ_NAMESPACE_END

#endif // BZ_VECPICK_CC
