/***************************************************************************
 * blitz/array/iter.h  Basic iterator for arrays.
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
 * Revision 1.3  2002/03/06 15:56:43  patricg
 *
 * data_ replaced by this->data_ in
 * template<class T, int N>
 * class ArrayIterator : public ConstArrayIterator<T,N> {},
 * removed struct _bz_endTag { }; declaration
 *
 * Revision 1.2  2001/01/25 00:25:55  tveldhui
 * Ensured that source files have cvs logs.
 *
 */

#ifndef BZ_ARRAY_H
 #error <blitz/array/iter.h> must be included via <blitz/array.h>
#endif

#ifndef BZ_ARRAY_ITER_H
#define BZ_ARRAY_ITER_H

BZ_NAMESPACE(blitz)



template<class T, int N>
class ConstArrayIterator {

public:
    ConstArrayIterator(const Array<T,N>& array)
    {
        // Making internal copies of these avoids keeping
        // a pointer to the array and doing indirection.
        strides_ = array.stride();
        lbound_ = array.lbound();
        extent_ = array.extent();
        order_ = array.ordering();
        first_ = const_cast<T*>(array.dataFirst());
        data_ = first_;

        maxRank_ = order_(0);
        stride_ = strides_(maxRank_);

        for (int i=0; i < N; ++i)
        {
            stack_[i] = data_;
            last_[i] = data_ + array.extent(order_(i))  
                * strides_(order_(i));
        }

        pos_ = lbound_;
    }

    ConstArrayIterator(const Array<T,N>& array, _bz_endTag)
    {
        // The _bz_endTag type is provided by the end() method
        // in Array<T,N>, and indicates that an end iterator
        // is to be constructed.

        // Use 0 pointer to mark end of array.
        // This also handles the case of empty arrays, which
        // have their data pointer set to 0.
        data_ = 0;
    }

    T operator*() const
    {
        BZPRECHECK(data_ != 0, "Attempted to dereference invalid iterator "
             << "(empty array or past end of array)");
        return *data_;
    }

    const T* _bz_restrict operator->() const
    {
        BZPRECHECK(data_ != 0, "Attempted to dereference invalid iterator "
             << "(empty array or past end of array)");
        return data_;
    }

    ConstArrayIterator<T,N>& operator++();

    // This operator returns void, which breaks the STL forward
    // iterator requirements.  Unfortunately many people have
    // gotten into the habit of writing iter++ when they really
    // mean ++iter.  iter++ implemented the proper way requires
    // returning a copy of the original state of the iterator,
    // before increment.  This would be very inefficient, since
    // the iterator contains a lot of data.  Hence the void
    // return: it will be efficient even if you write iter++.
    // Maybe this is a bad idea, let me know if this causes
    // you problems.
    void operator++(int)
    { ++(*this); }

    const TinyVector<int,N>& position() const
    { 
        BZPRECHECK(data_ != 0, "Array<T,N>::iterator::position() called on"
             << " invalid iterator");
        return pos_; 
    }
   
    bool operator==(const ConstArrayIterator<T,N>& x) const
    {
        return data_ == x.data_;
    }

    bool operator!=(const ConstArrayIterator<T,N>& x) const
    {
        return data_ != x.data_;
    }
 
private:
    ConstArrayIterator() { }

private:
    TinyVector<int,N> strides_, lbound_, extent_, order_;
    T * stack_[N];
    T * last_[N];
    int stride_;
    int maxRank_;

protected:
    TinyVector<int,N> pos_;
    T * _bz_restrict data_;
    T * _bz_restrict first_;
};



template<class T, int N>
class ArrayIterator : public ConstArrayIterator<T,N> {
  public:
    ArrayIterator(Array<T,N>& x)
      : ConstArrayIterator<T,N>(x)
    { }

    ArrayIterator(Array<T,N>& x, _bz_endTag y)
      : ConstArrayIterator<T,N>(x,y)
    { }

    ArrayIterator<T,N>& operator++()
    {
        ConstArrayIterator<T,N>::operator++();
        return *this;
    }

    T& operator*()
    {
        return *this->data_;
    }

    T* _bz_restrict operator->() 
    {
        return this->data_;
    }
};



template<class T, int N>
ConstArrayIterator<T,N>& ConstArrayIterator<T,N>::operator++()
{
    BZPRECHECK(data_ != 0, "Attempted to iterate past the end of an array.");

    data_ += stride_;

    if (data_ != last_[0])
    {
        // We hit this case almost all the time.
        ++pos_[maxRank_];
        return *this;
    }

    // We've hit the end of a row/column/whatever.  Need to
    // increment one of the loops over another dimension.

    int j = 1;
    for (; j < N; ++j)
    {
        int r = order_(j);
        data_ = stack_[j];
        data_ += strides_[r];
        ++pos_(r);

        if (data_ != last_[j])
            break;
    }

    // All done?
    if (j == N)
    {
        // Setting data_ to 0 indicates the end of the array has
        // been reached, and will match the end iterator.
        data_ = 0;
        return *this;
    }

    stack_[j] = data_;

    // Now reset all the last pointers
    for (--j; j >= 0; --j)
    {
        int r2 = order_(j);
        stack_[j] = data_;
        last_[j] = data_ + extent_(r2) * strides_(r2);
        pos_(r2) = lbound_(r2);
    }

    return *this;
}

BZ_NAMESPACE_END

#endif // BZ_ARRAY_ITER_H

