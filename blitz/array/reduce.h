// -*- C++ -*-
/***************************************************************************
 * blitz/array/reduce.h   Reductions of an array (or array expression) in a 
 *                        single rank: sum, mean, min, minIndex, max, maxIndex,
 *                        product, count, any, all
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
#ifndef BZ_ARRAYREDUCE_H
#define BZ_ARRAYREDUCE_H

#ifndef BZ_ARRAYEXPR_H
 #error <blitz/array/reduce.h> must be included after <blitz/array/expr.h>
#endif

#include <blitz/reduce.h>

BZ_NAMESPACE(blitz)

template<bool needIndex,bool needInit> struct _bz_ReduceReset;

template<>
struct _bz_ReduceReset<true,true> {
    template<typename T_reduction,typename T_index,typename T_expr>
    void operator()(T_reduction& reduce,const T_index& index,const T_expr& expr) {
        reduce.reset(index,expr.first_value());
    }
};

template<>
struct _bz_ReduceReset<false,true> {
    template<typename T_reduction,typename T_index,typename T_expr>
    void operator()(T_reduction& reduce,const T_index&,const T_expr& expr) {
        reduce.reset(expr.first_value());
    }
};

template<>
struct _bz_ReduceReset<true,false> {
    template<typename T_reduction,typename T_index,typename T_expr>
    void operator()(T_reduction& reduce,const T_index& index,const T_expr&) {
        reduce.reset(index);
    }
};

template<>
struct _bz_ReduceReset<false,false> {
    template<typename T_reduction,typename T_index,typename T_expr>
    void operator()(T_reduction& reduce,const T_index&,const T_expr&) {
        reduce.reset();
    }
};

template<typename T_expr, int N_index, typename T_reduction>
class _bz_ArrayExprReduce {

public:   
    typedef _bz_typename T_reduction::T_numtype T_numtype;
    typedef T_expr      T_ctorArg1;
    typedef T_reduction T_ctorArg2;
  typedef int  T_range_result; // dummy

    static const int 
        numArrayOperands = T_expr::numArrayOperands,
        numIndexPlaceholders = T_expr::numIndexPlaceholders + 1,
        rank = T_expr::rank - 1;

    _bz_ArrayExprReduce(const _bz_ArrayExprReduce& reduce)
        : reduce_(reduce.reduce_), iter_(reduce.iter_), ordering_(reduce.ordering_) { }

    _bz_ArrayExprReduce(T_expr expr)
        : iter_(expr)
    { computeOrdering(); }

#if 0
    _bz_ArrayExprReduce(T_expr expr, T_reduction reduce)
        : iter_(expr), reduce_(reduce)
    { computeOrdering(); }
#endif

    int ascending(const int r) const { return iter_.ascending(r); }
    int ordering(const int r)  const { return ordering_[r];       }
    int lbound(const int r)    const { return iter_.lbound(r);    }
    int ubound(const int r)    const { return iter_.ubound(r);    }
    RectDomain<rank> domain() const { return iter_.domain(); }

    template<int N_destRank>
    T_numtype operator()(const TinyVector<int, N_destRank>& destIndex) const
    {
        BZPRECHECK(N_destRank == N_index,  
            "Array reduction performed over rank " << N_index 
            << " to produce a rank " << N_destRank << " expression." << endl
            << "You must reduce over rank " << N_destRank << " instead.");

        TinyVector<int, N_destRank + 1> index;

        // This metaprogram copies elements 0..N-1 of destIndex into index
        _bz_meta_vecAssign<N_index, 0>::assign(index, destIndex, 
            _bz_update<int,int>());

        int lbound = iter_.lbound(N_index);
        int ubound = iter_.ubound(N_index);

        BZPRECHECK((lbound != tiny(int())) && (ubound != huge(int())),
           "Array reduction performed over rank " << N_index
           << " is unbounded." << endl 
           << "There must be an array object in the expression being reduced"
           << endl << "which provides a bound in rank " << N_index << ".");

        // If we are doing minIndex/maxIndex, initialize with lower bound

        _bz_ReduceReset<T_reduction::needIndex,T_reduction::needInit> reset;
        reset(reduce_,lbound,iter_);

        for (index[N_index]=lbound; index[N_index]<=ubound; ++index[N_index]) {
            if (!reduce_(iter_(index), index[N_index]))
                break;
        }

        return reduce_.result(ubound-lbound+1);
    }

    // If you have a precondition failure on these routines, it means
    // you are trying to use stack iteration mode on an expression
    // which contains an index placeholder.  You must use index
    // iteration mode instead.

    int operator*()        const { BZPRECONDITION(0); return 0; }
    int suggestStride(int) const { BZPRECONDITION(0); return 0; }

    void push(int)           const { BZPRECONDITION(0); }
    void pop(int)            const { BZPRECONDITION(0); }
    void advance()           const { BZPRECONDITION(0); }
    void advance(int)        const { BZPRECONDITION(0); }
    void loadStride(int)     const { BZPRECONDITION(0); }
    void advanceUnitStride() const { BZPRECONDITION(0); }

    template<int N_rank>
    void moveTo(const TinyVector<int,N_rank>&) const { BZPRECONDITION(0); }

    bool isUnitStride(int)    const { BZPRECONDITION(0); return false; }
    bool canCollapse(int,int) const { BZPRECONDITION(0); return false; }
    bool isStride(int,int)    const { BZPRECONDITION(0); return true;  }

    T_numtype operator[](int) const { BZPRECONDITION(0); return T_numtype(); }
    T_numtype fastRead(int)   const { BZPRECONDITION(0); return T_numtype(); }

    // don't know how to define these, so stencil expressions won't work
    T_numtype shift(int offset, int dim) const
  { BZPRECONDITION(0); return T_numtype(); }
    T_numtype shift(int offset1, int dim1,int offset2, int dim2) const 
  { BZPRECONDITION(0); return T_numtype(); }
    void _bz_offsetData(sizeType i) { BZPRECONDITION(0); }

  // Unclear how to define this, and stencils don't work anyway
  T_range_result operator()(RectDomain<rank> d) const
  { BZPRECONDITION(0); }

    void prettyPrint(BZ_STD_SCOPE(string) &str, prettyPrintFormat& format) const
    {
        // NEEDS_WORK-- do real formatting for reductions
        str += "reduce[NEEDS_WORK](";
        iter_.prettyPrint(str,format);
        str += ")";
    }

    template<typename T_shape>
    bool shapeCheck(const T_shape&) const
    { 
        // NEEDS_WORK-- do a real shape check (tricky)
        return true; 
    }

  // sliceinfo for expressions
  template<typename T1, typename T2 = nilArraySection, 
	   class T3 = nilArraySection, typename T4 = nilArraySection, 
	   class T5 = nilArraySection, typename T6 = nilArraySection, 
	   class T7 = nilArraySection, typename T8 = nilArraySection, 
	   class T9 = nilArraySection, typename T10 = nilArraySection, 
	   class T11 = nilArraySection>
  class SliceInfo {
  public:
    typedef typename T_expr::template SliceInfo<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11>::T_slice T_slice1;
    typedef _bz_ArrayExprReduce<T_slice1, N_index, T_reduction> T_slice;
};

    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6,
        typename T7, typename T8, typename T9, typename T10, typename T11>
    typename SliceInfo<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11>::T_slice
    operator()(T1 r1, T2 r2, T3 r3, T4 r4, T5 r5, T6 r6, T7 r7, T8 r8, T9 r9, T10 r10, T11 r11) const
    {
      // for slicing reduction results, we would need to set the
      // dimension reduced over to Range::all(). That's not easy to do
      // because it requires us to change the type of one of the rn's.
      BZPRECONDITION(0);
    }

private: 
    _bz_ArrayExprReduce() { }
// method for properly initializing the ordering values
    void computeOrdering()
    {
        TinyVector<bool,rank> in_ordering;
        in_ordering = false;

        int j = 0;
        for (int i=0; i<rank; ++i) {
            const int orderingj = iter_.ordering(i);
            if (orderingj != tiny(int()) && orderingj < rank && !in_ordering(orderingj)) {
                // unique value in ordering array
                in_ordering(orderingj) = true;
                ordering_(j++) = orderingj;
            }
        }

        // It is possible that ordering is not a permutation of 0,...,rank-1.
        // In that case j will be less than rank. We fill in ordering with
        // the unused values in decreasing order.
        for (int i = rank; j < rank; ++j) {
            while (in_ordering(--i)); // find an unused index
            ordering_(j) = i;
        }
    }

    T_reduction reduce_;
    T_expr iter_;
    TinyVector<int,rank> ordering_;
};

#define BZ_DECL_ARRAY_PARTIAL_REDUCE(fn,reduction)                      \
template<typename T_expr, int N_index>                                  \
inline                                                                  \
_bz_ArrayExpr<_bz_ArrayExprReduce<_bz_ArrayExpr<T_expr>, N_index,       \
    reduction<_bz_typename T_expr::T_numtype> > >                       \
fn(_bz_ArrayExpr<T_expr> expr, const IndexPlaceholder<N_index>&)        \
{                                                                       \
    return _bz_ArrayExprReduce<_bz_ArrayExpr<T_expr>, N_index,          \
        reduction<_bz_typename T_expr::T_numtype> >(expr);              \
}                                                                       \
                                                                        \
template<typename T_numtype, int N_rank, int N_index>                   \
inline                                                                  \
_bz_ArrayExpr<_bz_ArrayExprReduce<FastArrayIterator<T_numtype,N_rank>,  \
    N_index, reduction<T_numtype> > >                                   \
fn(const Array<T_numtype, N_rank>& array,                               \
    const IndexPlaceholder<N_index>&)                                   \
{                                                                       \
    return _bz_ArrayExprReduce<FastArrayIterator<T_numtype,N_rank>,     \
        N_index, reduction<T_numtype> > (array.beginFast());            \
}                        

BZ_DECL_ARRAY_PARTIAL_REDUCE(sum,      ReduceSum)
BZ_DECL_ARRAY_PARTIAL_REDUCE(mean,     ReduceMean)
BZ_DECL_ARRAY_PARTIAL_REDUCE((min),    ReduceMin)
BZ_DECL_ARRAY_PARTIAL_REDUCE(minIndex, ReduceMinIndex)
BZ_DECL_ARRAY_PARTIAL_REDUCE((max),    ReduceMax)
BZ_DECL_ARRAY_PARTIAL_REDUCE(maxIndex, ReduceMaxIndex)
BZ_DECL_ARRAY_PARTIAL_REDUCE(product,  ReduceProduct)
BZ_DECL_ARRAY_PARTIAL_REDUCE(count,    ReduceCount)
BZ_DECL_ARRAY_PARTIAL_REDUCE(any,      ReduceAny)
BZ_DECL_ARRAY_PARTIAL_REDUCE(all,      ReduceAll)
BZ_DECL_ARRAY_PARTIAL_REDUCE(first,    ReduceFirst)
BZ_DECL_ARRAY_PARTIAL_REDUCE(last,     ReduceLast)

/*
 * Complete reductions
 */

