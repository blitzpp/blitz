/***************************************************************************
 * blitz/array/newet.h  Gang include of new expression templates implementation
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
 * Revision 1.3  2002/07/02 19:15:45  jcumming
 * Added #include of blitz/array/functorExpr.h to support user-defined
 * functors and class methods acting on Array types.
 *
 * Revision 1.2  2001/01/25 00:25:55  tveldhui
 * Ensured that source files have cvs logs.
 *
 */

#ifndef BZ_ARRAY_NEWET_H
#define BZ_ARRAY_NEWET_H

// Gang include of new expression templates implementation.

#include <blitz/array/ops.h>
#include <blitz/array/funcs.h>

// ET support for functors acting on Arrays

#include <blitz/array/functorExpr.h>

#endif
