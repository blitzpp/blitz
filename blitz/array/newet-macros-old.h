/***************************************************************************
 * blitz/array/newet-macros-old.h  Macros for new e.t. implementation
 *
 * Copyright (C) 1997-2003 Todd Veldhuizen <tveldhui@oonumerics.org>
 *
 * WARNING: This file is the old version of the newet-macro.h that is
 *          still kept for the compilers that do not have the
 *          template-template parameter capability.
 *
 *          NEVER EVER ATTEMPT TO INCLUDE THIS FILE DIRECTLY.
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

//  Guard as much as possible against user inclusion.

#if !defined(BZ_NO_TEMPLATES_AS_TEMPLATE_ARGUMENTS) || !defined(BZ_NEWET_MACROS_H)
#error <blitz/array/newet-macros-old.h> must be included via newet-macros.h
#endif

/*
 * Unary functions and operators
 */

#define BZ_DECLARE_ARRAY_ET_UNARY(name, functor)                          \
template<class T1>                                                        \
_bz_inline_et                                                             \
_bz_ArrayExpr<_bz_ArrayExprUnaryOp<_bz_typename asExpr<T1>::T_expr,       \
    functor<_bz_typename asExpr<T1>::T_expr::T_numtype> > >               \
name(const ETBase<T1>& d1)                                                \
{                                                                         \
    return _bz_ArrayExpr<_bz_ArrayExprUnaryOp<                            \
        _bz_typename asExpr<T1>::T_expr,                                  \
        functor<_bz_typename asExpr<T1>::T_expr::T_numtype> > >           \
        (static_cast<const T1&>(d1));                                     \
}

/*
 * Array expression templates: the macro BZ_DECLARE_ARRAY_ET_BINARY(X,Y)
 * declares a function or operator which takes two operands.
 * X is the function name (or operator), and Y is the functor object
 * which implements the operation.
 */

#define BZ_DECLARE_ARRAY_ET_BINARY(name, applic)                          \
                                                                          \
template<class T_numtype1, int N_rank1, class T_other>                    \
_bz_inline_et                                                             \
_bz_ArrayExpr<_bz_ArrayExprOp<FastArrayIterator<T_numtype1, N_rank1>,     \
    _bz_typename asExpr<T_other>::T_expr, applic<T_numtype1,              \
    _bz_typename asExpr<T_other>::T_expr::T_numtype> > >                  \
name(const Array<T_numtype1,N_rank1>& d1, const T_other& d2)              \
{                                                                         \
    return _bz_ArrayExpr<_bz_ArrayExprOp<FastArrayIterator<T_numtype1,    \
        N_rank1>, _bz_typename asExpr<T_other>::T_expr,                   \
        applic<T_numtype1,                                                \
        _bz_typename asExpr<T_other>::T_expr::T_numtype> > >              \
        (d1.beginFast(),d2);                                              \
}                                                                         \
                                                                          \
template<class T_expr1, class T_other>                                    \
_bz_inline_et                                                             \
_bz_ArrayExpr<_bz_ArrayExprOp<_bz_ArrayExpr<T_expr1>,                     \
    _bz_typename asExpr<T_other>::T_expr,                                 \
    applic<_bz_typename T_expr1::T_numtype,                               \
    _bz_typename asExpr<T_other>::T_expr::T_numtype> > >                  \
name(const _bz_ArrayExpr<T_expr1>& d1, const T_other& d2)                 \
{                                                                         \
    return _bz_ArrayExpr<_bz_ArrayExprOp<_bz_ArrayExpr<T_expr1>,          \
        _bz_typename asExpr<T_other>::T_expr,                             \
        applic<_bz_typename T_expr1::T_numtype,                           \
        _bz_typename asExpr<T_other>::T_expr::T_numtype> > >(d1,d2);      \
}                                                                         \
                                                                          \
template<class T1, class T2>                                              \
_bz_inline_et                                                             \
_bz_ArrayExpr<_bz_ArrayExprOp<_bz_typename asExpr<T1>::T_expr,            \
    _bz_typename asExpr<T2>::T_expr,                                      \
    applic<_bz_typename asExpr<T1>::T_expr::T_numtype,                    \
    _bz_typename asExpr<T2>::T_expr::T_numtype> > >                       \
name(const ETBase<T1>& d1, const T2& d2)                                  \
{                                                                         \
    return _bz_ArrayExpr<_bz_ArrayExprOp<_bz_typename asExpr<T1>::T_expr, \
        _bz_typename asExpr<T2>::T_expr,                                  \
        applic<_bz_typename asExpr<T1>::T_expr::T_numtype,                \
        _bz_typename asExpr<T2>::T_expr::T_numtype> > >                   \
        (static_cast<const T1&>(d1), d2);                                 \
}                                                                         \
                                                                          \
template<class T1, class T2>                                              \
_bz_inline_et                                                             \
_bz_ArrayExpr<_bz_ArrayExprOp<_bz_typename asExpr<T1>::T_expr,            \
    _bz_typename asExpr<T2>::T_expr,                                      \
    applic<_bz_typename asExpr<T1>::T_expr::T_numtype,                    \
    _bz_typename asExpr<T2>::T_expr::T_numtype> > >                       \
