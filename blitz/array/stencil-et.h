// -*- C++ -*-
/***************************************************************************
 * blitz/array/stencil-et.h  Expression-template-capable stencils
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
#ifndef BZ_ARRAY_STENCIL_ET_H
#define BZ_ARRAY_STENCIL_ET_H

BZ_NAMESPACE(blitz)

/* Stencils as currently implemented rely on being able to give an
   iterator type to the operator. Some methods have been implemented
   to make index traversal work so that operands can include index
   remappings, but it's probably not very efficient. Operands
   containing reductions or index placeholders don't work. */

// Utility function for shrinking the domain of the expression the
// stencil operates on. The minb and maxb may be defined in fewer
// dimensions than the expression, in which the shape is the same in
// higher dims.
template<int N_rank, int N_rank2>
RectDomain<N_rank> _bz_shrinkDomain(const RectDomain<N_rank>& d,
				    const TinyVector<int,N_rank2>& minb,
				    const TinyVector<int,N_rank2>& maxb)
{
  TinyVector<int, N_rank> lb(d.lbound()), ub(d.ubound());
  // no slicing w tinyvector
  for(int i=0; i<N_rank2; ++i) {
    lb[i] = lb[i] - ((minb[i]<0) ? minb[i] : 0);
    ub[i] = ub[i] - ((maxb[i]>0) ? maxb[i] : 0);
  }
  return RectDomain<N_rank>(lb, ub);
}


// Helper function that converts slices to unit ranges
template<typename T>
Range _bz_makeRange(const T& r)
{
  return Range(r);
}

inline nilArraySection _bz_makeRange(const nilArraySection& r)
{
  return r;
}


// necessary because we can't have an #ifdef in the macros
template<typename T> struct _bz_IndexParameter {
#ifdef BZ_ARRAY_EXPR_PASS_INDEX_BY_VALUE
  typedef T type;
#else
  typedef const T& type;
#endif
};

/* There are resolution problems with the functions in this file that
   generate ET objects and the functions in stencilops.h that define
   the stencil operators. Because the operators are defined as
   all-encompassing templates, they will match to arrays with higher
   priority than the functions here will match to ETBase<..>. This
   means we must have explicit functions that match Arrays even though
   the general ETBase function would work. */

/** ET base class for applying a stencil to an expression. */
template<typename P_expr, _bz_typename P_result>
class _bz_StencilExpr {
 public:
  typedef P_expr T_expr;
  typedef P_result T_numtype;
  typedef T_expr T_ctorArg1;
  typedef int    T_ctorArg2;    // dummy
  
  static const int 
    numArrayOperands = T_expr::numArrayOperands,
    numIndexPlaceholders = T_expr::numIndexPlaceholders,
    rank = T_expr::rank;
  
 _bz_StencilExpr(const _bz_StencilExpr<T_expr, T_numtype>& a)
   : iter_(a.iter_)
    { }
  
 _bz_StencilExpr(BZ_ETPARM(T_expr) a)
   : iter_(a)
  { }

 _bz_StencilExpr(_bz_typename T_expr::T_ctorArg1 a)
   : iter_(a)
  { }

#if BZ_TEMPLATE_CTOR_DOESNT_CAUSE_HAVOC
  template<typename T1>
    explicit _bz_StencilExpr(BZ_ETPARM(T1) a)
    : iter_(a)
  { }
#endif

  int ascending(const int rank) const { return iter_.ascending(rank); }
  int ordering(const int rank)  const { return iter_.ordering(rank);  }
  int lbound(const int rank) const
  { 
    return iter_.lbound(rank);    
  }
  int ubound(const int rank) const 
  {
    return iter_.ubound(rank);
  }

  // defer calculation to lbound/ubound
  RectDomain<rank> domain() const 
    { 
      TinyVector<int, rank> lb, ub;
      for(int r=0; r<rank; ++r) {
	lb[r]=lbound(r); ub[r]=ubound(r); 
      }
      return RectDomain<rank>(lb,ub);
    }

  //T_numtype first_value() const { return iter_(iter_.lbound()); }

  void push(int position)
  {
    iter_.push(position);
  }

  void pop(int position)
  {
    iter_.pop(position);
  }

  void advance()
  {
    iter_.advance();
  }

  void advance(int n)
  {
    iter_.advance(n);
  }

  void loadStride(int rank)
  {
    iter_.loadStride(rank);
  }

  bool isUnitStride(int rank) const
  { return iter_.isUnitStride(rank); }

  void advanceUnitStride()
  {
    iter_.advanceUnitStride();
  }

  void moveTo(const TinyVector<int,_bz_StencilExpr::rank>& i)
  {
    iter_.moveTo(i);
  }

  bool canCollapse(int outerLoopRank, int innerLoopRank) const
  { 
    // BZ_DEBUG_MESSAGE("_bz_StencilExpr<>::canCollapse");
    return iter_.canCollapse(outerLoopRank, innerLoopRank); 
  }

  diffType suggestStride(int rank) const
  { return iter_.suggestStride(rank); }

  bool isStride(int rank, diffType stride) const
  { return iter_.isStride(rank,stride); }

  void _bz_offsetData(sizeType i) { iter_._bz_offsetData(i); }

  void prettyPrint(BZ_STD_SCOPE(string) &str) const
  {
    prettyPrintFormat format(true);  /* Terse formatting by default */
    iter_.prettyPrint(str, format);
  }

  template<typename T_shape>
    bool shapeCheck(const T_shape& shape) const
    { return iter_.shapeCheck(shape); }

 protected:
  _bz_StencilExpr() { }

  // it needs to be mutable because in the "conceptually const"
  // methods shift and fastread we offset the iterator but undo it
  // later
  mutable P_expr iter_;
};

/** ET base class for applying a stencil to an expression. */
template<typename P_expr1, typename P_expr2, _bz_typename P_result>
class _bz_StencilExpr2 {
 public:
  typedef P_expr1 T_expr1;
  typedef P_expr2 T_expr2;
  typedef _bz_typename T_expr1::T_numtype T_numtype1;
  typedef _bz_typename T_expr2::T_numtype T_numtype2;
  typedef P_result T_numtype;
  typedef T_expr1 T_ctorArg1;
  typedef T_expr2 T_ctorArg2;
  
  static const int 
  numArrayOperands = T_expr1::numArrayOperands
    + T_expr2::numArrayOperands,
    numIndexPlaceholders = T_expr1::numIndexPlaceholders
    + T_expr2::numIndexPlaceholders,
    rank = (T_expr1::rank > T_expr2::rank) 
    ? T_expr1::rank : T_expr2::rank;
  
  _bz_StencilExpr2(const _bz_StencilExpr2<T_expr1, T_expr2, T_numtype>& a)
    : iter1_(a.iter1_), iter2_(a.iter2_)
    { }
  
  _bz_StencilExpr2(BZ_ETPARM(T_expr1) a, BZ_ETPARM(T_expr2) b)
    : iter1_(a), iter2_(b)
  { }

  /*
  // what is this for?
 _bz_StencilExpr2(_bz_typename T_expr1::T_ctorArg1 a)
   : iter_(a)
  { }
  */

#if BZ_TEMPLATE_CTOR_DOESNT_CAUSE_HAVOC
  template<typename T1, typename T2>
  explicit _bz_StencilExpr2(BZ_ETPARM(T1) a, BZ_ETPARM(T2) b)
    : iter1_(a), iter2_(b)
  { }
#endif

    int ascending(const int rank) const {
        return bounds::compute_ascending(rank, iter1_.ascending(rank), iter2_.ascending(rank));
    }

    int ordering(const int rank) const {
        return bounds::compute_ordering(rank, iter1_.ordering(rank), iter2_.ordering(rank));
    }

    int lbound(const int rank) const { 
        return bounds::compute_lbound(rank, iter1_.lbound(rank), iter2_.lbound(rank));
    }

    int ubound(const int rank) const {
        return bounds::compute_ubound(rank, iter1_.ubound(rank), iter2_.ubound(rank));
    }

  // defer calculation to lbound/ubound
  RectDomain<rank> domain() const 
  { 
    TinyVector<int, rank> lb, ub;
    for(int r=0; r<rank; ++r) {
      lb[r]=lbound(r); ub[r]=ubound(r); 
    }
    return RectDomain<rank>(lb,ub);
  }

    void push(int position)
    { 
        iter1_.push(position); 
        iter2_.push(position);
    }

    void pop(int position)
    { 
        iter1_.pop(position); 
        iter2_.pop(position);
    }

    void advance()
    { 
        iter1_.advance(); 
        iter2_.advance();
    }

    void advance(int n)
    {
        iter1_.advance(n);
        iter2_.advance(n);
    }

    void loadStride(int rank)
    { 
        iter1_.loadStride(rank); 
        iter2_.loadStride(rank);
    }

    diffType suggestStride(int rank) const
    {
        diffType stride1 = iter1_.suggestStride(rank);
        diffType stride2 = iter2_.suggestStride(rank);
        return (stride1 > stride2) ? stride1 : stride2;
    }

    bool isStride(int rank, diffType stride) const
    {
        return iter1_.isStride(rank,stride) && iter2_.isStride(rank,stride);
    }
    
    bool isUnitStride(int rank) const
    { return iter1_.isUnitStride(rank) && iter2_.isUnitStride(rank); }

    void advanceUnitStride()
    { 
        iter1_.advanceUnitStride(); 
        iter2_.advanceUnitStride();
    }

    bool canCollapse(int outerLoopRank, int innerLoopRank) const
    { 
        return iter1_.canCollapse(outerLoopRank, innerLoopRank)
            && iter2_.canCollapse(outerLoopRank, innerLoopRank);
    }

    void moveTo(const TinyVector<int,rank>& i)
    {
        iter1_.moveTo(i);
        iter2_.moveTo(i);
    }

