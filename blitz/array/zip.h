/***************************************************************************
 * blitz/array/zip.h  "zip" scalar arrays into a multicomponent array expr
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
 * Revision 1.2  2001/01/25 00:25:56  tveldhui
 * Ensured that source files have cvs logs.
 *
 */

#ifndef BZ_ARRAYZIP_H
#define BZ_ARRAYZIP_H

#ifndef BZ_ARRAY_H
 #error <blitz/array/zip.h> must be included via <blitz/array.h>
#endif

BZ_NAMESPACE(blitz)

template<class P_component, class T1, class T2>
struct Zip2 {
    typedef P_component T_numtype;

    static inline T_numtype apply(T1 a, T2 b)
    { return T_numtype(a,b); }

    template<class T_left, class T_right>
    static inline void prettyPrint(string& str,
        prettyPrintFormat& format, const T_left& t1,
        const T_right& t2)
    {
        str += "zip(";
        t1.prettyPrint(str, format);
        str += ",";
        t2.prettyPrint(str, format);
        str += ")";
    }
};

template<class T_component, class T1, class T2>
inline _bz_ArrayExpr<_bz_ArrayExprOp<_bz_typename asExpr<T1>::T_expr, 
    _bz_typename asExpr<T2>::T_expr, Zip2<T_component, 
    _bz_typename asExpr<T1>::T_expr::T_numtype,
    _bz_typename asExpr<T2>::T_expr::T_numtype> > >
zip(const T1& a, const T2& b, T_component)
{
    return _bz_ArrayExpr<_bz_ArrayExprOp<_bz_typename asExpr<T1>::T_expr,
        _bz_typename asExpr<T2>::T_expr, Zip2<T_component, 
        _bz_typename asExpr<T1>::T_expr::T_numtype,
        _bz_typename asExpr<T2>::T_expr::T_numtype> > >(a,b);
}

BZ_NAMESPACE_END

#endif // BZ_ARRAYZIP_H

