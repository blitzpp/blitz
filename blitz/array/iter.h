// -*- C++ -*-
/***************************************************************************
 * blitz/array/iter.h  Basic iterator for arrays.
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
 ****************************************************************************/
#ifndef BZ_ARRAY_H
 #error <blitz/array/iter.h> must be included via <blitz/array.h>
#endif

#ifndef BZ_ARRAY_ITER_H
#define BZ_ARRAY_ITER_H

#ifdef BZ_HAVE_STL
#include <iterator>
#endif

BZ_NAMESPACE(blitz)

template<typename T, int N>
class ConstArrayIterator {
public:
    ConstArrayIterator() : data_(0) { }

    ConstArrayIterator(const Array<T,N>& array)
    {
        // Making internal copies of these avoids keeping
        // a pointer to the array and doing indirection.
        lbound_ = array.lbound();
        order_ = array.ordering();
        data_ = const_cast<T*>(array.dataFirst());
        
        ubound_(0) = array.ubound(0)+1;
        dataincr_(order_(0)) = array.stride(order_(0));
        for (int i=1,r,s=order_(0);i<N;s=r,++i) {
            r = order_(i);
            ubound_(i) = array.ubound(i)+1;
            dataincr_(r) = array.stride(r)-array.extent(s)*array.stride(s);
        }

        pos_ = lbound_;
    }

    bool operator==(const ConstArrayIterator<T,N>& x) const 
    { 
        return data_ == x.data_; 
    }
    
    bool operator!=(const ConstArrayIterator<T,N>& x) const 
    { 
        return data_ != x.data_; 
    }
 
    const T& operator*() const
    {
        BZPRECHECK(data_ != 0, "Attempted to dereference invalid iterator "
             << "(empty array or past end of array)");
        return *data_;
    }

    const T* restrict operator->() const
    {
        BZPRECHECK(data_ != 0, "Attempted to dereference invalid iterator "
             << "(empty array or past end of array)");
        return data_;
    }

    ConstArrayIterator<T,N>& operator++();

    ConstArrayIterator<T,N> operator++(int)
    {
        ConstArrayIterator<T,N> tmp = *this;
        ++(*this); 
        return tmp;
    }

    // get the current position of the Array iterator in index space
    const TinyVector<int,N>& position() const
    { 
        BZPRECHECK(data_ != 0, "Array<T,N>::iterator::position() called on"
             << " invalid iterator");
        return pos_; 
    }
   
private:
    TinyVector<int,N> dataincr_, lbound_, ubound_, order_;

protected:
    TinyVector<int,N> pos_;
    T * restrict data_;
};


template<typename T, int N>
class ArrayIterator : public ConstArrayIterator<T,N> {
private:
    typedef ConstArrayIterator<T,N> T_base;
    using T_base::data_;

public:
    ArrayIterator() { }

    ArrayIterator(Array<T,N>& x) : T_base(x) { }

    T& operator*() const
    {
        BZPRECHECK(data_ != 0, "Attempted to dereference invalid iterator "
             << "(empty array or past end of array)");
        return *data_;
    }

    T* restrict operator->() const
    {
        BZPRECHECK(data_ != 0, "Attempted to dereference invalid iterator "
             << "(empty array or past end of array)");
        return data_;
    }

    ArrayIterator<T,N>& operator++()
    {
        T_base::operator++();
        return *this;
    }

    ArrayIterator<T,N> operator++(int)
    {
        ArrayIterator<T,N> tmp = *this;
        ++(*this); 
        return tmp;
    }
};

template<typename T, int N>
ConstArrayIterator<T,N>& ConstArrayIterator<T,N>::operator++()
{
    BZPRECHECK(data_ != 0, "Attempted to iterate past the end of an array.");

    //   The first loop iteration is peeled as it increases performance.
    //   The same improvement can be obtained by telling the compiler that
    //   the test is likely to be true, but this has too many portability issues
    //   for now.

    // With a compiler peeling loops correctly (or with an effective BZ_LIKELY
    // macro, this could be simply written as:
    //
    // for (int i=0;i<N;++i) {
    //     const int r = order_(i);
    //     data_ += dataincr_[r];
    //     if (BZ_LIKELY(++pos_(r)!=ubound_(r)))
    //         return *this;
    //     pos_(r) = lbound_(r);
    // }


    const int r = order_(0);
    data_ += dataincr_[r];
    if (BZ_LIKELY(++pos_(r)!=ubound_(r)))
        return *this;
    pos_(r) = lbound_(r);

    for (int i=1;i<N;++i) {
        const int r = order_(i);
        data_ += dataincr_[r];
        if (BZ_LIKELY(++pos_(r)!=ubound_(r)))
            return *this;
        pos_(r) = lbound_(r);
    }

    // Setting data_ to 0 indicates the end of the array has
    // been reached, and will match the end iterator.
    //
    data_ = 0;
    return *this;
}

BZ_NAMESPACE_END


#ifdef BZ_HAVE_STL
// support for std::iterator_traits
BZ_NAMESPACE(std)

template <typename T, int N>
struct iterator_traits< BZ_BLITZ_SCOPE(ConstArrayIterator)<T,N> > 
{
    typedef forward_iterator_tag               iterator_category;
    typedef T                                  value_type;
    typedef ptrdiff_t                          difference_type;
    typedef const T*                           pointer;
    typedef const T&                           reference;
};

template <typename T, int N>
struct iterator_traits< BZ_BLITZ_SCOPE(ArrayIterator)<T,N> > 
{
    typedef forward_iterator_tag               iterator_category;
    typedef T                                  value_type;
    typedef ptrdiff_t                          difference_type;
    typedef T*                                 pointer;
    typedef T&                                 reference;
};

BZ_NAMESPACE_END

#endif // BZ_HAVE_STL

#endif // BZ_ARRAY_ITER_H