  void _bz_offsetData(sizeType i) 
  {
    iter1_._bz_offsetData(i);
    iter2_._bz_offsetData(i);
  }

  template<typename T_shape>
    bool shapeCheck(const T_shape& shape) const
  { return iter1_.shapeCheck(shape) && iter2_.shapeCheck(shape); }

 protected:
  _bz_StencilExpr2() { }

  mutable P_expr1 iter1_;
  mutable P_expr2 iter2_;
};

/* To avoid matching to the stencil operator in stencilops.h, we must
   explicitly define stencils that operate on arrays. This macro makes
   this slightly less painful for the majority of the stencil classes. */
#define BZ_ET_STENCIL_REDIRECT(name)					\
  template<typename T, int N>						\
   inline _bz_ArrayExpr<name ## _et<_bz_typename BZ_BLITZ_SCOPE(asExpr)<Array<T,N> >::T_expr::T_range_result> > \
   name(const Array<T,N>& d1)						\
   { return name(d1.wrap()); }						\
   template<typename T, int N>						\
   inline _bz_ArrayExpr<name ## _et<_bz_typename BZ_BLITZ_SCOPE(asExpr)<Array<T,N> >::T_expr::T_range_result> > \
   name(Array<T,N>& d1)							\
   { return name(d1.wrap()); }


/* Defines a stencil ET that operates on an array<P_numtype, N_rank>
   and specifies the return type as array<result, N_rank>. The result
   type is used when running on an array and the etresult type when
   running on an expression. If you want to refer to the native type
   of the expression, set result="P_numtype" and etresult="typename
   T1::T_numtype". Sorry for that ugliness, but they define types
   differently. */

#define BZ_ET_STENCIL(name,result, etresult, MINB, MAXB)		\
  template<typename P_expr, _bz_typename P_numtype>			\
  class name ## _et : public _bz_StencilExpr<P_expr, P_numtype>		\
  {									\
  public:								\
    typedef _bz_StencilExpr<P_expr, P_numtype> T_base;			\
    typedef _bz_typename T_base::T_numtype T_numtype;			\
    typedef _bz_typename T_base::T_expr T_expr;				\
    typedef  name ## _et<_bz_typename P_expr::T_range_result, T_numtype> T_range_result; \
									\
    using T_base::iter_;						\
    using T_base::rank;							\
  public:								\
    name ## _et(const name ## _et& a) :					\
    _bz_StencilExpr<P_expr, T_numtype>(a)				\
      { }								\
									\
    name ## _et(BZ_ETPARM(T_expr) a) :					\
    _bz_StencilExpr<P_expr, T_numtype>(a)				\
      { }								\
									\
    name ## _et(_bz_typename T_expr::T_ctorArg1 a) :			\
    _bz_StencilExpr<P_expr, T_numtype>(a)				\
      { }								\
									\
    T_numtype operator*() const						\
    { return name(iter_); }						\
									\
    /* this is not really const, because we don't undo the moveTo, but	\
       that should not be visible to outside. It would be if we used	\
       some kind of mixed index and stack traversal, but that will	\
       screw things up, const or not. */				\
    template<int N_rank2>						\
      T_numtype operator()(const TinyVector<int, N_rank2>& i) const	\
    { iter_.moveTo(i); return name(iter_); }				\
    									\
    T_range_result operator()(const RectDomain<rank>& d) const		\
    { return T_range_result(iter_(d)); }				\
									\
    T_numtype operator[](int i) const					\
    { return name(iter_[i]); }						\
									\
    T_numtype fastRead(sizeType i) const				\
    {/* this probably isn't very fast... */				\
      iter_._bz_offsetData(i);						\
      T_numtype r = name (iter_);					\
      iter_._bz_offsetData(-i);						\
      return r;								\
    }									\
    									\
    T_numtype shift(int offset, int dim) const				\
    {									\
      iter_._bz_offsetData(offset, dim);				\
      T_numtype r = name (iter_);					\
      iter_._bz_offsetData(-offset, dim);				\
      return r;								\
    }									\
									\
    T_numtype shift(int offset1, int dim1, int offset2, int dim2) const	\
    {									\
      iter_._bz_offsetData(offset1, dim1, offset2, dim2);		\
      T_numtype r = name (iter_);					\
      iter_._bz_offsetData(-offset1, dim1, -offset2, dim2);		\
      return r;								\
    }									\
									\
    void prettyPrint(BZ_STD_SCOPE(string) &str,				\
		     prettyPrintFormat& format) const			\
    {									\
      str += "name (stencil)";						\
      str += "(";							\
      iter_.prettyPrint(str, format);					\
      str += ")";							\
    }									\
    									\
    template<typename T1, typename T2 = nilArraySection,		\
      class T3 = nilArraySection, typename T4 = nilArraySection,	\
      class T5 = nilArraySection, typename T6 = nilArraySection,	\
      class T7 = nilArraySection, typename T8 = nilArraySection,	\
      class T9 = nilArraySection, typename T10 = nilArraySection,	\
      class T11 = nilArraySection>					\
      class SliceInfo {							\
      public:								\
      typedef name ## _et<T_expr, T_numtype> T_slice;			\
      };								\
    									\
    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, \
      typename T7, typename T8, typename T9, typename T10, typename T11> \
      name ## _et							\
      operator()(T1 r1, T2 r2, T3 r3, T4 r4, T5 r5, T6 r6, T7 r7, T8 r8, T9 r9, T10 r10, T11 r11) const \
    {									\
    /* because stencils work inherently in several dimensions it's	\
       complicated to slice the domain. slices will be changed to unit	\
       \ ranges instead. slicing stencil result thus *never* changes	\
       the rank of the expression, unlike the normal case. */		\
      return name ## _et						\
	(iter_(_bz_makeRange(r1),					\
	       _bz_makeRange(r2),					\
	       _bz_makeRange(r3),					\
	       _bz_makeRange(r4),					\
	       _bz_makeRange(r5),					\
	       _bz_makeRange(r6),					\
	       _bz_makeRange(r7),					\
	       _bz_makeRange(r8),					\
	       _bz_makeRange(r9),					\
	       _bz_makeRange(r10),					\
	       _bz_makeRange(r11)));					\
    }									\
									\
  };									\
  /* generate an ET object from an expression */			\
  template<typename T1>							\
  inline _bz_ArrayExpr<name ## _et<typename BZ_BLITZ_SCOPE(asExpr)<T1>::T_expr::T_range_result, etresult> > \
  name(const BZ_BLITZ_SCOPE(ETBase)<T1>& d1)				\
  {									\
    return _bz_ArrayExpr<name ## _et<typename BZ_BLITZ_SCOPE(asExpr)<T1>::T_expr::T_range_result, etresult> > \
      (BZ_BLITZ_SCOPE(asExpr)<T1>::getExpr(d1.unwrap())(_bz_shrinkDomain(d1.unwrap().domain(),MINB, MAXB))); \
  }									\
  /* redirect calls with bare arrays to the main function */		\
  template<typename T, int N>						\
  inline _bz_ArrayExpr<name ## _et<typename BZ_BLITZ_SCOPE(asExpr)<Array<T,N> >::T_expr::T_range_result, result> > \
  name(const Array<T,N>& d1)						\
  { return name(d1.wrap()); }						\
									\
  template<typename T, int N>						\
  inline _bz_ArrayExpr<name ## _et<typename BZ_BLITZ_SCOPE(asExpr)<Array<T,N> >::T_expr::T_range_result, result> > \
  name(Array<T,N>& d1)							\
  { return name(d1.wrap()); }
  

/* Defines a stencil ET that operates on two arrays of arbitrary type
   and specifies the return type as array<result, N_rank>. The result
   type is used when running on an array and the etresult type when
   running on an expression. If you want to refer to the native type
   of the expression, set result="P_numtype" and etresult="typename
   T1::T_numtype". Sorry for that ugliness, but they define types
   differently. */

