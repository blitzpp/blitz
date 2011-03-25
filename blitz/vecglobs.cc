/***************************************************************************
 * blitz/vecglobs.cc      Vector global methods
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
#ifndef BZ_VECGLOBS_CC
#define BZ_VECGLOBS_CC

#ifndef BZ_VECGLOBS_H
 #include <blitz/vecglobs.h>
#endif

#include <blitz/vecaccum.cc>    // accumulate()
#include <blitz/vecdelta.cc>    // delta()
#include <blitz/vecmin.cc>      // min(), minValue(), minIndex()
#include <blitz/vecmax.cc>      // max(), maxValue(), maxIndex()
#include <blitz/vecsum.cc>      // sum(), mean()
#include <blitz/vecproduct.cc>  // product()
#include <blitz/vecdot.cc>      // dot()
#include <blitz/vecnorm.cc>     // norm()
#include <blitz/vecnorm1.cc>    // norm1()
#include <blitz/vecany.cc>      // any()
#include <blitz/vecall.cc>      // all()
#include <blitz/veccount.cc>    // count()

#endif // BZ_VECGLOBS_CC
