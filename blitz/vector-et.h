// -*- C++ -*-
/***************************************************************************
 * blitz/vector-et.h      Vector<P_numtype> class + expression templates
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

#ifndef BZ_VECTOR_ET_H
#define BZ_VECTOR_ET_H

#include <blitz/vector.h>

// These are compile-time expensive things not included
// by <blitz/vector.h>, but needed if we want vector expressions.

#include <blitz/vecbops.cc>         // Operators with two operands
#include <blitz/vecuops.cc>         // Functions with one argument
#include <blitz/vecbfn.cc>          // Functions with two arguments

#endif  // BZ_VECTOR_ET_H