#define BZ_ET_STENCIL2(name,result, etresult, MINB, MAXB)		\
  template<typename P_expr1, typename P_expr2, _bz_typename P_numtype>	\
  class name ## _et2 : public _bz_StencilExpr2<P_expr1, P_expr2, P_numtype> \
  {									\
  public:								\
    typedef _bz_StencilExpr2<P_expr1, P_expr2, P_numtype> T_base;	\
    typedef _bz_typename T_base::T_numtype T_numtype;			\
    /*    using T_base::T_expr1;					\
	  using T_base::T_expr2; */					\
    typedef _bz_typename T_base::T_expr1 T_expr1;			\
    typedef _bz_typename T_base::T_expr2 T_expr2;			\
    typedef  name ## _et2<_bz_typename P_expr1::T_range_result, _bz_typename P_expr2::T_range_result, T_numtype> T_range_result; \
									\
    using T_base::iter1_;						\
    using T_base::iter2_;						\
    using T_base::rank;							\
  public:								\
    name ## _et2(const name ## _et2& a) :				\
      _bz_StencilExpr2<P_expr1, P_expr2, T_numtype>(a)			\
      { }								\
									\
    name ## _et2(BZ_ETPARM(T_expr1) a, BZ_ETPARM(T_expr2) b) :		\
      _bz_StencilExpr2<P_expr1, P_expr2, T_numtype>(a, b)		\
      { }								\
    /*									\
    name ## _et2(_bz_typename T_expr::T_ctorArg1 a) :			\
      _bz_StencilExpr2<P_expr, T_numtype>(a)				\
      { }								\
    */									\
    T_numtype operator*() const						\
    { return name(iter1_, iter2_); }					\
									\
    T_numtype operator()(_bz_typename _bz_IndexParameter<TinyVector<int, rank> >::type i) const \
    { iter1_.moveTo(i); iter2_.moveTo(i); return name(iter1_, iter2_); } \
									\
    T_range_result operator()(const RectDomain<rank>& d) const		\
    { return T_range_result(iter1_(d), iter2_(d)); }			\
									\
    T_numtype operator[](int i) const					\
    { return name(iter1_[i], iter2_[i]); }				\
									\
    T_numtype fastRead(sizeType i) const					\
    {/* this probably isn't very fast... */				\
      iter1_._bz_offsetData(i); iter2_._bz_offsetData(i);		\
      T_numtype r = name (iter1_, iter2_);				\
      iter1_._bz_offsetData(-i); iter2_._bz_offsetData(-i);		\
      return r;								\
    }									\
    									\
    T_numtype shift(int offset, int dim) const				\
    {									\
      iter1_._bz_offsetData(offset, dim);				\
      iter2_._bz_offsetData(offset, dim);				\
      T_numtype r = name (iter1_, iter2_);				\
      iter1_._bz_offsetData(-offset, dim);				\
      iter2_._bz_offsetData(-offset, dim);				\
      return r;								\
    }									\
									\
    T_numtype shift(int offset1, int dim1, int offset2, int dim2) const	\
    {									\
      iter1_._bz_offsetData(offset1, dim1, offset2, dim2);		\
      iter2_._bz_offsetData(offset1, dim1, offset2, dim2);		\
      T_numtype r = name (iter1_, iter2_);				\
      iter1_._bz_offsetData(-offset1, dim1, -offset2, dim2);		\
      iter2_._bz_offsetData(-offset1, dim1, -offset2, dim2);		\
      return r;								\
    }									\
									\
    void prettyPrint(BZ_STD_SCOPE(string) &str,				\
		     prettyPrintFormat& format) const			\
    {									\
      str += "name (stencil)";						\
      str += "(";							\
      iter1_.prettyPrint(str, format);					\
      str += ", ";							\
      iter2_.prettyPrint(str, format);					\
      str += ")";							\
    }									\
									\
    template<typename T1, typename T2 = nilArraySection,		\
      class T3 = nilArraySection, typename T4 = nilArraySection,	\
      class T5 = nilArraySection, typename T6 = nilArraySection,	\
      class T7 = nilArraySection, typename T8 = nilArraySection,	\
      class T9 = nilArraySection, typename T10 = nilArraySection,	\
      class T11 = nilArraySection>					\
      class SliceInfo {							\
      public:								\
      typedef name ## _et2<T_expr1, T_expr2, T_numtype> T_slice;	\
      };								\
    									\
    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, \
      typename T7, typename T8, typename T9, typename T10, typename T11> \
      name ## _et2							\
      operator()(T1 r1, T2 r2, T3 r3, T4 r4, T5 r5, T6 r6, T7 r7, T8 r8, T9 r9, T10 r10, T11 r11) const \
    {									\
      return name ## _et2						\
	(iter_(_bz_makeRange(r1),					\
	       _bz_makeRange(r2),					\
	       _bz_makeRange(r3),					\
	       _bz_makeRange(r4),					\
	       _bz_makeRange(r5),					\
	       _bz_makeRange(r6),					\
	       _bz_makeRange(r7),					\
	       _bz_makeRange(r8),					\
	       _bz_makeRange(r9),					\
	       _bz_makeRange(r10),					\
	       _bz_makeRange(r11)));					\
    }									\
  };									\
									\
  /* create ET object from application to expression */			\
  template<typename T1, typename T2>					\
  inline _bz_ArrayExpr<name ## _et2<typename BZ_BLITZ_SCOPE(asExpr)<T1>::T_expr::T_range_result, typename BZ_BLITZ_SCOPE(asExpr)<T2>::T_expr::T_range_result, etresult> > \
  name(const BZ_BLITZ_SCOPE(ETBase)<T1>& d1,				\
       const BZ_BLITZ_SCOPE(ETBase)<T2>& d2)				\
  {									\
    return _bz_ArrayExpr<name ## _et2<typename BZ_BLITZ_SCOPE(asExpr)<T1>::T_expr::T_range_result, typename BZ_BLITZ_SCOPE(asExpr)<T2>::T_expr::T_range_result, etresult> > \
      (BZ_BLITZ_SCOPE(asExpr)<T1>::getExpr(d1.unwrap())(_bz_shrinkDomain(d1.unwrap().domain(),MINB, MAXB)), \
       BZ_BLITZ_SCOPE(asExpr)<T2>::getExpr(d2.unwrap())(_bz_shrinkDomain(d2.unwrap().domain(),MINB, MAXB))); \
  }									\
  /* matches to calls involving bare arrays (this is very annoying	\
     because we have to exactly match every possible call combination	\
     to ensure that this matches instead of the operator in		\
     stencilops.h) */							\
  template<typename T1, typename T2, int N2>				\
  inline _bz_ArrayExpr<name ## _et2<typename BZ_BLITZ_SCOPE(asExpr)<T1>::T_expr::T_range_result, typename BZ_BLITZ_SCOPE(asExpr)<Array<T2,N2> >::T_expr::T_range_result, result> > \
  name(const BZ_BLITZ_SCOPE(ETBase)<T1>& d1, Array<T2,N2>& d2)		\
  { return name(d1.wrap(), d2.wrap()); }				\
									\
  template<typename T1, typename T2, int N2>				\
  inline _bz_ArrayExpr<name ## _et2<typename BZ_BLITZ_SCOPE(asExpr)<T1>::T_expr::T_range_result, typename BZ_BLITZ_SCOPE(asExpr)<Array<T2,N2> >::T_expr::T_range_result, result> > \
  name(const BZ_BLITZ_SCOPE(ETBase)<T1>& d1, const Array<T2,N2>& d2)	\
  { return name(d1.wrap(), d2.wrap()); }				\
									\
  template<typename T1, int N1, typename T2>				\
  inline _bz_ArrayExpr<name ## _et2<typename BZ_BLITZ_SCOPE(asExpr)<Array<T1,N1> >::T_expr::T_range_result, typename BZ_BLITZ_SCOPE(asExpr)<T2>::T_expr::T_range_result, result> > \
  name(Array<T1,N1>& d1, const BZ_BLITZ_SCOPE(ETBase)<T2>& d2)		\
  { return name(d1.wrap(), d2.wrap()); }				\
									\
  template<typename T1, int N1, typename T2>				\
  inline _bz_ArrayExpr<name ## _et2<typename BZ_BLITZ_SCOPE(asExpr)<Array<T1,N1> >::T_expr::T_range_result, typename BZ_BLITZ_SCOPE(asExpr)<T2>::T_expr::T_range_result, result> > \
  name(const Array<T1,N1>& d1, const BZ_BLITZ_SCOPE(ETBase)<T2>& d2)	\
  { return name(d1.wrap(), d2.wrap()); }				\
									\
  template<typename T1, int N1, typename T2, int N2>			\
  inline _bz_ArrayExpr<name ## _et2<typename BZ_BLITZ_SCOPE(asExpr)<Array<T1,N1> >::T_expr::T_range_result, typename BZ_BLITZ_SCOPE(asExpr)<Array<T2,N2> >::T_expr::T_range_result, result> > \
  name(const Array<T1,N1>& d1, Array<T2,N2>& d2)				\
  { return name(d1.wrap(), d2.wrap()); }				\
									\
  template<typename T1, int N1, typename T2, int N2>			\
  inline _bz_ArrayExpr<name ## _et2<typename BZ_BLITZ_SCOPE(asExpr)<Array<T1,N1> >::T_expr::T_range_result, typename BZ_BLITZ_SCOPE(asExpr)<Array<T2,N2> >::T_expr::T_range_result, result> > \
  name(Array<T1,N1>& d1, const Array<T2,N2>& d2)			\
  { return name(d1.wrap(), d2.wrap()); }				\
  									\
  template<typename T, int N>						\
  inline _bz_ArrayExpr<name ## _et2<typename BZ_BLITZ_SCOPE(asExpr)<Array<T,N> >::T_expr::T_range_result, typename BZ_BLITZ_SCOPE(asExpr)<Array<T,N> >::T_expr::T_range_result, result> > \
  name(Array<T,N>& d1, Array<T,N>& d2)					\
  { return name(d1.wrap(), d2.wrap()); }				\
									\
  template<typename T, int N>						\
  inline _bz_ArrayExpr<name ## _et2<typename BZ_BLITZ_SCOPE(asExpr)<Array<T,N> >::T_expr::T_range_result, typename BZ_BLITZ_SCOPE(asExpr)<Array<T,N> >::T_expr::T_range_result, result> > \
  name(const Array<T,N>& d1, const Array<T,N>& d2)			\
  { return name(d1.wrap(), d2.wrap()); }


 /* Defines a stencil ET that operates on an array<P_numtype, N_rank>
    and returns a multicomponent array<TinyMatrix<P_numtype::T_element,
    rank, rank> >, N_rank>. P_numtype can be a TinyVector or a scalar,
    I think. */

 #define BZ_ET_STENCILM(name,result_rank, MINB, MAXB)			\
   template<typename P_expr>						\
   class name ## _et : public _bz_StencilExpr<P_expr, TinyMatrix<_bz_typename multicomponent_traits<typename P_expr::T_numtype>::T_element, result_rank, result_rank> > \
   {									\
 public:									\
     typedef _bz_StencilExpr<P_expr, TinyMatrix<_bz_typename multicomponent_traits<typename P_expr::T_numtype>::T_element, result_rank, result_rank> > T_base; \
     typedef _bz_typename T_base::T_numtype T_numtype;			\
     typedef _bz_typename T_base::T_expr T_expr;				\
     typedef  name ## _et<_bz_typename P_expr::T_range_result> T_range_result; \
									 \
     using T_base::iter_;						\
     using T_base::rank;						\
   public:								\
     name ## _et(const name ## _et& a) :				\
       _bz_StencilExpr<P_expr, T_numtype>(a)				\
       { }								\
     									\
     name ## _et(BZ_ETPARM(T_expr) a) :					\
       _bz_StencilExpr<P_expr, T_numtype>(a)				\
       { }								\
									 \
     name ## _et(_bz_typename T_expr::T_ctorArg1 a) :			\
       _bz_StencilExpr<P_expr, T_numtype>(a)				\
       { }								\
     									\
     T_numtype operator*() const					\
     { return name(iter_); }						\
     T_numtype operator()(_bz_typename _bz_IndexParameter<TinyVector<int, rank> >::type i) const \
     { iter_.moveTo(i); return name(iter_); }				\
     									\
     T_range_result operator()(const RectDomain<rank>& d) const		\
     { return T_range_result(iter_(d)); }				\
     									\
     T_numtype operator[](int i) const					\
     { return name(iter_[i]); }						\
     									\
     T_numtype fastRead(sizeType i) const				\
     {/* this probably isn't very fast... */				\
       iter_._bz_offsetData(i);						\
       T_numtype r = name (iter_);					\
       iter_._bz_offsetData(-i);					\
       return r;							\
     }									\
     									\
     T_numtype shift(int offset, int dim) const				\
     {									\
       iter_._bz_offsetData(offset, dim);				\
       T_numtype r = name (iter_);					\
       iter_._bz_offsetData(-offset, dim);				\
       return r;							\
     }									\
									 \
     T_numtype shift(int offset1, int dim1, int offset2, int dim2) const \
     {									\
       iter_._bz_offsetData(offset1, dim1, offset2, dim2);		\
       T_numtype r = name (iter_);					\
       iter_._bz_offsetData(-offset1, dim1, -offset2, dim2);		\
       return r;							\
     }									\
									 \
     void prettyPrint(BZ_STD_SCOPE(string) &str,			\
		      prettyPrintFormat& format) const			\
     {									\
       str += "name (stencil)";						\
       str += "(";							\
       iter_.prettyPrint(str, format);					\
       str += ")";							\
     }									\
									\
    template<typename T1, typename T2 = nilArraySection,		\
      class T3 = nilArraySection, typename T4 = nilArraySection,	\
      class T5 = nilArraySection, typename T6 = nilArraySection,	\
      class T7 = nilArraySection, typename T8 = nilArraySection,	\
      class T9 = nilArraySection, typename T10 = nilArraySection,	\
      class T11 = nilArraySection>					\
      class SliceInfo {							\
      public:								\
      typedef name ## _et<T_expr> T_slice;				\
      };								\
    									\
    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, \
      typename T7, typename T8, typename T9, typename T10, typename T11> \
      name ## _et							\
      operator()(T1 r1, T2 r2, T3 r3, T4 r4, T5 r5, T6 r6, T7 r7, T8 r8, T9 r9, T10 r10, T11 r11) const \
    {									\
      return name ## _et						\
	(iter_(_bz_makeRange(r1),					\
	       _bz_makeRange(r2),					\
	       _bz_makeRange(r3),					\
	       _bz_makeRange(r4),					\
	       _bz_makeRange(r5),					\
	       _bz_makeRange(r6),					\
	       _bz_makeRange(r7),					\
	       _bz_makeRange(r8),					\
	       _bz_makeRange(r9),					\
	       _bz_makeRange(r10),					\
	       _bz_makeRange(r11)));					\
    }									\
   };									\
   /* create ET from application to expression */			\
   template<typename T1>						\
   inline _bz_ArrayExpr<name ## _et<_bz_typename BZ_BLITZ_SCOPE(asExpr)<T1>::T_expr::T_range_result> > \
   name(const BZ_BLITZ_SCOPE(ETBase)<T1>& d1)				\
   {									\
     return _bz_ArrayExpr<name ## _et<_bz_typename BZ_BLITZ_SCOPE(asExpr)<T1>::T_expr::T_range_result> >	\
       (BZ_BLITZ_SCOPE(asExpr)<T1>::getExpr(d1.unwrap())(_bz_shrinkDomain(d1.unwrap().domain(),MINB, MAXB))); \
       }								\
   BZ_ET_STENCIL_REDIRECT(name)						\


 /* Defines a stencil ET that operates on a (scalar) array<P_numtype,
    N_rank> and returns a multicomponent
    array<TinyVector<P_numtype::T_element, result_rank> >, N_rank>. */

 #define BZ_ET_STENCILV(name,result_rank, MINB, MAXB)			\
   template<typename P_expr>						\
   class name ## _et : public _bz_StencilExpr<P_expr, TinyVector<typename P_expr::T_numtype,result_rank> > \
   {									\
 public:									\
     typedef _bz_StencilExpr<P_expr, TinyVector<typename P_expr::T_numtype,result_rank> > T_base; \
     typedef _bz_typename T_base::T_numtype T_numtype;			\
     typedef _bz_typename T_base::T_expr T_expr;				\
     typedef  name ## _et<_bz_typename P_expr::T_range_result> T_range_result; \
									 \
     using T_base::iter_;						\
     using T_base::rank;							\
   public:								\
     name ## _et(const name ## _et& a) :					\
     _bz_StencilExpr<P_expr, T_numtype>(a)				\
       { }								\
									 \
     name ## _et(BZ_ETPARM(T_expr) a) :					\
     _bz_StencilExpr<P_expr, T_numtype>(a)				\
       { }								\
									 \
     name ## _et(_bz_typename T_expr::T_ctorArg1 a) :			\
     _bz_StencilExpr<P_expr, T_numtype>(a)				\
       { }								\
									 \
     T_numtype operator*() const					\
     { return name(iter_); }						\
     T_numtype operator()(_bz_typename _bz_IndexParameter<TinyVector<int, rank> >::type i) const \
     { iter_.moveTo(i); return name(iter_); }				\
									 \
     T_range_result operator()(const RectDomain<rank>& d) const		\
     { return T_range_result(iter_(d)); }				\
									 \
     T_numtype operator[](int i) const					\
     { return name(iter_[i]); }						\
									 \
     T_numtype fastRead(sizeType i) const				\
     {/* this probably isn't very fast... */				\
       iter_._bz_offsetData(i);						\
       T_numtype r = name (iter_);					\
       iter_._bz_offsetData(-i);					\
       return r;							\
     }									\
									 \
     T_numtype shift(int offset, int dim) const				\
     {									\
       iter_._bz_offsetData(offset, dim);				\
       T_numtype r = name (iter_);					\
       iter_._bz_offsetData(-offset, dim);				\
       return r;								\
     }									\
									 \
     T_numtype shift(int offset1, int dim1, int offset2, int dim2) const \
     {									\
       iter_._bz_offsetData(offset1, dim1, offset2, dim2);		\
       T_numtype r = name (iter_);					\
       iter_._bz_offsetData(-offset1, dim1, -offset2, dim2);		\
       return r;								\
     }									\
									 \
     void prettyPrint(BZ_STD_SCOPE(string) &str,				\
		      prettyPrintFormat& format) const			\
     {									\
       str += "name (stencil)";						\
       str += "(";							\
       iter_.prettyPrint(str, format);					\
       str += ")";							\
     }									\
									\
    template<typename T1, typename T2 = nilArraySection,		\
      class T3 = nilArraySection, typename T4 = nilArraySection,	\
      class T5 = nilArraySection, typename T6 = nilArraySection,	\
      class T7 = nilArraySection, typename T8 = nilArraySection,	\
      class T9 = nilArraySection, typename T10 = nilArraySection,	\
      class T11 = nilArraySection>					\
      class SliceInfo {							\
      public:								\
      typedef name ## _et<T_expr> T_slice;				\
      };								\
    									\
    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, \
      typename T7, typename T8, typename T9, typename T10, typename T11> \
      name ## _et							\
      operator()(T1 r1, T2 r2, T3 r3, T4 r4, T5 r5, T6 r6, T7 r7, T8 r8, T9 r9, T10 r10, T11 r11) const \
    {									\
      return name ## _et						\
	(iter_(_bz_makeRange(r1),					\
	       _bz_makeRange(r2),					\
	       _bz_makeRange(r3),					\
	       _bz_makeRange(r4),					\
	       _bz_makeRange(r5),					\
	       _bz_makeRange(r6),					\
	       _bz_makeRange(r7),					\
	       _bz_makeRange(r8),					\
	       _bz_makeRange(r9),					\
	       _bz_makeRange(r10),					\
	       _bz_makeRange(r11)));					\
    }									\
   };									\
  /* create ET from application to expression */				\
   template<typename T1>							\
   inline _bz_ArrayExpr<name ## _et<_bz_typename BZ_BLITZ_SCOPE(asExpr)<T1>::T_expr::T_range_result> >	\
   name(const BZ_BLITZ_SCOPE(ETBase)<T1>& d1)				\
   {									\
     return _bz_ArrayExpr<name ## _et<_bz_typename BZ_BLITZ_SCOPE(asExpr)<T1>::T_expr::T_range_result> >	\
       (BZ_BLITZ_SCOPE(asExpr)<T1>::getExpr(d1.unwrap())(_bz_shrinkDomain(d1.unwrap().domain(),MINB, MAXB))); \
   }									\
   BZ_ET_STENCIL_REDIRECT(name)


 /* Defines a stencil ET that operates on an array<P_numtype, N_rank>
    (where P_numtype presumably is a multicomponent type) and returns a
    scalar array<P_numtype::T_element, N_rank>. */

 #define BZ_ET_STENCIL_SCA(name, MINB, MAXB)				\
   template<typename P_expr>						\
   class name ## _et : public _bz_StencilExpr<P_expr, _bz_typename multicomponent_traits<typename P_expr::T_numtype>::T_element> \
   {									\
 public:									\
     typedef _bz_typename multicomponent_traits<typename P_expr::T_numtype>::T_element T_result; \
     typedef _bz_StencilExpr<P_expr, T_result> T_base;			\
     typedef _bz_typename T_base::T_numtype T_numtype;			\
     typedef _bz_typename T_base::T_expr T_expr;				\
     typedef  name ## _et<_bz_typename P_expr::T_range_result> T_range_result; \
									 \
     using T_base::iter_;						\
     using T_base::rank;							\
   public:								\
     name ## _et(const name ## _et& a) :					\
     _bz_StencilExpr<P_expr, T_numtype>(a)				\
       { }								\
									 \
     name ## _et(BZ_ETPARM(T_expr) a) :					\
     _bz_StencilExpr<P_expr, T_numtype>(a)				\
       { }								\
									 \
     name ## _et(_bz_typename T_expr::T_ctorArg1 a) :			\
     _bz_StencilExpr<P_expr, T_numtype>(a)				\
             { }								\
    									\
    T_numtype operator*() const						\
    { return name(iter_); }						\
    T_numtype operator()(_bz_typename _bz_IndexParameter<TinyVector<int, rank> >::type i) const \
    { iter_.moveTo(i); return name(iter_); }				\
									\
    T_range_result operator()(const RectDomain<rank>& d) const		\
    { return T_range_result(iter_(d)); }				\
									\
    T_numtype operator[](int i) const					\
    { return name(iter_[i]); }						\
									\
    T_numtype fastRead(sizeType i) const				\
    {/* this probably isn't very fast... */				\
      iter_._bz_offsetData(i);						\
      T_numtype r = name (iter_);					\
      iter_._bz_offsetData(-i);						\
      return r;								\
    }									\
									\
    T_numtype shift(int offset, int dim) const				\
    {									\
      iter_._bz_offsetData(offset, dim);				\
      T_numtype r = name (iter_);					\
      iter_._bz_offsetData(-offset, dim);				\
      return r;								\
    }									\
									\
    T_numtype shift(int offset1, int dim1, int offset2, int dim2) const	\
    {									\
      iter_._bz_offsetData(offset1, dim1, offset2, dim2);		\
      T_numtype r = name (iter_);					\
      iter_._bz_offsetData(-offset1, dim1, -offset2, dim2);		\
      return r;								\
    }									\
									\
    void prettyPrint(BZ_STD_SCOPE(string) &str,				\
		     prettyPrintFormat& format) const			\
    {									\
      str += "name (stencil)";						\
      str += "(";							\
      iter_.prettyPrint(str, format);					\
      str += ")";							\
    }									\
									\
    template<typename T1, typename T2 = nilArraySection,		\
      class T3 = nilArraySection, typename T4 = nilArraySection,	\
      class T5 = nilArraySection, typename T6 = nilArraySection,	\
      class T7 = nilArraySection, typename T8 = nilArraySection,	\
      class T9 = nilArraySection, typename T10 = nilArraySection,	\
      class T11 = nilArraySection>					\
      class SliceInfo {							\
      public:								\
      typedef name ## _et<T_expr> T_slice;				\
      };								\
    									\
    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, \
      typename T7, typename T8, typename T9, typename T10, typename T11> \
      name ## _et							\
      operator()(T1 r1, T2 r2, T3 r3, T4 r4, T5 r5, T6 r6, T7 r7, T8 r8, T9 r9, T10 r10, T11 r11) const \
    {									\
      return name ## _et						\
	(iter_(_bz_makeRange(r1),					\
	       _bz_makeRange(r2),					\
	       _bz_makeRange(r3),					\
	       _bz_makeRange(r4),					\
	       _bz_makeRange(r5),					\
	       _bz_makeRange(r6),					\
	       _bz_makeRange(r7),					\
	       _bz_makeRange(r8),					\
	       _bz_makeRange(r9),					\
	       _bz_makeRange(r10),					\
	       _bz_makeRange(r11)));					\
    }									\
  };									\
  /* create ET from application to expression */			\
  template<typename T1>							\
  inline _bz_ArrayExpr<name ## _et<_bz_typename BZ_BLITZ_SCOPE(asExpr)<T1>::T_expr::T_range_result> >	\
  name(const BZ_BLITZ_SCOPE(ETBase)<T1>& d1)				\
  {									\
    return _bz_ArrayExpr<name ## _et<_bz_typename BZ_BLITZ_SCOPE(asExpr)<T1>::T_expr::T_range_result> >	\
      (BZ_BLITZ_SCOPE(asExpr)<T1>::getExpr(d1.unwrap())(_bz_shrinkDomain(d1.unwrap().domain(),MINB, MAXB))); \
  }									\
   BZ_ET_STENCIL_REDIRECT(name)


