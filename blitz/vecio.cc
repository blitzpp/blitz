/***************************************************************************
 * blitz/vecio.cc      Vector I/O methods
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
#ifndef BZ_VECIO_CC
#define BZ_VECIO_CC

#ifndef BZ_VECTOR_H
 #include <blitz/vector.h>
#endif

BZ_NAMESPACE(blitz)

// This version of operator<< is provided as a temporary measure
// only.  It will be revised in a future release.
// NEEDS_WORK

template<typename P_numtype>
ostream& operator<<(ostream& os, const Vector<P_numtype>& x)
{
    os << x.length() << endl << "[ ";
    for (int i=0; i < x.length(); ++i)
    {
        os << x[i] << " ";
    }
    os << "]";
    return os;
}

template<typename P_expr>
ostream& operator<<(ostream& os, _bz_VecExpr<P_expr> expr)
{
    Vector<_bz_typename P_expr::T_numtype> result(expr);
    os << result;
    return os;
}

template<typename P_numtype>
istream& operator>>(istream& is, Vector<P_numtype>& x)
{
    int length;
    char sep;

    is >> length;
    BZPRECHECK(!is.bad(), "Premature end of input while scanning Vector");
    x.resize(length);

    is >> sep;
    BZPRECHECK(sep == '[', "Format error while scanning input \
Vector \n (expected '[' before beginning of Vector data)");
    for (int i=0; i < x.length(); ++i) {
        BZPRECHECK(!is.bad(), "Premature end of input while scanning Vector");
        is >> x(i);
    }

    is >> sep;
    BZPRECHECK(sep == ']', "Format error while scanning input \
Vector \n (expected ']' after end of Vector data)");
    return is;
}

BZ_NAMESPACE_END

#endif // BZ_VECIO_CC
