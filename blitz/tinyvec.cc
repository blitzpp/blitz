/***************************************************************************
 * blitz/tinyvec.cc  Declaration of TinyVector methods
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
 * Revision 1.4  2002/06/27 00:09:37  jcumming
 * Changed T_numtype to P_numtype when used outside the argument list or body
 * of a member function definition (i.e., outside the class scope).  Inside
 * the class scope, we can use the typedef T_numtype.  The IBM xlC compiler
 * gets confused if P_numtype is used as a template parameter name in a member
 * function declaration and then T_numtype is used as the parameter name in
 * the member function definition.  Fixed usage to be more consistent.
 *
 * Revision 1.3  2001/01/25 00:25:55  tveldhui
 * Ensured that source files have cvs logs.
 *
 */

#ifndef BZ_TINYVEC_CC
#define BZ_TINYVEC_CC

#ifndef BZ_TINYVEC_H
 #include <blitz/tinyvec.h>
#endif

#ifndef BZ_VECTOR_H
 #include <blitz/vector.h>
#endif

#ifndef BZ_RANGE_H
 #include <blitz/range.h>
#endif

#include <blitz/meta/vecassign.h>

BZ_NAMESPACE(blitz)

template<class P_numtype, int N_length>
inline TinyVector<P_numtype, N_length>::TinyVector(T_numtype initValue)
{
    for (int i=0; i < N_length; ++i)
        data_[i] = initValue;
}

template<class P_numtype, int N_length>
inline TinyVector<P_numtype, N_length>::TinyVector(const 
    TinyVector<T_numtype, N_length>& x)
{
    for (int i=0; i < N_length; ++i)
        data_[i] = x.data_[i];
}

template<class P_numtype, int N_length> template<class P_expr, class P_updater>
inline
void TinyVector<P_numtype, N_length>::_bz_assign(P_expr expr, P_updater up)
{
    BZPRECHECK(expr.length(N_length) == N_length,
        "An expression with length " << expr.length(N_length)
        << " was assigned to a TinyVector<"
        << BZ_DEBUG_TEMPLATE_AS_STRING_LITERAL(T_numtype)
        << "," << N_length << ">");

    if (expr._bz_hasFastAccess())
    {
        _bz_meta_vecAssign<N_length, 0>::fastAssign(*this, expr, up);
    }
    else {
        _bz_meta_vecAssign<N_length, 0>::assign(*this, expr, up);
    }
}

// Constructor added by Peter Nordlund (peter.nordlund@ind.af.se)
template<class P_numtype, int N_length> template<class P_expr>
inline TinyVector<P_numtype, N_length>::TinyVector(_bz_VecExpr<P_expr> expr) 
{
  _bz_assign(expr, _bz_update<T_numtype, _bz_typename P_expr::T_numtype>());
}

/*****************************************************************************
 * Assignment operators with vector expression operand
 */

template<class P_numtype, int N_length> template<class P_expr>
inline TinyVector<P_numtype, N_length>& 
TinyVector<P_numtype, N_length>::operator=(_bz_VecExpr<P_expr> expr)
{
    _bz_assign(expr, _bz_update<T_numtype, _bz_typename P_expr::T_numtype>());
    return *this;
}

template<class P_numtype, int N_length> template<class P_expr>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator+=(_bz_VecExpr<P_expr> expr)
{
    _bz_assign(expr, _bz_plus_update<T_numtype, 
        _bz_typename P_expr::T_numtype>());
    return *this;
}

template<class P_numtype, int N_length> template<class P_expr>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator-=(_bz_VecExpr<P_expr> expr)
{
    _bz_assign(expr, _bz_minus_update<T_numtype,
        _bz_typename P_expr::T_numtype>());
    return *this;
}

template<class P_numtype, int N_length> template<class P_expr>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator*=(_bz_VecExpr<P_expr> expr)
{
    _bz_assign(expr, _bz_multiply_update<T_numtype,
        _bz_typename P_expr::T_numtype>());
    return *this;
}

template<class P_numtype, int N_length> template<class P_expr>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator/=(_bz_VecExpr<P_expr> expr)
{
    _bz_assign(expr, _bz_divide_update<T_numtype,
        _bz_typename P_expr::T_numtype>());
    return *this;
}

template<class P_numtype, int N_length> template<class P_expr>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator%=(_bz_VecExpr<P_expr> expr)
{
    _bz_assign(expr, _bz_mod_update<T_numtype,
        _bz_typename P_expr::T_numtype>());
    return *this;
}

