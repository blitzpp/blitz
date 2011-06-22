// -*- C++ -*-
/***************************************************************************
 * blitz/array/types.h      Typedefs for various datatypes
 *
 * Copyright (C) 2011 Paul P. Hilscher <pphilscher.kyodai@gmail.com>
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


#ifndef BZ_BLITZ_TYPES_H
#define BZ_BLITZ_TYPES_H


namespace blitz {

// Typedefs for vectors


// Typedefs for multi-dimensional arrys

typedef Array<int, 1>  Array1i;
typedef Array<int, 2>  Array2i;
typedef Array<int, 3>  Array3i;
typedef Array<int, 4>  Array4i;
typedef Array<int, 5>  Array5i;
typedef Array<int, 6>  Array6i;
typedef Array<int, 7>  Array7i;
typedef Array<int, 8>  Array8i;
typedef Array<int, 9>  Array9i;
typedef Array<int,10>  Array10i;
typedef Array<int,11>  Array11i;


typedef Array<unsigned int, 1 >  Array1ui;
typedef Array<unsigned int, 2 >  Array2ui;
typedef Array<unsigned int, 3 >  Array3ui;
typedef Array<unsigned int, 4 >  Array4ui;
typedef Array<unsigned int, 5 >  Array5ui;
typedef Array<unsigned int, 6 >  Array6ui;
typedef Array<unsigned int, 7 >  Array7ui;
typedef Array<unsigned int, 8 >  Array8ui;
typedef Array<unsigned int, 9 >  Array9ui;
typedef Array<unsigned int, 10>  Array10ui;
typedef Array<unsigned int, 11>  Array11ui;


typedef Array<double, 1>  Array1d;
typedef Array<double, 2>  Array2d;
typedef Array<double, 3>  Array3d;
typedef Array<double, 4>  Array4d;
typedef Array<double, 5>  Array5d;
typedef Array<double, 6>  Array6d;
typedef Array<double, 7>  Array7d;
typedef Array<double, 8>  Array8d;
typedef Array<double, 9>  Array9d;
typedef Array<double,10>  Array10d;
typedef Array<double,11>  Array11d;

typedef Array<float, 1>  Array1f;
typedef Array<float, 2>  Array2f;
typedef Array<float, 3>  Array3f;
typedef Array<float, 4>  Array4f;
typedef Array<float, 5>  Array5f;
typedef Array<float, 6>  Array6f;
typedef Array<float, 7>  Array7f;
typedef Array<float, 8>  Array8f;
typedef Array<float, 9>  Array9f;
typedef Array<float,10>  Array10f;
typedef Array<float,11>  Array11f;

#ifdef BZ_HAVE_COMPLEX

typedef std::complex<float> cmplxf;
typedef std::complex<double> cmplxd;

typedef Array<cmplxf, 1>  Array1c;
typedef Array<cmplxf, 2>  Array2c;
typedef Array<cmplxf, 3>  Array3c;
typedef Array<cmplxf, 4>  Array4c;
typedef Array<cmplxf, 5>  Array5c;
typedef Array<cmplxf, 6>  Array6c;
typedef Array<cmplxf, 7>  Array7c;
typedef Array<cmplxf, 8>  Array8c;
typedef Array<cmplxf, 9>  Array9c;
typedef Array<cmplxf,10>  Array10c;
typedef Array<cmplxf,11>  Array11c;

typedef Array<cmplxd, 1>  Array1z;
typedef Array<cmplxd, 2>  Array2z;
typedef Array<cmplxd, 4>  Array4z;
typedef Array<cmplxd, 3>  Array3z;
typedef Array<cmplxd, 5>  Array5z;
typedef Array<cmplxd, 6>  Array6z;
typedef Array<cmplxd, 7>  Array7z;
typedef Array<cmplxd, 8>  Array8z;
typedef Array<cmplxd, 9>  Array9z;
typedef Array<cmplxd,10>  Array10z;
typedef Array<cmplxd,11>  Array11z;


#endif // BZ_HAVE_COMPLEX


//  quad precision
/*
#ifdef HAS_QUAD
// not tested yet
typedef __float128 quad;
typedef Array<quad, 1>  Array1q;
typedef Array<quad, 2>  Array2q;
typedef Array<quad, 4>  Array4q;
typedef Array<quad, 3>  Array3q;
typedef Array<quad, 5>  Array5q;
typedef Array<quad, 6>  Array6q;
typedef Array<quad, 7>  Array7q;
typedef Array<quad, 8>  Array8q;
typedef Array<quad, 9>  Array9q;
typedef Array<quad,10>  Array10q;
typedef Array<quad,11>  Array11q;
#endif
*/

};

#endif // BZ_BLITZ_TYPES_H