/* Defines a stencil ET difference operator that operates on an
   array<P_numtype, N_rank> and returns a array<P_numtype,
   N_rank>. (The only significance of the "difference" aspect is that
   the operator is assumed to take a second argument which is the
   dimension to do the difference in). MINB and MAXB are integer
   expressions describing the extent of the operator in the operating
   dimension. */

#define BZ_ET_STENCIL_DIFF(name, MINB, MAXB)				\
  template<typename P_expr>						\
  class name ## _et : public _bz_StencilExpr<P_expr, _bz_typename P_expr::T_numtype>	\
  {									\
  public:								\
    typedef _bz_StencilExpr<P_expr, _bz_typename P_expr::T_numtype> T_base; \
    typedef _bz_typename T_base::T_numtype T_numtype;			\
    typedef _bz_typename T_base::T_expr T_expr;				\
    typedef  name ## _et<_bz_typename P_expr::T_range_result> T_range_result; \
									\
    using T_base::iter_;						\
    using T_base::rank;							\
  public:								\
    name ## _et(const name ## _et& a) :				\
    _bz_StencilExpr<P_expr, T_numtype>(a), dim_(a.dim_)	\
      { }								\
									\
    name ## _et(BZ_ETPARM(T_expr) a, int dim) :			\
      _bz_StencilExpr<P_expr, T_numtype>(a), dim_(dim)		\
      { }								\
									\
    name ## _et(_bz_typename T_expr::T_ctorArg1 a, int dim) :	\
      _bz_StencilExpr<P_expr, T_numtype>(a), dim_(dim)		\
      { }								\
									\
    T_numtype operator*() const						\
    { return name(iter_, dim_); }					\
    T_numtype operator()(_bz_typename _bz_IndexParameter<TinyVector<int, rank> >::type i) const \
    { iter_.moveTo(i); return name(iter_, dim_); }			\
									\
    T_range_result operator()(const RectDomain<rank>& d) const		\
    { return T_range_result(iter_(d), dim_); }				\
									\
    T_numtype operator[](int i) const					\
    { return name(iter_[i], dim_); }					\
									\
    T_numtype fastRead(sizeType i) const				\
    {/* this probably isn't very fast... */				\
      iter_._bz_offsetData(i);						\
      T_numtype r = name (iter_, dim_);					\
      iter_._bz_offsetData(-i);						\
      return r;								\
    }									\
									\
    T_numtype shift(int offset, int dim) const				\
    {									\
      iter_._bz_offsetData(offset, dim);				\
      T_numtype r = name (iter_);					\
      iter_._bz_offsetData(-offset, dim);				\
      return r;								\
    }									\
									\
    T_numtype shift(int offset1, int dim1, int offset2, int dim2) const	\
    {									\
      iter_._bz_offsetData(offset1, dim1, offset2, dim2);		\
      T_numtype r = name (iter_);					\
      iter_._bz_offsetData(-offset1, dim1, -offset2, dim2);		\
      return r;								\
    }									\
									\
    void prettyPrint(BZ_STD_SCOPE(string) &str,				\
		     prettyPrintFormat& format) const			\
    {									\
      str += "name (stencil)";						\
      str += "(";							\
      iter_.prettyPrint(str, format);					\
      str += ")";							\
    }									\
									\
    template<typename T1, typename T2 = nilArraySection,		\
      class T3 = nilArraySection, typename T4 = nilArraySection,	\
      class T5 = nilArraySection, typename T6 = nilArraySection,	\
      class T7 = nilArraySection, typename T8 = nilArraySection,	\
      class T9 = nilArraySection, typename T10 = nilArraySection,	\
      class T11 = nilArraySection>					\
      class SliceInfo {							\
      public:								\
      typedef name ## _et<T_expr> T_slice;				\
      };								\
    									\
    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, \
      typename T7, typename T8, typename T9, typename T10, typename T11> \
      name ## _et							\
      operator()(T1 r1, T2 r2, T3 r3, T4 r4, T5 r5, T6 r6, T7 r7, T8 r8, T9 r9, T10 r10, T11 r11) const \
    {									\
      return name ## _et						\
	(iter_(_bz_makeRange(r1),					\
	       _bz_makeRange(r2),					\
	       _bz_makeRange(r3),					\
	       _bz_makeRange(r4),					\
	       _bz_makeRange(r5),					\
	       _bz_makeRange(r6),					\
	       _bz_makeRange(r7),					\
	       _bz_makeRange(r8),					\
	       _bz_makeRange(r9),					\
	       _bz_makeRange(r10),					\
	       _bz_makeRange(r11)),dim_);				\
    }									\
									\
  private:								\
    int dim_;								\
  };									\
 /* create ET from application to expression */				\
  template<typename T1>							\
  inline _bz_ArrayExpr<name ## _et<typename BZ_BLITZ_SCOPE(asExpr)<T1>::T_expr::T_range_result> >	\
  name(const BZ_BLITZ_SCOPE(ETBase)<T1>& d1, int dim)			\
  {									\
    TinyVector<int, BZ_BLITZ_SCOPE(asExpr)<T1>::T_expr::rank> minb(0), maxb(0); \
    minb[dim]=MINB; maxb[dim]=MAXB;					\
    return _bz_ArrayExpr<name ## _et<typename BZ_BLITZ_SCOPE(asExpr)<T1>::T_expr::T_range_result> >	\
      (BZ_BLITZ_SCOPE(asExpr)<T1>::getExpr(d1.unwrap())(_bz_shrinkDomain(d1.unwrap().domain(),minb, maxb)), dim); \
  }									\
  /* forward operations on arrays to main function */			\
  template<typename T, int N>						\
   inline _bz_ArrayExpr<name ## _et<_bz_typename BZ_BLITZ_SCOPE(asExpr)<Array<T,N> >::T_expr::T_range_result> > \
  name(const Array<T,N>& d1, int dim)					\
  { return name(d1.wrap(), dim); }					\
   template<typename T, int N>						\
   inline _bz_ArrayExpr<name ## _et<_bz_typename BZ_BLITZ_SCOPE(asExpr)<Array<T,N> >::T_expr::T_range_result> > \
   name(Array<T,N>& d1, int dim)						\
   { return name(d1.wrap(), dim); }