// Prototype of reduction functions
template<typename T_expr, typename T_reduction>
_bz_typename T_reduction::T_resulttype
_bz_ArrayExprFullReduce(T_expr expr, T_reduction reduction);

template<typename T_expr, typename T_reduction>
_bz_typename T_reduction::T_resulttype
_bz_reduceWithIndexTraversal(T_expr expr, T_reduction reduction);

template<typename T_expr, typename T_reduction>
_bz_typename T_reduction::T_resulttype
_bz_reduceWithIndexVectorTraversal(T_expr expr, T_reduction reduction);

#define BZ_DECL_ARRAY_FULL_REDUCE(fn,reduction)                         \
template<typename T_expr>                                               \
inline                                                                  \
_bz_typename reduction<_bz_typename T_expr::T_numtype>::T_resulttype    \
fn(_bz_ArrayExpr<T_expr> expr)                                          \
{                                                                       \
    return _bz_ArrayExprFullReduce(expr,                                \
        reduction<_bz_typename T_expr::T_numtype>());                   \
}                                                                       \
                                                                        \
template<typename T_numtype, int N_rank>                                \
inline                                                                  \
_bz_typename reduction<T_numtype>::T_resulttype                         \
fn(const Array<T_numtype, N_rank>& array)                               \
{                                                                       \
    return _bz_ArrayExprFullReduce(array.beginFast(),                   \
        reduction<T_numtype>());                                        \
}                                                                     