template<class P_numtype, int N_length> template<class P_expr>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator^=(_bz_VecExpr<P_expr> expr)
{
    _bz_assign(expr, _bz_xor_update<T_numtype,
        _bz_typename P_expr::T_numtype>());
    return *this;
}

template<class P_numtype, int N_length> template<class P_expr>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator&=(_bz_VecExpr<P_expr> expr)
{
    _bz_assign(expr, _bz_bitand_update<T_numtype,
        _bz_typename P_expr::T_numtype>());
    return *this;
}

template<class P_numtype, int N_length> template<class P_expr>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator|=(_bz_VecExpr<P_expr> expr)
{
    _bz_assign(expr, _bz_bitor_update<T_numtype,
        _bz_typename P_expr::T_numtype>());
    return *this;
}

template<class P_numtype, int N_length> template<class P_expr>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator<<=(_bz_VecExpr<P_expr> expr)
{
    _bz_assign(expr, _bz_shiftl_update<T_numtype,
        _bz_typename P_expr::T_numtype>());
    return *this;
}

template<class P_numtype, int N_length> template<class P_expr>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator>>=(_bz_VecExpr<P_expr> expr)
{
    _bz_assign(expr, _bz_shiftr_update<T_numtype,
        _bz_typename P_expr::T_numtype>());
    return *this;
}

/*****************************************************************************
 * Assignment operators with scalar operand
 */

template<class P_numtype, int N_length> 
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::initialize(T_numtype x)
{
#ifndef BZ_KCC_COPY_PROPAGATION_KLUDGE
    typedef _bz_VecExprConstant<T_numtype> T_expr;
    (*this) = _bz_VecExpr<T_expr>(T_expr(x));
#else
    // Avoid using the copy propagation kludge for this simple
    // operation.
    for (int i=0; i < N_length; ++i)
        data_[i] = x;
#endif
    return *this;
}

template<class P_numtype, int N_length>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator+=(T_numtype x)
{
    typedef _bz_VecExprConstant<T_numtype> T_expr;
    (*this) += _bz_VecExpr<T_expr>(T_expr(x));
    return *this;
}

template<class P_numtype, int N_length>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator-=(T_numtype x)
{
    typedef _bz_VecExprConstant<T_numtype> T_expr;
    (*this) -= _bz_VecExpr<T_expr>(T_expr(x));
    return *this;
}

template<class P_numtype, int N_length>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator*=(T_numtype x)
{
    typedef _bz_VecExprConstant<T_numtype> T_expr;
    (*this) *= _bz_VecExpr<T_expr>(T_expr(x));
    return *this;
}

template<class P_numtype, int N_length>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator/=(T_numtype x)
{
    typedef _bz_VecExprConstant<T_numtype> T_expr;
    (*this) /= _bz_VecExpr<T_expr>(T_expr(x));
    return *this;
}

template<class P_numtype, int N_length>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator%=(T_numtype x)
{
    typedef _bz_VecExprConstant<T_numtype> T_expr;
    (*this) %= _bz_VecExpr<T_expr>(T_expr(x));
    return *this;
}

template<class P_numtype, int N_length>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator^=(T_numtype x)
{
    typedef _bz_VecExprConstant<T_numtype> T_expr;
    (*this) ^= _bz_VecExpr<T_expr>(T_expr(x));
    return *this;
}

template<class P_numtype, int N_length>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator&=(T_numtype x)
{
    typedef _bz_VecExprConstant<T_numtype> T_expr;
    (*this) &= _bz_VecExpr<T_expr>(T_expr(x));
    return *this;
}

template<class P_numtype, int N_length>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator|=(T_numtype x)
{
    typedef _bz_VecExprConstant<T_numtype> T_expr;
    (*this) |= _bz_VecExpr<T_expr>(T_expr(x));
    return *this;
}

template<class P_numtype, int N_length>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator<<=(int x)
{
    typedef _bz_VecExprConstant<int> T_expr;
    (*this) <<= _bz_VecExpr<T_expr>(T_expr(x));
    return *this;
}

template<class P_numtype, int N_length>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator>>=(int x)
{
    typedef _bz_VecExprConstant<int> T_expr;
    (*this) >>= _bz_VecExpr<T_expr>(T_expr(x));
    return *this;
}

/*****************************************************************************
 * Assignment operators with TinyVector operand
 */

template<class P_numtype, int N_length> template<class P_numtype2>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator=(const 
    TinyVector<P_numtype2, N_length>& x)
{
    (*this) = _bz_VecExpr<_bz_typename 
        TinyVector<P_numtype2, N_length>::T_constIterator>(x.begin());
    return *this;
}