/* Defines a stencil ET difference operator that operates on a
   multicomponent array<P_numtype, N_rank> and returns an
   array<P_numtype::T_element, N_rank>. */

#define BZ_ET_STENCIL_MULTIDIFF(name, MINB, MAXB)			\
  template<typename P_expr>						\
  class name ## _et_multi : public _bz_StencilExpr<P_expr, _bz_typename multicomponent_traits<typename P_expr::T_numtype>::T_element> \
  {									\
  public:								\
    typedef _bz_typename multicomponent_traits<typename P_expr::T_numtype>::T_element T_result; \
    typedef _bz_StencilExpr<P_expr, T_result> T_base;		\
    typedef _bz_typename T_base::T_numtype T_numtype;			\
    typedef _bz_typename T_base::T_expr T_expr;				\
    typedef  name ## _et_multi<_bz_typename P_expr::T_range_result> T_range_result; \
									\
    using T_base::iter_;						\
    using T_base::rank;							\
  public:								\
    name ## _et_multi(const name ## _et_multi& a) :		\
      _bz_StencilExpr<P_expr, T_numtype>(a), comp_(a.comp_), dim_(a.dim_) \
      { }								\
									\
    name ## _et_multi(BZ_ETPARM(T_expr) a, int comp, int dim) :	\
      _bz_StencilExpr<P_expr, T_numtype>(a),			\
      comp_(comp), dim_(dim)						\
      { }								\
									\
    name ## _et_multi(_bz_typename T_expr::T_ctorArg1 a, int comp, int dim) : \
      _bz_StencilExpr<P_expr, T_numtype>(a),			\
      comp_(comp), dim_(dim)						\
      { }								\
									\
    T_numtype operator*() const						\
    { return name(iter_, comp_, dim_); }				\
    T_numtype operator()(_bz_typename _bz_IndexParameter<TinyVector<int, rank> >::type i) const \
    { iter_.moveTo(i); return name(iter_, comp_, dim_); }		\
									\
    T_range_result operator()(const RectDomain<rank>& d) const		\
    { return T_range_result(iter_(d), comp_, dim_); }			\
									\
    T_numtype operator[](int i) const					\
    { return name(iter_[i], comp_, dim_); }				\
									\
    T_numtype fastRead(sizeType i) const				\
    {/* this probably isn't very fast... */				\
      iter_._bz_offsetData(i);						\
      T_numtype r = name (iter_, comp_, dim_);				\
      iter_._bz_offsetData(-i);						\
      return r;								\
    }									\
									\
    T_numtype shift(int offset, int dim) const				\
    {									\
      iter_._bz_offsetData(offset, dim);				\
      T_numtype r = name (iter_);					\
      iter_._bz_offsetData(-offset, dim);				\
      return r;								\
    }									\
									\
    T_numtype shift(int offset1, int dim1, int offset2, int dim2) const	\
    {									\
      iter_._bz_offsetData(offset1, dim1, offset2, dim2);		\
      T_numtype r = name (iter_);					\
      iter_._bz_offsetData(-offset1, dim1, -offset2, dim2);		\
      return r;								\
    }									\
									\
    void prettyPrint(BZ_STD_SCOPE(string) &str,				\
		     prettyPrintFormat& format) const			\
    {									\
      str += "name (stencil)";						\
      str += "(";							\
      iter_.prettyPrint(str, format);					\
      str += ")";							\
    }									\
									\
    template<typename T1, typename T2 = nilArraySection,		\
      class T3 = nilArraySection, typename T4 = nilArraySection,	\
      class T5 = nilArraySection, typename T6 = nilArraySection,	\
      class T7 = nilArraySection, typename T8 = nilArraySection,	\
      class T9 = nilArraySection, typename T10 = nilArraySection,	\
      class T11 = nilArraySection>					\
      class SliceInfo {							\
      public:								\
      typedef name ## _et_multi<T_expr> T_slice;				\
      };								\
    									\
    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, \
      typename T7, typename T8, typename T9, typename T10, typename T11> \
      name ## _et_multi							\
      operator()(T1 r1, T2 r2, T3 r3, T4 r4, T5 r5, T6 r6, T7 r7, T8 r8, T9 r9, T10 r10, T11 r11) const \
    {									\
      return name ## _et_multi						\
	(iter_(_bz_makeRange(r1),					\
	       _bz_makeRange(r2),					\
	       _bz_makeRange(r3),					\
	       _bz_makeRange(r4),					\
	       _bz_makeRange(r5),					\
	       _bz_makeRange(r6),					\
	       _bz_makeRange(r7),					\
	       _bz_makeRange(r8),					\
	       _bz_makeRange(r9),					\
	       _bz_makeRange(r10),					\
	       _bz_makeRange(r11)),comp_, dim_);			\
    }									\
									\
  private:								\
    int comp_;								\
    int dim_;								\
  };									\
  /* create ET from application to expression */			\
  template<typename T1>							\
  inline _bz_ArrayExpr<name ## _et_multi<typename BZ_BLITZ_SCOPE(asExpr)<T1>::T_expr::T_range_result> >	\
  name(const BZ_BLITZ_SCOPE(ETBase)<T1>& d1, int comp, int dim)		\
  {									\
    TinyVector<int, BZ_BLITZ_SCOPE(asExpr)<T1>::T_expr::rank> minb(0), maxb(0);	\
    minb[dim]=MINB; maxb[dim]=MAXB;					\
    return _bz_ArrayExpr<name ## _et_multi<typename BZ_BLITZ_SCOPE(asExpr)<T1>::T_expr::T_range_result> > \
      (BZ_BLITZ_SCOPE(asExpr)<T1>::getExpr(d1.unwrap())(_bz_shrinkDomain(d1.unwrap().domain(),minb, maxb)), comp, dim); \
  }									\
  /* forward operations on arrays to main function */			\
  template<typename T, int N>						\
  inline _bz_ArrayExpr<name ## _et_multi<_bz_typename BZ_BLITZ_SCOPE(asExpr)<Array<T,N> >::T_expr::T_range_result> > \
  name(const Array<T,N>& d1, int comp, int dim)				\
  { return name(d1.wrap(), comp, dim); }				\
									\
  template<typename T, int N>						\
  inline _bz_ArrayExpr<name ## _et_multi<_bz_typename BZ_BLITZ_SCOPE(asExpr)<Array<T,N> >::T_expr::T_range_result> > \
  name(Array<T,N>& d1, int comp, int dim)				\
  { return name(d1.wrap(), comp, dim); }