BZ_DECL_ARRAY_FULL_REDUCE(sum,      ReduceSum)
BZ_DECL_ARRAY_FULL_REDUCE(mean,     ReduceMean)
BZ_DECL_ARRAY_FULL_REDUCE((min),    ReduceMin)
BZ_DECL_ARRAY_FULL_REDUCE((max),    ReduceMax)
BZ_DECL_ARRAY_FULL_REDUCE((minmax), ReduceMinMax)
BZ_DECL_ARRAY_FULL_REDUCE(product,  ReduceProduct)
BZ_DECL_ARRAY_FULL_REDUCE(count,    ReduceCount)
BZ_DECL_ARRAY_FULL_REDUCE(any,      ReduceAny)
BZ_DECL_ARRAY_FULL_REDUCE(all,      ReduceAll)
BZ_DECL_ARRAY_FULL_REDUCE(first,    ReduceFirst)
BZ_DECL_ARRAY_FULL_REDUCE(last,     ReduceLast)

// Special versions of complete reductions: minIndex and
// maxIndex

#define BZ_DECL_ARRAY_FULL_REDUCE_INDEXVECTOR(fn,reduction)             \
template<typename T_expr>                                               \
inline                                                                  \
_bz_typename reduction<_bz_typename T_expr::T_numtype,                  \
    T_expr::rank>::T_resulttype                                         \
fn(_bz_ArrayExpr<T_expr> expr)                                          \
{                                                                       \
    return _bz_reduceWithIndexVectorTraversal(expr,                     \
        reduction<_bz_typename T_expr::T_numtype, T_expr::rank>());     \
}                                                                       \
                                                                        \
template<typename T_numtype, int N_rank>                                \
inline                                                                  \
_bz_typename reduction<T_numtype,N_rank>::T_resulttype                  \
fn(const Array<T_numtype, N_rank>& array)                               \
{                                                                       \
    return _bz_reduceWithIndexVectorTraversal(array.beginFast(),        \
        reduction<T_numtype,N_rank>());                                 \
}

BZ_DECL_ARRAY_FULL_REDUCE_INDEXVECTOR(minIndex, ReduceMinIndexVector)
BZ_DECL_ARRAY_FULL_REDUCE_INDEXVECTOR(maxIndex, ReduceMaxIndexVector)

BZ_NAMESPACE_END

#include <blitz/array/reduce.cc>

#endif // BZ_ARRAYREDUCE_H
