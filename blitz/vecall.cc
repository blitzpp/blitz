/*
 * $Id$
 *
 * Copyright (C) 1997 Todd Veldhuizen <tveldhui@oonumerics.org>
 * All rights reserved.  Please see <blitz/blitz.h> for terms and
 * conditions of use.
 *
 */

#ifndef BZ_VECALL_CC
#define BZ_VECALL_CC

#ifndef BZ_VECGLOBS_H
 #error <blitz/vecall.cc> must be included via <blitz/vecglobs.h>
#endif

BZ_NAMESPACE(blitz)

template<class P_expr>
inline _bz_bool _bz_vec_all(P_expr vector)
{
    int length = vector._bz_suggestLength();

    if (vector._bz_hasFastAccess())
    {
        for (int i=0; i < length; ++i)
            if (!vector._bz_fastAccess(i))
                return _bz_false;
    }
    else {
        for (int i=0; i < length; ++i)
            if (!vector[i])
                return _bz_false;
    }

    return _bz_true;
}

template<class P_numtype>
inline _bz_bool all(const Vector<P_numtype>& x)
{
    return _bz_vec_all(x._bz_asVecExpr());
}

template<class P_expr>
inline _bz_bool all(_bz_VecExpr<P_expr> expr)
{
    return _bz_vec_all(expr);
}

template<class P_numtype>
inline _bz_bool all(const VectorPick<P_numtype>& x)
{
    return _bz_vec_all(x._bz_asVecExpr());
}

template<class P_numtype, int N_dimensions>
inline _bz_bool all(const TinyVector<P_numtype, N_dimensions>& x)
{
    return _bz_vec_all(x._bz_asVecExpr());
}

BZ_NAMESPACE_END

#endif // BZ_VECALL_CC