/* Defines a stencil ET double-difference operator that operates on an
   array<P_numtype, N_rank> and returns a array<P_numtype,
   N_rank>. (The only significance of the "difference" aspect is that
   the operator is assumed to take two extra arguments which are the
   dimensions to do the differences in). */

#define BZ_ET_STENCIL_DIFF2(name, MINB1, MAXB1, MINB2, MAXB2)		\
 template<typename P_expr>						\
 class name ## _et : public _bz_StencilExpr<P_expr, _bz_typename P_expr::T_numtype> \
 {									\
 public:								\
   typedef _bz_StencilExpr<P_expr, _bz_typename P_expr::T_numtype> T_base;	\
   typedef _bz_typename T_base::T_numtype T_numtype;			\
   typedef _bz_typename T_base::T_expr T_expr;				\
   typedef  name ## _et<_bz_typename P_expr::T_range_result> T_range_result; \
   									\
   using T_base::iter_;							\
   using T_base::rank;							\
 public:								\
   name ## _et(const name ## _et& a) :					\
   _bz_StencilExpr<P_expr, T_numtype>(a),				\
     dim1_(a.dim1_), dim2_(a.dim2_)					\
     { }								\
   									\
   name ## _et(BZ_ETPARM(T_expr) a, int dim1, int dim2) :		\
   _bz_StencilExpr<P_expr, T_numtype>(a),				\
     dim1_(dim1), dim2_(dim2)						\
   { }									\
   									\
   name ## _et(_bz_typename T_expr::T_ctorArg1 a,			\
	       int dim1, int dim2) :					\
   _bz_StencilExpr<P_expr, T_numtype>(a),				\
     dim1_(dim1), dim2_(dim2)						\
   { }									\
   									\
   T_numtype operator*() const						\
   { return name(iter_, dim1_, dim2_); }				\
   T_numtype operator()(_bz_typename _bz_IndexParameter<TinyVector<int, rank> >::type i) const \
   { iter_.moveTo(i); return name(iter_, dim1_, dim2_); }		\
									\
   T_range_result operator()(const RectDomain<rank>& d) const		\
   { return T_range_result(iter_(d), dim1_, dim2_); }			\
   									\
   T_numtype operator[](int i) const					\
   { return name(iter_[i], dim1_, dim2_); }				\
									\
   T_numtype fastRead(sizeType i) const					\
   {/* this probably isn't very fast... */				\
     iter_._bz_offsetData(i);						\
     T_numtype r = name (iter_, dim1_, dim2_);				\
     iter_._bz_offsetData(-i);						\
     return r;								\
   }									\
									\
    T_numtype shift(int offset, int dim) const				\
    {									\
      iter_._bz_offsetData(offset, dim);				\
      T_numtype r = name (iter_);					\
      iter_._bz_offsetData(-offset, dim);				\
      return r;								\
    }									\
									\
    T_numtype shift(int offset1, int dim1, int offset2, int dim2) const	\
    {									\
      iter_._bz_offsetData(offset1, dim1, offset2, dim2);		\
      T_numtype r = name (iter_);					\
      iter_._bz_offsetData(-offset1, dim1, -offset2, dim2);		\
      return r;								\
    }									\
									\
    void prettyPrint(BZ_STD_SCOPE(string) &str,				\
		     prettyPrintFormat& format) const			\
    {									\
      str += "name (stencil)";						\
      str += "(";							\
      iter_.prettyPrint(str, format);					\
      str += ")";							\
    }									\
									\
    template<typename T1, typename T2 = nilArraySection,		\
      class T3 = nilArraySection, typename T4 = nilArraySection,	\
      class T5 = nilArraySection, typename T6 = nilArraySection,	\
      class T7 = nilArraySection, typename T8 = nilArraySection,	\
      class T9 = nilArraySection, typename T10 = nilArraySection,	\
      class T11 = nilArraySection>					\
      class SliceInfo {							\
      public:								\
      typedef name ## _et<T_expr> T_slice;				\
      };								\
    									\
    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, \
      typename T7, typename T8, typename T9, typename T10, typename T11> \
      name ## _et							\
      operator()(T1 r1, T2 r2, T3 r3, T4 r4, T5 r5, T6 r6, T7 r7, T8 r8, T9 r9, T10 r10, T11 r11) const \
    {									\
      return name ## _et						\
	(iter_(_bz_makeRange(r1),					\
	       _bz_makeRange(r2),					\
	       _bz_makeRange(r3),					\
	       _bz_makeRange(r4),					\
	       _bz_makeRange(r5),					\
	       _bz_makeRange(r6),					\
	       _bz_makeRange(r7),					\
	       _bz_makeRange(r8),					\
	       _bz_makeRange(r9),					\
	       _bz_makeRange(r10),					\
	       _bz_makeRange(r11)), dim1_, dim2_);			\
    }									\
   									\
