// -*- C++ -*-
/***************************************************************************
 * blitz/tinyvec.h      Declaration of the TinyVector2<T, N> class
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

#ifndef BZ_TINYVEC2_H
#define BZ_TINYVEC2_H

#include <blitz/blitz.h>
//#include <blitz/range.h>
#include <blitz/listinit.h>
//#include <blitz/tiny.h>
#include <blitz/etbase.h>

#ifdef BZ_HAVE_CSTRING
#include <cstring> // For memcpy
#endif

BZ_NAMESPACE(blitz)

/*****************************************************************************
 * Forward declarations
 */

template<typename P_numtype, int N_length>
class FastTV2Iterator;

// template<typename P_numtype, int N_length, int N_stride BZ_TEMPLATE_DEFAULT(1) >
// class TinyVector2IterConst;

// template<typename P_numtype>
// class Vector;

// template<typename P_expr>
// class _bz_VecExpr;

// template<typename P_distribution>
// class Random;

// template<typename P_numtype>
// class VectorPick;

// template<typename T_numtype1, typename T_numtype2, int N_rows, int N_columns,
//     int N_vecStride>
// class _bz_matrixVectorProduct;



/*****************************************************************************
 * Declaration of class TinyVector2
 */

template<typename P_numtype, int N_length>
class TinyVector2 : public ETBase<TinyVector2<P_numtype, N_length> >
{
public:

    //////////////////////////////////////////////
    // Public Types
    //////////////////////////////////////////////

    typedef P_numtype                                    T_numtype;
    typedef TinyVector2<T_numtype,N_length>               T_vector;
    typedef FastTV2Iterator<T_numtype,N_length>         T_iterator;
  //typedef TinyVector2IterConst<T_numtype,N_length,1>    T_constIterator;
    typedef T_numtype*                                   iterator;
    typedef const T_numtype*                             const_iterator;
  //enum { numElements = N_length };

    static const int 
        numArrayOperands = 1, 
        numIndexPlaceholders = 0,
        rank_ = 1;

    TinyVector2()  { }
    ~TinyVector2() { }

    inline TinyVector2(const TinyVector2<T_numtype,N_length>& x);

    template <typename T_numtype2>
    inline TinyVector2(const TinyVector2<T_numtype2,N_length>& x);

    inline TinyVector2(const T_numtype initValue);

    inline TinyVector2(const T_numtype x[]) {
        memcpy(data_,x,N_length*sizeof(T_numtype));
    }

    TinyVector2(T_numtype x0, T_numtype x1)
    {
        data_[0] = x0;
        data_[1] = x1;
    }

    TinyVector2(T_numtype x0, T_numtype x1, T_numtype x2)
    {
        data_[0] = x0;
        data_[1] = x1;
        data_[2] = x2;
    }

    TinyVector2(T_numtype x0, T_numtype x1, T_numtype x2,
        T_numtype x3)
    {
        data_[0] = x0;
        data_[1] = x1;
        data_[2] = x2;
        data_[3] = x3;
    }

    TinyVector2(T_numtype x0, T_numtype x1, T_numtype x2,
        T_numtype x3, T_numtype x4)
    {
        data_[0] = x0;
        data_[1] = x1;
        data_[2] = x2;
        data_[3] = x3;
        data_[4] = x4;
    }

    TinyVector2(T_numtype x0, T_numtype x1, T_numtype x2,
        T_numtype x3, T_numtype x4, T_numtype x5)
    {
        data_[0] = x0;
        data_[1] = x1;
        data_[2] = x2;
        data_[3] = x3;
        data_[4] = x4;
        data_[5] = x5;
    }

    TinyVector2(T_numtype x0, T_numtype x1, T_numtype x2,
        T_numtype x3, T_numtype x4, T_numtype x5, T_numtype x6)
    {
        data_[0] = x0;
        data_[1] = x1;
        data_[2] = x2;
        data_[3] = x3;
        data_[4] = x4;
        data_[5] = x5;
        data_[6] = x6;
    }

    TinyVector2(T_numtype x0, T_numtype x1, T_numtype x2,
        T_numtype x3, T_numtype x4, T_numtype x5, T_numtype x6,
        T_numtype x7)
    {
        data_[0] = x0;
        data_[1] = x1;
        data_[2] = x2;
        data_[3] = x3;
        data_[4] = x4;
        data_[5] = x5;
        data_[6] = x6;
        data_[7] = x7;
    }

    TinyVector2(T_numtype x0, T_numtype x1, T_numtype x2,
        T_numtype x3, T_numtype x4, T_numtype x5, T_numtype x6,
        T_numtype x7, T_numtype x8)
    {
        data_[0] = x0;
        data_[1] = x1;
        data_[2] = x2;
        data_[3] = x3;
        data_[4] = x4;
        data_[5] = x5;
        data_[6] = x6;
        data_[7] = x7;
        data_[8] = x8;
    }

    TinyVector2(T_numtype x0, T_numtype x1, T_numtype x2,
        T_numtype x3, T_numtype x4, T_numtype x5, T_numtype x6,
        T_numtype x7, T_numtype x8, T_numtype x9)
    {
        data_[0] = x0;
        data_[1] = x1;
        data_[2] = x2;
        data_[3] = x3;
        data_[4] = x4;
        data_[5] = x5;
        data_[6] = x6;
        data_[7] = x7;
        data_[8] = x8;
        data_[9] = x9;
    }

