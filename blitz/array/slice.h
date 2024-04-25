// -*- C++ -*-
/***************************************************************************
 * blitz/array/slice.h    Helper classes for slicing arrays
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
 ****************************************************************************/
#ifndef BZ_ARRAYSLICE_H
#define BZ_ARRAYSLICE_H

// #ifndef BZ_ARRAY_H
//  #error <blitz/array/slice.h> must be included via <blitz/array.h>
// #endif

#include <blitz/range.h>


#include <boost/preprocessor/repetition/enum_shifted_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>


namespace blitz {

// Forward declarations
template<typename T, int N>
class Array;

class nilArraySection { };

template<typename T>
class ArraySectionInfo {
public:
    static const int isValidType = 0;
	static const int rank = 0;
	static const int isPick = 0;
};

template<>
class ArraySectionInfo<Range> {
public:
    static const int isValidType = 1;
	static const int rank = 1;
	static const int isPick = 0;
};

template<>
class ArraySectionInfo<int> {
public:
    static const int isValidType = 1;
	static const int rank = 0;
	static const int isPick = 0;
};

template<>
class ArraySectionInfo<nilArraySection> {
public:
    static const int isValidType = 1;
	static const int rank = 0;
	static const int isPick = 0;
};


// #define NUMBER_OF_PARAMS BOOST_PP_SUB(BLITZ_ARRAY_LARGEST_RANK,1)

template<typename T_numtype, typename T0, BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS(BLITZ_ARRAY_LARGEST_RANK,typename T,=nilArraySection BOOST_PP_INTERCEPT)>
class SliceInfo {
public:
#define DEFAULT_print(z, n, data) + ArraySectionInfo<T##n>::isValidType

  static const int 
        numValidTypes = ArraySectionInfo<T0>::isValidType BOOST_PP_REPEAT_FROM_TO(1,BLITZ_ARRAY_LARGEST_RANK,DEFAULT_print,~);

#undef  DEFAULT_print
#define DEFAULT_print(z, n, data) + ArraySectionInfo<T##n>::rank

	static const int 
        rank          = ArraySectionInfo<T0>::rank BOOST_PP_REPEAT_FROM_TO(1,BLITZ_ARRAY_LARGEST_RANK,DEFAULT_print,~);

#undef  DEFAULT_print
#define DEFAULT_print(z, n, data) + ArraySectionInfo<T##n>::isPick

	static const int 
        isPick        = ArraySectionInfo<T0>::isPick BOOST_PP_REPEAT_FROM_TO(1,BLITZ_ARRAY_LARGEST_RANK,DEFAULT_print,~);

#undef  DEFAULT_print

    typedef Array<T_numtype,numValidTypes> T_array;
    typedef Array<T_numtype,rank> T_slice;
};


}

#endif // BZ_ARRAYSLICE_H
