/***************************************************************************
 * blitz/array/newet-macros.h  Macros for new e.t. implementation
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
#ifndef BZ_NEWET_MACROS_H
#define BZ_NEWET_MACROS_H

#include <blitz/array/asexpr.h>

BZ_NAMESPACE(blitz)

/*
 * Unary functions and operators
 */

#define BZ_DECLARE_ARRAY_ET_UNARY(name,functor)                           \
template <typename T1>                                                    \
_bz_inline_et                                                             \
typename BzUnaryExprResult<functor,T1>::T_result                          \
name(const ETBase<T1>& d1)                                                \
{                                                                         \
    typedef typename BzUnaryExprResult<functor,T1>::T_result result;      \
    return result(static_cast<const T1&>(d1));                            \
}

/*
 * Array expression templates: the macro BZ_DECLARE_ARRAY_ET_BINARY(X,Y)
 * declares a function or operator which takes two operands.
 * X is the function name (or operator), and Y is the functor object
 * which implements the operation.
 */

#define BZ_DECLARE_ARRAY_ET_BINARY(name, applic)                                 \
                                                                                 \
template <typename T_numtype1,int N_rank1,typename T_other>                      \
_bz_inline_et                                                                    \
typename BzBinaryExprResult<applic,Array<T_numtype1,N_rank1>,T_other>::T_result  \
name (const Array<T_numtype1,N_rank1>& d1, const T_other& d2)                    \
{                                                                                \
    typedef typename BzBinaryExprResult<applic,                                  \
                                  Array<T_numtype1,N_rank1>,                     \
                                  T_other>::T_result         result;             \
    return result(d1.beginFast(),d2);                                            \
}                                                                                \
                                                                                 \
template <typename T_expr1,typename T_other>                                     \
_bz_inline_et                                                                    \
typename BzBinaryExprResult<applic,_bz_ArrayExpr<T_expr1>,T_other>::T_result     \
name(const _bz_ArrayExpr<T_expr1>& d1, const T_other& d2)                        \
{                                                                                \
    typedef typename BzBinaryExprResult<applic,                                  \
                                  _bz_ArrayExpr<T_expr1>,                        \
                                  T_other>::T_result         result;             \
    return result(d1,d2);                                                        \
}                                                                                \
                                                                                 \
template <typename T1,typename T2>                                               \
_bz_inline_et                                                                    \
typename BzBinaryExprResult<applic,ETBase<T1>,T2>::T_result                      \
name(const ETBase<T1>& d1, const T2& d2)                                         \
{                                                                                \
    typedef typename BzBinaryExprResult<applic,ETBase<T1>,T2>::T_result result;  \
    return result(static_cast<const T1&>(d1),d2);                                \
}                                                                                \
                                                                                 \
template <typename T1,typename T2>                                               \
_bz_inline_et                                                                    \
typename BzBinaryExprResult<applic,T1,T2>::T_result                              \
name(const T1& d1,const ETBase<T2>& d2)                                          \
{                                                                                \
    typedef typename BzBinaryExprResult<applic,T1,T2>::T_result result;          \
    return result(d1,static_cast<const T2&>(d2));                                \
}                                                                                \
                                                                                 \
template <int N1,typename T_other>                                               \
_bz_inline_et                                                                    \
typename BzBinaryExprResult<applic,IndexPlaceholder<N1>,T_other>::T_result       \
name(IndexPlaceholder<N1> d1, const T_other& d2)                                 \
{                                                                                \
    typedef typename BzBinaryExprResult<applic,                                  \
                                  IndexPlaceholder<N1>,                          \
                                  T_other>::T_result    result;                  \
    return result(d1,d2);                                                        \
}

/*
 * User-defined expression template routines
 */

#define BZ_DECLARE_FUNCTION(name)                                                    \
    template <typename P_numtype>                                                    \
    struct name ## _impl {                                                           \
        typedef P_numtype T_numtype;                                                 \
                                                                                     \
        static inline T_numtype apply(P_numtype x) { return name(x); }               \
                                                                                     \
        template <typename T>                                                        \
        static void prettyPrint(string& str,prettyPrintFormat& format,const T& a) {  \
            str += #name;                                                            \
            str += "(";                                                              \
            a.prettyPrint(str,format);                                               \
            str += ")";                                                              \
        }                                                                            \
    };                                                                               \
                                                                                     \
    BZ_DECLARE_ARRAY_ET_UNARY(name,name ## _impl)

#define BZ_DECLARE_FUNCTION_RET(name,return_type)                                    \
    template <typename P_numtype>                                                    \
    struct name ## _impl {                                                           \
        typedef return_type T_numtype;                                               \
                                                                                     \
        static inline T_numtype apply(P_numtype x) { return name(x); }               \
                                                                                     \
        template <typename T1>                                                       \
        static void prettyPrint(string& str,prettyPrintFormat& format,const T1& a) { \
            str += #name;                                                            \
            str += "(";                                                              \
            a.prettyPrint(str,format);                                               \
            str += ")";                                                              \
        }                                                                            \
    };                                                                               \
                                                                                     \
  BZ_DECLARE_ARRAY_ET_UNARY(name,name ## _impl)

#define BZ_DECLARE_FUNCTION2(name)                                                               \
    template <typename P_numtype1,typename P_numtype2>                                           \
    struct name ## _impl {                                                                       \
        typedef BZ_PROMOTE(P_numtype1,P_numtype2) T_numtype;                                     \
                                                                                                 \
        static inline T_numtype                                                                  \
        apply(P_numtype1 x,P_numtype2 y) {                                                       \
            return static_cast<T_numtype>(name(x,y));                                            \
        }                                                                                        \
                                                                                                 \
        template <typename T1,typename T2>                                                       \
        static void prettyPrint(string& str,prettyPrintFormat& format,const T1& a,const T2& b) { \
            str += #name;                                                                        \
            str += "(";                                                                          \
            a.prettyPrint(str,format);                                                           \
            str += ",";                                                                          \
            b.prettyPrint(str,format);                                                           \
            str += ")";                                                                          \
        }                                                                                        \
    };                                                                                           \
                                                                                                 \
    BZ_DECLARE_ARRAY_ET_BINARY(name, name ## _impl)

#define BZ_DECLARE_FUNCTION2_RET(name, return_type)                                              \
    template <typename P_numtype1,typename P_numtype2>                                           \
    struct name ## _impl {                                                                       \
        typedef return_type T_numtype;                                                           \
                                                                                                 \
        static inline T_numtype apply(P_numtype1 x,P_numtype2 y) {                               \
            return name(x,y);                                                                    \
        }                                                                                        \
                                                                                                 \
        template <typename T1,typename T2>                                                       \
        static void prettyPrint(string& str,prettyPrintFormat& format,const T1& a,const T2& b) { \
            str += #name;                                                                        \
            str += "(";                                                                          \
            a.prettyPrint(str,format);                                                           \
            str += ",";                                                                          \
            b.prettyPrint(str,format);                                                           \
            str += ")";                                                                          \
        }                                                                                        \
    };                                                                                           \
                                                                                                 \
  BZ_DECLARE_ARRAY_ET_BINARY(name, name ## _impl)

BZ_NAMESPACE_END

#endif
