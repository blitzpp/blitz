/***************************************************************************
 * blitz/array/ops.h  Array operators
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

#ifndef BZ_ARRAY_OPS_H
#define BZ_ARRAY_OPS_H

#ifndef BZ_OPS_H
 #include <blitz/ops.h>
#endif

#ifndef BZ_NEWET_MACROS_H
 #include <blitz/array/newet-macros.h>
#endif

BZ_NAMESPACE(blitz)

// operator<< has been commented out because it causes ambiguity
// with statements like "cout << A".  NEEDS_WORK
// ditto operator<<

BZ_DECLARE_ARRAY_ET(operator+,  Add)
BZ_DECLARE_ARRAY_ET(operator-,  Subtract)
BZ_DECLARE_ARRAY_ET(operator*,  Multiply)
BZ_DECLARE_ARRAY_ET(operator/,  Divide)
BZ_DECLARE_ARRAY_ET(operator%,  Modulo)
BZ_DECLARE_ARRAY_ET(operator^,  BitwiseXor)
BZ_DECLARE_ARRAY_ET(operator&,  BitwiseAnd)
BZ_DECLARE_ARRAY_ET(operator|,  BitwiseOr)
// BZ_DECLARE_ARRAY_ET(operator>>, ShiftRight)
// BZ_DECLARE_ARRAY_ET(operator<<, ShiftLeft)
BZ_DECLARE_ARRAY_ET(operator>,  Greater)
BZ_DECLARE_ARRAY_ET(operator<,  Less)
BZ_DECLARE_ARRAY_ET(operator>=, GreaterOrEqual)
BZ_DECLARE_ARRAY_ET(operator<=, LessOrEqual)
BZ_DECLARE_ARRAY_ET(operator==, Equal)
BZ_DECLARE_ARRAY_ET(operator!=, NotEqual)
BZ_DECLARE_ARRAY_ET(operator&&, LogicalAnd)
BZ_DECLARE_ARRAY_ET(operator||, LogicalOr)

BZ_DECLARE_ARRAY_ET_UOP(operator-, _bz_negate)

// NEEDS_WORK: operator!, operator~

BZ_NAMESPACE_END

#endif
