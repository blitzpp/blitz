/*
 * $Id$
 *
 * Copyright (C) 1997 Todd Veldhuizen <tveldhui@oonumerics.org>
 * All rights reserved.  Please see <blitz/blitz.h> for terms and
 * conditions of use.
 *
 */

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

