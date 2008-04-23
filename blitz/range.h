// -*- C++ -*-
/***************************************************************************
 * blitz/range.h      Declaration of the Range class
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
 ***************************************************************************/

#ifndef BZ_RANGE_H
#define BZ_RANGE_H

#ifndef BZ_BLITZ_H
 #include <blitz/blitz.h>
#endif

#ifndef BZ_VECEXPRWRAP_H
 #include <blitz/vecexprwrap.h>      // _bz_VecExpr wrapper
#endif

#include <climits>                  // for INT_MIN, INT_MAX

BZ_NAMESPACE(blitz)

// Examples: 
// Array<int,1> A(7);
// A = 0,1,2,3,4,5,6;
// A(Range::all());                   [0,1,2,3,4,5,6]
// A(Range(3,5));                     [3,4,5]
// A(Range(3,toEnd));                 [3,4,5,6]
// A(Range(fromStart,3));             [0,1,2,3]
// A(Range(1,5,2));                   [1,3,5]
// A(Range(5,1,-2));                  [5,3,1]
// A(Range(fromStart,toEnd,2));       [0,2,4,6]


const int fromStart = INT_MIN;
const int toEnd = INT_MAX;

// Class Range
class Range {

public:
    typedef int T_numtype;
	typedef unsigned int T_sizetype;

    Range()
    {
        first_ = fromStart;
        last_ = toEnd;
        stride_ = 1;
    }

    // Range(Range r): allow default copy constructor to be used
#ifdef BZ_MANUAL_VECEXPR_COPY_CONSTRUCTOR
    Range(const Range& r)
    {
        first_ = r.first_;
        last_ = r.last_;
        stride_ = r.stride_;
    }
#endif

    explicit Range(T_numtype slicePosition)
    {
        first_ = slicePosition;
        last_ = slicePosition;
        stride_ = 1;
    }

    Range(T_numtype first, T_numtype last, T_numtype stride=1)
        : first_(first), last_(last), stride_(stride)
    { 
        BZPRECHECK((first == fromStart) || (last == toEnd) ||
                       (first < last) && (stride > 0) ||
                       (first > last) && (stride < 0) ||
                       (first == last), (*this) << " is an invalid range.");
        BZPRECHECK((first == fromStart) || (last == toEnd) ||
            (last-first) % stride == 0,
            (*this) << ": the stride must evenly divide the range");
    }

    T_numtype first(T_numtype lowRange = 0) const
    { 
        if (first_ == fromStart)
            return lowRange;
        return first_; 
    }

    T_numtype last(T_numtype highRange = 0) const
    {
        if (last_ == toEnd)
            return highRange;
        return last_;
    }

    T_sizetype length(int =0) const
    {
        BZPRECONDITION(first_ != fromStart);
        BZPRECONDITION(last_ != toEnd);
        BZPRECONDITION((last_ - first_) % stride_ == 0);
        return (last_ - first_) / stride_ + 1;
    }

    T_numtype stride() const
    { return stride_; }

    bool isAscendingContiguous() const
    {
        return ((first_ < last_) && (stride_ == 1) || (first_ == last_));
    }

    void setRange(T_numtype first, T_numtype last, T_numtype stride=1)
    {
        BZPRECONDITION((first < last) && (stride > 0) ||
                       (first > last) && (stride < 0) ||
                       (first == last));
        BZPRECONDITION((last-first) % stride == 0);
        first_ = first;
        last_ = last;
        stride_ = stride;
    }

    static Range all() 
    { return Range(fromStart,toEnd,1); }

    bool isUnitStride() const
    { return stride_ == 1; }

    // Operators
    Range operator-(T_numtype shift) const
    { 
        BZPRECONDITION(first_ != fromStart);
        BZPRECONDITION(last_ != toEnd);
        return Range(first_ - shift, last_ - shift, stride_); 
    }

    Range operator+(T_numtype shift) const
    { 
        BZPRECONDITION(first_ != fromStart);
        BZPRECONDITION(last_ != toEnd);
        return Range(first_ + shift, last_ + shift, stride_); 
    }

    T_numtype operator[](T_sizetype i) const
    {
        return first_ + i * stride_;
    }

    T_numtype operator()(T_sizetype i) const
    {
        return first_ + i * stride_;
    }

    friend inline ostream& operator<<(ostream& os, const Range& range)
    {
        os << "Range(" << range.first() << "," << range.last() << ","
           << range.stride() << ")";

        return os;
    }

    /////////////////////////////////////////////
    // Library-internal member functions
    // These are undocumented and may change or
    // disappear in future releases.
    /////////////////////////////////////////////

    static const int
        _bz_staticLengthCount = 0,
        _bz_dynamicLengthCount = 0,
        _bz_staticLength = 0;

    bool _bz_hasFastAccess() const
    { return stride_ == 1; }

    int _bz_fastAccess(unsigned int i) const
    { return first_ + i; }

    unsigned int _bz_suggestLength() const
    { 
        return length();
    }

    _bz_VecExpr<Range> _bz_asVecExpr() const
    { return _bz_VecExpr<Range>(*this); }

private:
    T_numtype first_, last_, stride_;
};

BZ_NAMESPACE_END

#endif // BZ_RANGE_H