template<class P_numtype, int N_length> template<class P_numtype2>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator+=(const
    TinyVector<P_numtype2, N_length>& x)
{
    (*this) += _bz_VecExpr<_bz_typename
        TinyVector<P_numtype2, N_length>::T_constIterator>(x.begin());
    return *this;
}

template<class P_numtype, int N_length> template<class P_numtype2>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator-=(const
    TinyVector<P_numtype2, N_length>& x)
{
    (*this) -= _bz_VecExpr<_bz_typename
        TinyVector<P_numtype2, N_length>::T_constIterator>(x.begin());
    return *this;
}

template<class P_numtype, int N_length> template<class P_numtype2>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator*=(const
    TinyVector<P_numtype2, N_length>& x)
{
    (*this) *= _bz_VecExpr<_bz_typename
        TinyVector<P_numtype2, N_length>::T_constIterator>(x.begin());
    return *this;
}

template<class P_numtype, int N_length> template<class P_numtype2>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator/=(const
    TinyVector<P_numtype2, N_length>& x)
{
    (*this) /= _bz_VecExpr<_bz_typename
        TinyVector<P_numtype2, N_length>::T_constIterator>(x.begin());
    return *this;
}

template<class P_numtype, int N_length> template<class P_numtype2>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator%=(const
    TinyVector<P_numtype2, N_length>& x)
{
    (*this) %= _bz_VecExpr<_bz_typename
        TinyVector<P_numtype2, N_length>::T_constIterator>(x.begin());
    return *this;
}

template<class P_numtype, int N_length> template<class P_numtype2>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator^=(const
    TinyVector<P_numtype2, N_length>& x)
{
    (*this) ^= _bz_VecExpr<_bz_typename
        TinyVector<P_numtype2, N_length>::T_constIterator>(x.begin());
    return *this;
}

template<class P_numtype, int N_length> template<class P_numtype2>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator&=(const
    TinyVector<P_numtype2, N_length>& x)
{
    (*this) &= _bz_VecExpr<_bz_typename
        TinyVector<P_numtype2, N_length>::T_constIterator>(x.begin());
    return *this;
}

template<class P_numtype, int N_length> template<class P_numtype2>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator|=(const
    TinyVector<P_numtype2, N_length>& x)
{
    (*this) |= _bz_VecExpr<_bz_typename
        TinyVector<P_numtype2, N_length>::T_constIterator>(x.begin());
    return *this;
}

template<class P_numtype, int N_length> template<class P_numtype2>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator<<=(const
    TinyVector<P_numtype2, N_length>& x)
{
    (*this) <<= _bz_VecExpr<_bz_typename
        TinyVector<P_numtype2, N_length>::T_constIterator>(x.begin());
    return *this;
}

template<class P_numtype, int N_length> template<class P_numtype2>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator>>=(const
    TinyVector<P_numtype2, N_length>& x)
{
    (*this) >>= _bz_VecExpr<_bz_typename
        TinyVector<P_numtype2, N_length>::T_constIterator>(x.begin());
    return *this;
}

/*****************************************************************************
 * Assignment operators with Vector operand
 */

template<class P_numtype, int N_length> template<class P_numtype2>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator=(const Vector<P_numtype2>& x)
{
    (*this) = x._bz_asVecExpr();
    return *this;
}

template<class P_numtype, int N_length> template<class P_numtype2>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator+=(const Vector<P_numtype2>& x)
{
    (*this) += x._bz_asVecExpr();
    return *this;
}

template<class P_numtype, int N_length> template<class P_numtype2>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator-=(const Vector<P_numtype2>& x)
{
    (*this) -= x._bz_asVecExpr();
    return *this;
}

template<class P_numtype, int N_length> template<class P_numtype2>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator*=(const Vector<P_numtype2>& x)
{
    (*this) *= x._bz_asVecExpr();
    return *this;
}

template<class P_numtype, int N_length> template<class P_numtype2>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator/=(const Vector<P_numtype2>& x)
{
    (*this) /= x._bz_asVecExpr();
    return *this;
}

template<class P_numtype, int N_length> template<class P_numtype2>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator%=(const Vector<P_numtype2>& x)
{
    (*this) %= x._bz_asVecExpr();
    return *this;
}

template<class P_numtype, int N_length> template<class P_numtype2>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator^=(const Vector<P_numtype2>& x)
{
    (*this) ^= x._bz_asVecExpr();
    return *this;
}

