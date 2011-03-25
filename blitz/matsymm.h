// -*- C++ -*-
/***************************************************************************
 * blitz/matsymm.h      Declarations for Symmetric matrices
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

#ifndef BZ_MATSYMM_H
#define BZ_MATSYMM_H

#ifndef BZ_MSTRUCT_H
 #error <blitz/matsymm.h> must be included via <blitz/mstruct.h>
#endif

BZ_NAMESPACE(blitz)

// Symmetric, lower triangular row major ordering
// [ 0 1 3 6 ]
// [ 1 2 4 7 ]
// [ 3 4 5 8 ]
// [ 6 7 8 9 ]

class SymmetricIterator {
public:
    SymmetricIterator(unsigned rows, unsigned cols)
    {
        BZPRECONDITION(rows == cols);
        size_ = rows;
        good_ = true;
        offset_ = 0;
        i_ = 0;
        j_ = 0;
    }
   
    operator bool() const { return good_; }

    void operator++()
    {
        BZPRECONDITION(good_);
        ++offset_;
        ++j_;
        if (j_ > i_)
        {
            j_ = 0;
            ++i_;
            if (i_ == size_)
                good_ = false;
        }
    }

    unsigned row() const
    { return i_; }

    unsigned col() const
    { return j_; }

    unsigned offset() const
    { return offset_; }

protected:
    unsigned size_;
    bool     good_;
    unsigned offset_;
    unsigned i_, j_;
};

class Symmetric : public MatrixStructure {

public:
    typedef SymmetricIterator T_iterator;

    Symmetric()
        : size_(0)
    { }

    Symmetric(unsigned size)
        : size_(size)
    { }

    Symmetric(unsigned rows, unsigned cols)
        : size_(rows)
    {
        BZPRECONDITION(rows == cols);
    }

    unsigned columns() const
    { return size_; }

    unsigned coordToOffset(unsigned i, unsigned j) const
    {
        BZPRECONDITION(inRange(i,j));
        if (i >= j)
            return i*(i+1)/2 + j;
        else
            return j*(j+1)/2 + i;
    }

    unsigned firstInRow(unsigned i) const
    { return 0; }

    template<typename T_numtype>
    T_numtype get(const T_numtype * restrict data,
        unsigned i, unsigned j) const
    {
        BZPRECONDITION(inRange(i,j));
        return data[coordToOffset(i,j)];
    }

    template<typename T_numtype>
    T_numtype& get(T_numtype * restrict data, unsigned i, unsigned j)
    {
        BZPRECONDITION(inRange(i,j));
        return data[coordToOffset(i,j)];
    }

    unsigned lastInRow(unsigned i) const
    { return i; }

    unsigned firstInCol(unsigned j) const
    { return j; }

    unsigned lastInCol(unsigned j) const
    { return size_ - 1; }

    bool inRange(unsigned i, unsigned j) const {
        return (i < size_) && (j < size_);
    }

    unsigned numElements() const
    { return size_ * (size_ + 1) / 2; }

    unsigned rows() const
    { return size_; }

    void resize(unsigned size)
    {
        size_ = size;
    }

    void resize(unsigned rows, unsigned cols)
    {
        BZPRECONDITION(rows == cols);
        size_  = rows;
    }

private:
    unsigned size_;
};

BZ_NAMESPACE_END

#endif // BZ_MATSYMM_H

