/***************************************************************************
 * blitz/array/asexpr.h  Declaration of the asExpr helper functions
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
 * Revision 1.2  2001/01/25 00:25:55  tveldhui
 * Ensured that source files have cvs logs.
 *
 */

#ifndef BZ_ARRAYASEXPR_H
#define BZ_ARRAYASEXPR_H

#ifndef BZ_ARRAY_H
 #error <blitz/array/asexpr.h> must be included via <blitz/array.h>
#endif

BZ_NAMESPACE(blitz)

// The traits class asExpr converts arbitrary things to
// expression templatable operands.

// Default to scalar.
template<class T>
struct asExpr {
    typedef _bz_ArrayExprConstant<T> T_expr;
};

// Already an expression template term
template<class T>
struct asExpr<_bz_ArrayExpr<T> > {
    typedef _bz_ArrayExpr<T> T_expr;
};

// An array operand
template<class T, int N>
struct asExpr<Array<T,N> > {
    typedef FastArrayIterator<T,N> T_expr;
};

// Index placeholder
template<int N>
struct asExpr<IndexPlaceholder<N> > {
    typedef IndexPlaceholder<N> T_expr;
};

BZ_NAMESPACE_END

#endif