private:								\
   int dim1_, dim2_;							\
 };									\
 									\
 /* create ET from application to expression */				\
template<typename T1>							\
 inline _bz_ArrayExpr<name ## _et<typename BZ_BLITZ_SCOPE(asExpr)<T1>::T_expr::T_range_result> >	\
 name(const BZ_BLITZ_SCOPE(ETBase)<T1>& d1, int dim1, int dim2)		\
 {									\
   TinyVector<int, BZ_BLITZ_SCOPE(asExpr)<T1>::T_expr::rank> minb(0), maxb(0);	\
   minb[dim1]=MINB1; maxb[dim1]=MAXB1;					\
   minb[dim2]=MINB2; maxb[dim2]=MAXB2;					\
   return _bz_ArrayExpr<name ## _et<typename BZ_BLITZ_SCOPE(asExpr)<T1>::T_expr::T_range_result> >	\
     (BZ_BLITZ_SCOPE(asExpr)<T1>::getExpr(d1.unwrap())(_bz_shrinkDomain(d1.unwrap().domain(),minb, maxb)), dim1, dim2); \
 }									\
  /* forward operations on arrays to main function */			\
  template<typename T, int N>						\
  inline _bz_ArrayExpr<name ## _et<_bz_typename BZ_BLITZ_SCOPE(asExpr)<Array<T,N> >::T_expr::T_range_result> > \
  name(const Array<T,N>& d1, int dim1, int dim2)			\
  { return name(d1.wrap(), dim1, dim2); }				\
									\
  template<typename T, int N>						\
  inline _bz_ArrayExpr<name ## _et<_bz_typename BZ_BLITZ_SCOPE(asExpr)<Array<T,N> >::T_expr::T_range_result> > \
  name(Array<T,N>& d1, int dim1, int dim2)				\
  { return name(d1.wrap(), dim1, dim2); }

#define bzCC(...) __VA_ARGS__


/* Definitions of ET stencil operators follows.

   Note: You can't pass templates with >1 parameter as macro
   parameters because cpp doesn't recognize that the comma is balanced
   between the angle brackets and interprets them as multiple
   arguments, i.e., the following alternative declaration of grad2D
   will not work:

   BZ_ET_STENCIL(grad2D, TinyVector<P_numtype, 2>, 
     TinyVector<typename T1::T_numtype, 2>, shape(-1,1), shape(1,1))

   instead, you have to use the above bzCC ("ConCatenate") macro to
   protect the things containing commas. The following would work:

   BZ_ET_STENCIL(grad2D, bzCC(TinyVector<P_numtype, 2>), 
     bzCC(TinyVector<typename T1::T_numtype, 2>), shape(-1,-1), shape(1,1))

*/


BZ_ET_STENCIL_DIFF(central12, -1, 1)
BZ_ET_STENCIL_DIFF(central22, -1, 1)
BZ_ET_STENCIL_DIFF(central32, -2, 2)
BZ_ET_STENCIL_DIFF(central42, -2, 2)
BZ_ET_STENCIL_DIFF(central14, -2, 2)
BZ_ET_STENCIL_DIFF(central24, -2, 2)
BZ_ET_STENCIL_DIFF(central34, -2, 2)
BZ_ET_STENCIL_DIFF(central44, -2, 2)
BZ_ET_STENCIL_DIFF(central12n, -1, 1)
BZ_ET_STENCIL_DIFF(central22n, -1, 1)
BZ_ET_STENCIL_DIFF(central32n, -2, 2)
BZ_ET_STENCIL_DIFF(central42n, -2, 2)
BZ_ET_STENCIL_DIFF(central14n, -2, 2)
BZ_ET_STENCIL_DIFF(central24n, -2, 2)
BZ_ET_STENCIL_DIFF(central34n, -2, 2)
BZ_ET_STENCIL_DIFF(central44n, -2, 2)

BZ_ET_STENCIL_DIFF(backward11, -1, 0)
BZ_ET_STENCIL_DIFF(backward21, -2, 0)
BZ_ET_STENCIL_DIFF(backward31, -3, 0)
BZ_ET_STENCIL_DIFF(backward41, -4, 0)
BZ_ET_STENCIL_DIFF(backward12, -2, 0)
BZ_ET_STENCIL_DIFF(backward22, -3, 0)
BZ_ET_STENCIL_DIFF(backward32, -4, 0)
BZ_ET_STENCIL_DIFF(backward42, -5, 0)
BZ_ET_STENCIL_DIFF(backward11n, -1, 0)
BZ_ET_STENCIL_DIFF(backward21n, -2, 0)
BZ_ET_STENCIL_DIFF(backward31n, -3, 0)
BZ_ET_STENCIL_DIFF(backward41n, -4, 0)
BZ_ET_STENCIL_DIFF(backward12n, -2, 0)
BZ_ET_STENCIL_DIFF(backward22n, -3, 0)
BZ_ET_STENCIL_DIFF(backward32n, -4, 0)
BZ_ET_STENCIL_DIFF(backward42n, -5, 0)

BZ_ET_STENCIL_DIFF(forward11, 0, 1)
BZ_ET_STENCIL_DIFF(forward21, 0, 2)
BZ_ET_STENCIL_DIFF(forward31, 0, 3)
BZ_ET_STENCIL_DIFF(forward41, 0, 4)
BZ_ET_STENCIL_DIFF(forward12, 0, 2)
BZ_ET_STENCIL_DIFF(forward22, 0, 3)
BZ_ET_STENCIL_DIFF(forward32, 0, 4)
BZ_ET_STENCIL_DIFF(forward42, 0, 5)
BZ_ET_STENCIL_DIFF(forward11n, 0, 1)
BZ_ET_STENCIL_DIFF(forward21n, 0, 2)
BZ_ET_STENCIL_DIFF(forward31n, 0, 3)
BZ_ET_STENCIL_DIFF(forward41n, 0, 4)
BZ_ET_STENCIL_DIFF(forward12n, 0, 2)
BZ_ET_STENCIL_DIFF(forward22n, 0, 3)
BZ_ET_STENCIL_DIFF(forward32n, 0, 4)
BZ_ET_STENCIL_DIFF(forward42n, 0, 5)

BZ_ET_STENCIL_MULTIDIFF(central12, -1, 1)
BZ_ET_STENCIL_MULTIDIFF(central22, -1, 1)
BZ_ET_STENCIL_MULTIDIFF(central32, -2, 2)
BZ_ET_STENCIL_MULTIDIFF(central42, -2, 2)
BZ_ET_STENCIL_MULTIDIFF(central14, -2, 2)
BZ_ET_STENCIL_MULTIDIFF(central24, -2, 2)
BZ_ET_STENCIL_MULTIDIFF(central34, -2, 2)
BZ_ET_STENCIL_MULTIDIFF(central44, -2, 2)
BZ_ET_STENCIL_MULTIDIFF(central12n, -1, 1)
BZ_ET_STENCIL_MULTIDIFF(central22n, -1, 1)
BZ_ET_STENCIL_MULTIDIFF(central32n, -2, 2)
BZ_ET_STENCIL_MULTIDIFF(central42n, -2, 2)
BZ_ET_STENCIL_MULTIDIFF(central14n, -2, 2)
BZ_ET_STENCIL_MULTIDIFF(central24n, -2, 2)
BZ_ET_STENCIL_MULTIDIFF(central34n, -2, 2)
BZ_ET_STENCIL_MULTIDIFF(central44n, -2, 2)

