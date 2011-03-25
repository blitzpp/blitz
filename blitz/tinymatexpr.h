// -*- C++ -*-
/***************************************************************************
 * blitz/tinymatexpr.h   Tiny Matrix Expressions
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

#ifndef BZ_TINYMATEXPR_H
#define BZ_TINYMATEXPR_H

#ifndef BZ_TINYMAT_H
 #error <blitz/tinymatexpr.h> must be included via <blitz/tinymat.h>
#endif

BZ_NAMESPACE(blitz)

template<typename T_expr>
class _bz_tinyMatExpr {
public:
    typedef _bz_typename T_expr::T_numtype T_numtype;

    static const int
        rows = T_expr::rows,
        columns = T_expr::columns;

    _bz_tinyMatExpr(T_expr expr)
        : expr_(expr)
    { }

    _bz_tinyMatExpr(const _bz_tinyMatExpr<T_expr>& x)
        : expr_(x.expr_)
    { }

    T_numtype operator()(int i, int j) const
    { return expr_(i,j); }

protected:
    T_expr expr_;
};

BZ_NAMESPACE_END

#endif // BZ_TINYMATEXPR_H