name(const T1& d1, const ETBase<T2>& d2)                                  \
{                                                                         \
    return _bz_ArrayExpr<_bz_ArrayExprOp<_bz_typename asExpr<T1>::T_expr, \
        _bz_typename asExpr<T2>::T_expr,                                  \
        applic<_bz_typename asExpr<T1>::T_expr::T_numtype,                \
        _bz_typename asExpr<T2>::T_expr::T_numtype> > >                   \
        (d1, static_cast<const T2&>(d2));                                 \
}                                                                         \
                                                                          \
template<int N1, class T_other>                                           \
_bz_inline_et                                                             \
_bz_ArrayExpr<_bz_ArrayExprOp<IndexPlaceholder<N1>,                       \
    _bz_typename asExpr<T_other>::T_expr,                                 \
    applic<int, _bz_typename asExpr<T_other>::T_expr::T_numtype> > >      \
name(IndexPlaceholder<N1> d1, const T_other& d2)                          \
{                                                                         \
    return _bz_ArrayExpr<_bz_ArrayExprOp<IndexPlaceholder<N1>,            \
        _bz_typename asExpr<T_other>::T_expr,                             \
        applic<int, _bz_typename asExpr<T_other>::T_expr::T_numtype> > >  \
        (d1,d2);                                                          \
}

/*
 * User-defined expression template routines
 */

#define BZ_DECLARE_FUNCTION(name)                                         \
  template<class T_numtype1>                                              \
  struct name ## _impl {                                                  \
    typedef T_numtype1 T_numtype;                                         \
                                                                          \
    static inline T_numtype apply(T_numtype1 x)                           \
    { return name(x); }                                                   \
                                                                          \
    template<class T1>                                                    \
    static void prettyPrint(string& str,                                  \
        prettyPrintFormat& format, const T1& a)                           \
    {                                                                     \
        str += #name;                                                     \
        str += "(";                                                       \
        a.prettyPrint(str,format);                                        \
        str += ")";                                                       \
    }                                                                     \
  };                                                                      \
                                                                          \
  BZ_DECLARE_ARRAY_ET_UNARY(name, name ## _impl)

#define BZ_DECLARE_FUNCTION_RET(name, return_type)                        \
  template<class T_numtype1>                                              \
  struct name ## _impl {                                                  \
    typedef return_type T_numtype;                                        \
                                                                          \
    static inline T_numtype apply(T_numtype1 x)                           \
    { return name(x); }                                                   \
                                                                          \
    template<class T1>                                                    \
    static void prettyPrint(string& str,                                  \
        prettyPrintFormat& format, const T1& a)                           \
    {                                                                     \
        str += #name;                                                     \
        str += "(";                                                       \
        a.prettyPrint(str,format);                                        \
        str += ")";                                                       \
    }                                                                     \
  };                                                                      \
                                                                          \
  BZ_DECLARE_ARRAY_ET_UNARY(name, name ## _impl)


#define BZ_DECLARE_FUNCTION2(name)                                        \
  template<class T_numtype1, class T_numtype2>                            \
  struct name ## _impl {                                                  \
    typedef BZ_PROMOTE(T_numtype1, T_numtype2) T_numtype;                 \
                                                                          \
    static inline T_numtype apply(T_numtype1 x, T_numtype2 y)             \
    { return name(x,y); }                                                 \
                                                                          \
    template<class T1, class T2>                                          \
    static void prettyPrint(string& str,                                  \
        prettyPrintFormat& format, const T1& a, const T2& b)              \
    {                                                                     \
        str += #name;                                                     \
        str += "(";                                                       \
        a.prettyPrint(str,format);                                        \
        str += ",";                                                       \
        b.prettyPrint(str,format);                                        \
        str += ")";                                                       \
    }                                                                     \
  };                                                                      \
                                                                          \
  BZ_DECLARE_ARRAY_ET_BINARY(name, name ## _impl)

#define BZ_DECLARE_FUNCTION2_RET(name, return_type)                       \
  template<class T_numtype1, class T_numtype2>                            \
  struct name ## _impl {                                                  \
    typedef return_type T_numtype;                                        \
                                                                          \
    static inline T_numtype apply(T_numtype1 x, T_numtype2 y)             \
    { return name(x,y); }                                                 \
                                                                          \
    template<class T1, class T2>                                          \
    static void prettyPrint(string& str,                                  \
        prettyPrintFormat& format, const T1& a, const T2& b)              \
    {                                                                     \
        str += #name;                                                     \
        str += "(";                                                       \
        a.prettyPrint(str,format);                                        \
        str += ",";                                                       \
        b.prettyPrint(str,format);                                        \
        str += ")";                                                       \
    }                                                                     \
  };                                                                      \
                                                                          \
  BZ_DECLARE_ARRAY_ET_BINARY(name, name ## _impl)
