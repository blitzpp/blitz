// -*- C++ -*-
/***************************************************************************
 * blitz/compiler.h      Compiler specific directives and kludges
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


#ifndef BZ_COMPILER_H
#define BZ_COMPILER_H

#include <blitz/config.h>

/*
 * Define some kludges.
 */

#ifdef BZ_HAVE_TEMPLATE_QUALIFIED_RETURN_TYPE
  #define BZ_USE_NUMTRAIT
#endif

#ifdef BZ_HAVE_DEFAULT_TEMPLATE_PARAMETERS
    #define BZ_TEMPLATE_DEFAULT(X)   = X
#else
    #define BZ_TEMPLATE_DEFAULT(X) 
#endif

#ifdef BZ_DISABLE_RESTRICT
 #undef BZ_HAVE_NCEG_RESTRICT
#endif

#ifndef BZ_HAVE_NCEG_RESTRICT
    #if defined(BZ_HAVE_NCEG_RESTRICT_EGCS)
        #define restrict     __restrict__
    #else
        #define restrict
    #endif
#endif

#ifdef BZ_HAVE_ENUM_COMPUTATIONS_WITH_CAST
    #define BZ_ENUM_CAST(X)   (int)X
#elif defined(BZ_HAVE_ENUM_COMPUTATIONS)
    #define BZ_ENUM_CAST(X)   X
#else
    #error In <blitz/config.h>: Your compiler does not support enum computations.  You may have to rerun compiler/bzconfig.
#endif

#if defined(BZ_MATH_FN_IN_NAMESPACE_STD)
  #define BZ_MATHFN_SCOPE(x) std::x
#else
  #define BZ_MATHFN_SCOPE(x) ::x
#endif

#if defined(BZ_MATH_ABSINT_IN_NAMESPACE_STD)
#include <cstdlib>
#else
#include <stdlib.h>
#endif

#if defined(BZ_MATH_ABSINT_IN_NAMESPACE_STD)
  #define BZ_MATHABSINT_SCOPE(x) std::x
#else
  #define BZ_MATHABSINT_SCOPE(x) ::x
#endif

#if defined(BZ_HAVE_COMPLEX_MATH_IN_NAMESPACE_STD)
  #define BZ_CMATHFN_SCOPE(x) std::x
#else
  #define BZ_CMATHFN_SCOPE(x) ::x
#endif

#define BZ_IEEEMATHFN_SCOPE(x) ::x

//  These macros are just markers to document the code in the places
//  where playing with the processor branch prediction scheme might
//  help. For now these are just nops.

#define BZ_LIKELY(x)   (x)
#define BZ_UNLIKELY(x) (x)

#endif // BZ_COMPILER_H