template<class P_numtype, int N_length> template<class P_numtype2>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator&=(const Vector<P_numtype2>& x)
{
    (*this) &= x._bz_asVecExpr();
    return *this;
}

template<class P_numtype, int N_length> template<class P_numtype2>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator|=(const Vector<P_numtype2>& x)
{
    (*this) |= x._bz_asVecExpr();
    return *this;
}

template<class P_numtype, int N_length> template<class P_numtype2>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator<<=(const Vector<P_numtype2>& x)
{
    (*this) <<= x._bz_asVecExpr();
    return *this;
}

template<class P_numtype, int N_length> template<class P_numtype2>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator>>=(const Vector<P_numtype2>& x)
{
    (*this) >>= x._bz_asVecExpr();
    return *this;
}

/*****************************************************************************
 * Assignment operators with Range operand
 */

template<class P_numtype, int N_length> 
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator=(Range r)
{
    (*this) = r._bz_asVecExpr();
    return *this;
}

template<class P_numtype, int N_length>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator+=(Range r)
{
    (*this) += r._bz_asVecExpr();
    return *this;
}

template<class P_numtype, int N_length>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator-=(Range r)
{
    (*this) -= r._bz_asVecExpr();
    return *this;
}

template<class P_numtype, int N_length>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator*=(Range r)
{
    (*this) *= r._bz_asVecExpr();
    return *this;
}

template<class P_numtype, int N_length>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator/=(Range r)
{
    (*this) /= r._bz_asVecExpr();
    return *this;
}

template<class P_numtype, int N_length>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator%=(Range r)
{
    (*this) %= r._bz_asVecExpr();
    return *this;
}

template<class P_numtype, int N_length>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator^=(Range r)
{
    (*this) ^= r._bz_asVecExpr();
    return *this;
}

template<class P_numtype, int N_length>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator&=(Range r)
{
    (*this) &= r._bz_asVecExpr();
    return *this;
}

template<class P_numtype, int N_length>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator|=(Range r)
{
    (*this) |= r._bz_asVecExpr();
    return *this;
}

template<class P_numtype, int N_length>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator<<=(Range r)
{
    (*this) <<= r._bz_asVecExpr();
    return *this;
}

template<class P_numtype, int N_length>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator>>=(Range r)
{
    (*this) >>= r._bz_asVecExpr();
    return *this;
}

/*****************************************************************************
 * Assignment operators with VectorPick operand
 */

template<class P_numtype, int N_length> template<class P_numtype2>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator=(const VectorPick<P_numtype2>& x)
{
    (*this) = x._bz_asVecExpr();
    return *this;
}

template<class P_numtype, int N_length> template<class P_numtype2>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator+=(const VectorPick<P_numtype2>& x)
{
    (*this) += x._bz_asVecExpr();
    return *this;
}

template<class P_numtype, int N_length> template<class P_numtype2>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator-=(const VectorPick<P_numtype2>& x)
{
    (*this) -= x._bz_asVecExpr();
    return *this;
}

template<class P_numtype, int N_length> template<class P_numtype2>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator*=(const VectorPick<P_numtype2>& x)
{
    (*this) *= x._bz_asVecExpr();
    return *this;
}

template<class P_numtype, int N_length> template<class P_numtype2>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator/=(const VectorPick<P_numtype2>& x)
{
    (*this) /= x._bz_asVecExpr();
    return *this;
}

template<class P_numtype, int N_length> template<class P_numtype2>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator%=(const VectorPick<P_numtype2>& x)
{
    (*this) %= x._bz_asVecExpr();
    return *this;
}

template<class P_numtype, int N_length> template<class P_numtype2>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator^=(const VectorPick<P_numtype2>& x)
{
    (*this) ^= x._bz_asVecExpr();
    return *this;
}

template<class P_numtype, int N_length> template<class P_numtype2>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator&=(const VectorPick<P_numtype2>& x)
{
    (*this) &= x._bz_asVecExpr();
    return *this;
}

template<class P_numtype, int N_length> template<class P_numtype2>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator|=(const VectorPick<P_numtype2>& x)
{
    (*this) |= x._bz_asVecExpr();
    return *this;
}

template<class P_numtype, int N_length> template<class P_numtype2>
inline TinyVector<P_numtype, N_length>&
TinyVector<P_numtype, N_length>::operator>>=(const VectorPick<P_numtype2>& x)
{
    (*this) <<= x._bz_asVecExpr();
    return *this;
}

BZ_NAMESPACE_END

#endif // BZ_TINYVEC_CC