    TinyVector2(T_numtype x0, T_numtype x1, T_numtype x2,
        T_numtype x3, T_numtype x4, T_numtype x5, T_numtype x6,
        T_numtype x7, T_numtype x8, T_numtype x9, T_numtype x10)
    {
        data_[0] = x0;
        data_[1] = x1;
        data_[2] = x2;
        data_[3] = x3;
        data_[4] = x4;
        data_[5] = x5;
        data_[6] = x6;
        data_[7] = x7;
        data_[8] = x8;
        data_[9] = x9;
        data_[10] = x10;
    }

    // // Constructor added by Peter Nordlund
    // template<typename P_expr>
    // inline TinyVector2(_bz_VecExpr<P_expr> expr);

  static int base() 
  { return 0; }

  static int                               base(int rank) 
  { return 0; }


    T_iterator      beginFast() const       { return T_iterator(*this);      }
  //T_constIterator beginFast() const { return T_constIterator(*this); }

    iterator       begin()       { return data_; }
    const_iterator begin() const { return data_; }

    iterator       end()       { return data_ + N_length; }
    const_iterator end() const { return data_ + N_length; }

    T_numtype * restrict data()
    { return data_; }

    const T_numtype * restrict data() const
    { return data_; }

    T_numtype * restrict dataFirst()
    { return data_; }

    const T_numtype * restrict dataFirst() const
    { return data_; }

  static int                               lbound(int rank) 
  { return 0; }
  static int            lbound() 
  { return 0; }

  static int                               length(int rank) 
  { return N_length; }
  static int    length() 
  { return N_length; }

  static int                               ordering(int storageRankIndex) 
  { return 0; }

  static int    ordering() 
  { return 0; }

  static  int                               rank()
    { return rank_; }

    static sizeType                               numElements() 
  { return length(); }

    static diffType    stride() 
    { return 1; }

  static diffType                               stride(int rank) 
    { return 1; }

  static int                               ubound(int rank) 
  { return length()-1; }

  static int           ubound() 
  { return length()-1; }

    /////////////////////////////////////////////
    // Library-internal member functions
    // These are undocumented and may change or
    // disappear in future releases.
    /////////////////////////////////////////////

    // unsigned _bz_suggestLength() const
    // { return N_length; }

    // bool _bz_hasFastAccess() const
    // { return true; }

    // T_numtype& restrict _bz_fastAccess(unsigned i)
    // { return data_[i]; }

    // T_numtype _bz_fastAccess(unsigned i) const
    // { return data_[i]; }

     template<typename P_expr, typename P_updater>
     void _bz_assign(P_expr, P_updater);

    // _bz_VecExpr<T_constIterator> _bz_asVecExpr() const
    // { return _bz_VecExpr<T_constIterator>(beginFast()); }
   
    //////////////////////////////////////////////
    // Subscripting operators
    //////////////////////////////////////////////

    bool lengthCheck(unsigned i) const
    {
        BZPRECHECK(i < N_length, 
            "TinyVector2<" << BZ_DEBUG_TEMPLATE_AS_STRING_LITERAL(T_numtype) 
            << "," << N_length << "> index out of bounds: " << i);
        return true;
    }

    const T_numtype& operator()(unsigned i) const
    {
        BZPRECONDITION(lengthCheck(i));
        return data_[i];
    }

    T_numtype& restrict operator()(unsigned i)
    { 
        BZPRECONDITION(lengthCheck(i));
        return data_[i];
    }

    const T_numtype& operator[](unsigned i) const
    {
        BZPRECONDITION(lengthCheck(i));
        return data_[i];
    }

    T_numtype& restrict operator[](unsigned i)
    {
        BZPRECONDITION(lengthCheck(i));
        return data_[i];
    }

    //////////////////////////////////////////////
    // Assignment operators
    //////////////////////////////////////////////

    // Scalar operand
    ListInitializationSwitch<T_vector,T_numtype*> operator=(T_numtype x)
    {
        return ListInitializationSwitch<T_vector,T_numtype*>(*this, x);
    }

  T_vector& initialize(T_numtype);

    template<typename T_expr>
    T_vector& operator=(const ETBase<T_expr>&);
    T_vector& operator=(const TinyVector2<T_numtype,N_length>&);

    template<typename T> T_vector& operator+=(const T&);
    template<typename T> T_vector& operator-=(const T&);
    template<typename T> T_vector& operator*=(const T&);
    template<typename T> T_vector& operator/=(const T&);
    template<typename T> T_vector& operator%=(const T&);
    template<typename T> T_vector& operator^=(const T&);
    template<typename T> T_vector& operator&=(const T&);
    template<typename T> T_vector& operator|=(const T&);
    template<typename T> T_vector& operator>>=(const T&);
    template<typename T> T_vector& operator<<=(const T&);

    T_numtype* restrict getInitializationIterator()
    { return dataFirst(); }

private:
    T_numtype data_[N_length];
};


// Specialization for N = 0: KCC is giving some
// peculiar errors, perhaps this will fix.

template<typename T>
class TinyVector2<T,0> {
};

//  A tinyvector operand

template <typename T,int N>
struct asExpr<TinyVector2<T,N> > {
    typedef FastTV2Iterator<T,N> T_expr;
    static T_expr getExpr(const TinyVector2<T,N>& x) { return x.beginFast(); }
};

BZ_NAMESPACE_END

#include <blitz/tv2fastiter.h>  // Iterators
#include <blitz/tv2ops.cc>
#include <blitz/tinyvec2.cc>
#include <blitz/tinyvec2io.cc>

#endif // BZ_TINYVEC_H

