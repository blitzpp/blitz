/***************************************************************************
 * blitz/array/domain.h  Declaration of the RectDomain class
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
 * Revision 1.3  2001/02/11 15:43:39  tveldhui
 * Additions from Julian Cummings:
 *  - StridedDomain class
 *  - more versions of resizeAndPreserve
 *
 * Revision 1.2  2001/01/25 00:25:55  tveldhui
 * Ensured that source files have cvs logs.
 *
 */

#ifndef BZ_DOMAIN_H
#define BZ_DOMAIN_H

#ifndef BZ_TINYVEC_H
 #include <blitz/tinyvec.h>
#endif

#ifndef BZ_RANGE_H
 #include <blitz/range.h>
#endif

/*
 * Portions of this class were inspired by the "RectDomain" class
 * provided by the Titanium language (UC Berkeley).
 */

BZ_NAMESPACE(blitz)

template<int N_rank>
class RectDomain {

public:
    RectDomain(const TinyVector<int,N_rank>& lbound,
        const TinyVector<int,N_rank>& ubound)
      : lbound_(lbound), ubound_(ubound)
    { }

    // NEEDS_WORK: better constructors
    // RectDomain(Range, Range, ...)
    // RectDomain with any combination of Range and int

    const TinyVector<int,N_rank>& lbound() const
    { return lbound_; }

    int lbound(int i) const
    { return lbound_(i); }

    const TinyVector<int,N_rank>& ubound() const
    { return ubound_; }

    int ubound(int i) const
    { return ubound_(i); }

    Range operator[](int rank) const
    { return Range(lbound_(rank), ubound_(rank)); }

    void shrink(int amount)
    {
        lbound_ += amount;
        ubound_ -= amount;
    }

    void shrink(int dim, int amount)
    {
        lbound_(dim) += amount;
        ubound_(dim) -= amount;
    }

    void expand(int amount)
    {
        lbound_ -= amount;
        ubound_ += amount;
    }

    void expand(int dim, int amount)
    {
        lbound_(dim) -= amount;
        ubound_(dim) += amount;
    }

private:
    TinyVector<int,N_rank> lbound_, ubound_;
};

/*
 * StridedDomain added by Julian Cummings
 */
template<int N_rank>
class StridedDomain {

public:
    StridedDomain(const TinyVector<int,N_rank>& lbound,
        const TinyVector<int,N_rank>& ubound,
        const TinyVector<int,N_rank>& stride)
      : lbound_(lbound), ubound_(ubound), stride_(stride)
    { }

    // NEEDS_WORK: better constructors
    // StridedDomain(Range, Range, ...)
    // StridedDomain with any combination of Range and int

    const TinyVector<int,N_rank>& lbound() const
    { return lbound_; }

    int lbound(int i) const
    { return lbound_(i); }

    const TinyVector<int,N_rank>& ubound() const
    { return ubound_; }

    int ubound(int i) const
    { return ubound_(i); }

    const TinyVector<int,N_rank>& stride() const
    { return stride_; }

    int stride(int i) const
    { return stride_(i); }

    Range operator[](int rank) const
    { return Range(lbound_(rank), ubound_(rank), stride_(rank)); }

    void shrink(int amount)
    {
        lbound_ += amount * stride_;
        ubound_ -= amount * stride_;
    }

    void shrink(int dim, int amount)
    {
        lbound_(dim) += amount * stride_(dim);
        ubound_(dim) -= amount * stride_(dim);
    }

    void expand(int amount)
    {
        lbound_ -= amount * stride_;
        ubound_ += amount * stride_;
    }

    void expand(int dim, int amount)
    {
        lbound_(dim) -= amount * stride_(dim);
        ubound_(dim) += amount * stride_(dim);
    }

private:
    TinyVector<int,N_rank> lbound_, ubound_, stride_;
};


template<int N_rank>
inline RectDomain<N_rank> strip(const TinyVector<int,N_rank>& startPosition,
    int stripDimension, int ubound)
{
    BZPRECONDITION((stripDimension >= 0) && (stripDimension < N_rank));
    BZPRECONDITION(ubound >= startPosition(stripDimension));

    TinyVector<int,N_rank> endPosition = startPosition;
    endPosition(stripDimension) = ubound;
    return RectDomain<N_rank>(startPosition, endPosition);
}

BZ_NAMESPACE_END

#endif // BZ_DOMAIN_H