BZ_ET_STENCIL_MULTIDIFF(backward11, -1, 0)
BZ_ET_STENCIL_MULTIDIFF(backward21, -2, 0)
BZ_ET_STENCIL_MULTIDIFF(backward31, -3, 0)
BZ_ET_STENCIL_MULTIDIFF(backward41, -4, 0)
BZ_ET_STENCIL_MULTIDIFF(backward12, -2, 0)
BZ_ET_STENCIL_MULTIDIFF(backward22, -3, 0)
BZ_ET_STENCIL_MULTIDIFF(backward32, -4, 0)
BZ_ET_STENCIL_MULTIDIFF(backward42, -5, 0)
BZ_ET_STENCIL_MULTIDIFF(backward11n, -1, 0)
BZ_ET_STENCIL_MULTIDIFF(backward21n, -2, 0)
BZ_ET_STENCIL_MULTIDIFF(backward31n, -3, 0)
BZ_ET_STENCIL_MULTIDIFF(backward41n, -4, 0)
BZ_ET_STENCIL_MULTIDIFF(backward12n, -2, 0)
BZ_ET_STENCIL_MULTIDIFF(backward22n, -3, 0)
BZ_ET_STENCIL_MULTIDIFF(backward32n, -4, 0)
BZ_ET_STENCIL_MULTIDIFF(backward42n, -5, 0)

BZ_ET_STENCIL_MULTIDIFF(forward11, 0, 1)
BZ_ET_STENCIL_MULTIDIFF(forward21, 0, 2)
BZ_ET_STENCIL_MULTIDIFF(forward31, 0, 3)
BZ_ET_STENCIL_MULTIDIFF(forward41, 0, 4)
BZ_ET_STENCIL_MULTIDIFF(forward12, 0, 2)
BZ_ET_STENCIL_MULTIDIFF(forward22, 0, 3)
BZ_ET_STENCIL_MULTIDIFF(forward32, 0, 4)
BZ_ET_STENCIL_MULTIDIFF(forward42, 0, 5)
BZ_ET_STENCIL_MULTIDIFF(forward11n, 0, 1)
BZ_ET_STENCIL_MULTIDIFF(forward21n, 0, 2)
BZ_ET_STENCIL_MULTIDIFF(forward31n, 0, 3)
BZ_ET_STENCIL_MULTIDIFF(forward41n, 0, 4)
BZ_ET_STENCIL_MULTIDIFF(forward12n, 0, 2)
BZ_ET_STENCIL_MULTIDIFF(forward22n, 0, 3)
BZ_ET_STENCIL_MULTIDIFF(forward32n, 0, 4)
BZ_ET_STENCIL_MULTIDIFF(forward42n, 0, 5)

BZ_ET_STENCIL(Laplacian2D, T, typename BZ_BLITZ_SCOPE(asExpr)<T1>::T_expr::T_numtype, shape(-1,-1), shape(1,1))
BZ_ET_STENCIL(Laplacian3D, T, typename BZ_BLITZ_SCOPE(asExpr)<T1>::T_expr::T_numtype, shape(-1,-1,-1), shape(1,1,1))
BZ_ET_STENCIL(Laplacian2D4, T, typename BZ_BLITZ_SCOPE(asExpr)<T1>::T_expr::T_numtype, shape(-2,-2), shape(2,2))
BZ_ET_STENCIL(Laplacian2D4n, T, typename BZ_BLITZ_SCOPE(asExpr)<T1>::T_expr::T_numtype, shape(-2,-2), shape(2,2))
BZ_ET_STENCIL(Laplacian3D4, T, typename BZ_BLITZ_SCOPE(asExpr)<T1>::T_expr::T_numtype, shape(-2,-2,-2), shape(2,2,2))
BZ_ET_STENCIL(Laplacian3D4n, T, typename BZ_BLITZ_SCOPE(asExpr)<T1>::T_expr::T_numtype, shape(-2,-2,-2), shape(2,2,2))

BZ_ET_STENCILV(grad2D, 2, shape(-1,-1), shape(1,1))
BZ_ET_STENCILV(grad2D4, 2, shape(-2,-2), shape(2,2))
BZ_ET_STENCILV(grad3D, 3, shape(-1,-1,-1), shape(1,1,1))
BZ_ET_STENCILV(grad3D4, 3, shape(-2,-2,-2), shape(2,2,2))
BZ_ET_STENCILV(grad2Dn, 2, shape(-1,-1), shape(1,1))
BZ_ET_STENCILV(grad2D4n, 2, shape(-2,-2), shape(2,2))
BZ_ET_STENCILV(grad3Dn, 3, shape(-1,-1,-1), shape(1,1,1))
BZ_ET_STENCILV(grad3D4n, 3, shape(-2,-2,-2), shape(2,2,2))
BZ_ET_STENCILV(gradSqr2D, 2, shape(-1,-1), shape(1,1))
BZ_ET_STENCILV(gradSqr2D4, 2, shape(-2,-2), shape(2,2))
BZ_ET_STENCILV(gradSqr3D, 3, shape(-1,-1,-1), shape(1,1,1))
BZ_ET_STENCILV(gradSqr3D4, 3, shape(-2,-2,-2), shape(2,2,2))
BZ_ET_STENCILV(gradSqr2Dn, 2, shape(-1,-1), shape(1,1))
BZ_ET_STENCILV(gradSqr2D4n, 2, shape(-2,-2), shape(2,2))
BZ_ET_STENCILV(gradSqr3Dn, 3, shape(-1,-1,-1), shape(1,1,1))
BZ_ET_STENCILV(gradSqr3D4n, 3, shape(-2,-2,-2), shape(2,2,2))

BZ_ET_STENCILM(Jacobian3D, 3, shape(-1,-1,-1), shape(1,1,1))
BZ_ET_STENCILM(Jacobian3Dn, 3, shape(-1,-1,-1), shape(1,1,1))
BZ_ET_STENCILM(Jacobian3D4, 3, shape(-2,-2,-2), shape(2,2,2))
BZ_ET_STENCILM(Jacobian3D4n, 3, shape(-2,-2,-2), shape(2,2,2))

BZ_ET_STENCIL(curl3D, T, typename BZ_BLITZ_SCOPE(asExpr)<T1>::T_expr::T_numtype, shape(-1,-1,-1), shape(1,1,1))
BZ_ET_STENCIL(curl3Dn, T, typename BZ_BLITZ_SCOPE(asExpr)<T1>::T_expr::T_numtype, shape(-1,-1,-1), shape(1,1,1))
BZ_ET_STENCIL(curl3D4, T, typename BZ_BLITZ_SCOPE(asExpr)<T1>::T_expr::T_numtype, shape(-2,-2,-2), shape(2,2,2))
BZ_ET_STENCIL(curl3D4n, T, typename BZ_BLITZ_SCOPE(asExpr)<T1>::T_expr::T_numtype, shape(-2,-2,-2), shape(2,2,2))
BZ_ET_STENCIL(curl2D, T, typename BZ_BLITZ_SCOPE(asExpr)<T1>::T_expr::T_numtype, shape(-1,-1), shape(1,1))
BZ_ET_STENCIL(curl2Dn, T, typename BZ_BLITZ_SCOPE(asExpr)<T1>::T_expr::T_numtype, shape(-1,-1), shape(1,1))
BZ_ET_STENCIL(curl2D4, T, typename BZ_BLITZ_SCOPE(asExpr)<T1>::T_expr::T_numtype, shape(-2,-2), shape(2,2))
BZ_ET_STENCIL(curl2D4n, T, typename BZ_BLITZ_SCOPE(asExpr)<T1>::T_expr::T_numtype, shape(-2,-2), shape(2,2))

BZ_ET_STENCIL_SCA(div2D, shape(-1,-1), shape(1,1))
BZ_ET_STENCIL_SCA(div2Dn, shape(-1,-1), shape(1,1))
BZ_ET_STENCIL_SCA(div2D4, shape(-2,-2), shape(2,2))
BZ_ET_STENCIL_SCA(div2D4n, shape(-2,-2), shape(2,2))
BZ_ET_STENCIL_SCA(div3D, shape(-1,-1,-1), shape(1,1,1))
BZ_ET_STENCIL_SCA(div3Dn, shape(-1,-1,-1), shape(1,1,1))
BZ_ET_STENCIL_SCA(div3D4, shape(-2,-2,-2), shape(2,2,2))


BZ_ET_STENCIL2(div, double , bzCC(BZ_PROMOTE(typename BZ_BLITZ_SCOPE(asExpr)<T1>::T_expr::T_numtype, typename BZ_BLITZ_SCOPE(asExpr)<T2>::T_expr::T_numtype)), shape(-1,-1), shape(1,1))
BZ_ET_STENCIL2(divn, double , bzCC(BZ_PROMOTE(typename BZ_BLITZ_SCOPE(asExpr)<T1>::T_expr::T_numtype, typename BZ_BLITZ_SCOPE(asExpr)<T2>::T_expr::T_numtype)), shape(-1,-1), shape(1,1))
BZ_ET_STENCIL2(div4, double , bzCC(BZ_PROMOTE(typename BZ_BLITZ_SCOPE(asExpr)<T1>::T_expr::T_numtype, typename BZ_BLITZ_SCOPE(asExpr)<T2>::T_expr::T_numtype)), shape(-2,-2), shape(2,2))
BZ_ET_STENCIL2(div4n, double , bzCC(BZ_PROMOTE(typename BZ_BLITZ_SCOPE(asExpr)<T1>::T_expr::T_numtype, typename BZ_BLITZ_SCOPE(asExpr)<T2>::T_expr::T_numtype)), shape(-2,-2), shape(2,2))

BZ_ET_STENCIL_DIFF2(mixed22, -1, 1, -1, 1)
BZ_ET_STENCIL_DIFF2(mixed22n, -1, 1, -1, 1)
BZ_ET_STENCIL_DIFF2(mixed24, -2, 2, -2, 2)
BZ_ET_STENCIL_DIFF2(mixed24n, -2, 2, -2, 2)
// no multicomponent versions of these in stencilops.h

BZ_NAMESPACE_END

#endif // BZ_ARRAY_STENCIL_ET_H
