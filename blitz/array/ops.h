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
 * Revision 1.3  2002/07/02 19:12:50  jcumming
 * Use new style of Array ET macros to create unary and binary operators
 * that act on Array types.
 *
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
    
// unary operators
    
BZ_DECLARE_ARRAY_ET_UNARY(operator~, BitwiseNot)
BZ_DECLARE_ARRAY_ET_UNARY(operator!, LogicalNot)
BZ_DECLARE_ARRAY_ET_UNARY(operator+, UnaryPlus)
BZ_DECLARE_ARRAY_ET_UNARY(operator-, UnaryMinus)

// binary operators
    
// operator<< has been commented out because it causes ambiguity
// with statements like "cout << A".  NEEDS_WORK
// ditto operator<<

BZ_DECLARE_ARRAY_ET_BINARY(operator+,  Add)
BZ_DECLARE_ARRAY_ET_BINARY(operator-,  Subtract)
BZ_DECLARE_ARRAY_ET_BINARY(operator*,  Multiply)
BZ_DECLARE_ARRAY_ET_BINARY(operator/,  Divide)
BZ_DECLARE_ARRAY_ET_BINARY(operator%,  Modulo)
BZ_DECLARE_ARRAY_ET_BINARY(operator^,  BitwiseXor)
BZ_DECLARE_ARRAY_ET_BINARY(operator&,  BitwiseAnd)
BZ_DECLARE_ARRAY_ET_BINARY(operator|,  BitwiseOr)
// BZ_DECLARE_ARRAY_ET_BINARY(operator>>, ShiftRight)
// BZ_DECLARE_ARRAY_ET_BINARY(operator<<, ShiftLeft)
BZ_DECLARE_ARRAY_ET_BINARY(operator>,  Greater)
BZ_DECLARE_ARRAY_ET_BINARY(operator<,  Less)
BZ_DECLARE_ARRAY_ET_BINARY(operator>=, GreaterOrEqual)
BZ_DECLARE_ARRAY_ET_BINARY(operator<=, LessOrEqual)
BZ_DECLARE_ARRAY_ET_BINARY(operator==, Equal)
BZ_DECLARE_ARRAY_ET_BINARY(operator!=, NotEqual)
BZ_DECLARE_ARRAY_ET_BINARY(operator&&, LogicalAnd)
BZ_DECLARE_ARRAY_ET_BINARY(operator||, LogicalOr)

BZ_NAMESPACE_END

#endif // BZ_ARRAY_OPS_H
