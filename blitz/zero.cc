/***************************************************************************
 * blitz/zero.cc      ZeroElement type definition
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
#ifndef BZ_ZERO_H
 #include <blitz/zero.h>
#endif

#ifndef BZ_ZERO_CC
#define BZ_ZERO_CC

BZ_NAMESPACE(blitz)

#ifdef BZ_HAVE_COMPLEX

complex<float>  ZeroElement<complex<float> >::zero_ = 
    complex<float>(0.0f, 0.0f);

complex<double> ZeroElement<complex<double> >::zero_ =
    complex<double>(0.,0.);

complex<long double> ZeroElement<complex<long double> >::zero_ =
    complex<long double>(0.0L, 0.0L);

#endif // BZ_HAVE_COMPLEX

BZ_NAMESPACE_END

#endif // BZ_ZERO_CC

