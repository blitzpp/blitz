#ifndef BZ_NEWET_MACROS_H
#define BZ_NEWET_MACROS_H

#include <blitz/array/asexpr.h>

BZ_NAMESPACE(blitz)

/*
 * Array expression templates: the macro BZ_DECLARE_ARRAY_ET(X,Y)
 * declares a function or operator which takes two operands.
 * X is the function name (or operator), and Y is the functor object
 * which implements the operation.
 */

#define BZ_DECLARE_ARRAY_ET(name, applic)                                 \
                                                                          \
template<class T_numtype1, int N_rank1, class T_other>                    \
_bz_inline_et                                                             \
_bz_ArrayExpr<_bz_ArrayExprOp<FastArrayIterator<T_numtype1, N_rank1>,     \
    _bz_typename asExpr<T_other>::T_expr,                                 \
    applic<T_numtype1,                                                    \
    _bz_typename asExpr<T_other>::T_expr::T_numtype> > >                  \
name (const Array<T_numtype1,N_rank1>& d1,                                \
    const T_other& d2)                                                    \
{                                                                         \
    return _bz_ArrayExpr<_bz_ArrayExprOp<FastArrayIterator<T_numtype1,    \
        N_rank1>,                                                         \
        _bz_typename asExpr<T_other>::T_expr,                             \
        applic<T_numtype1,                                                \
        _bz_typename asExpr<T_other>::T_expr::T_numtype> > >              \
      (d1.beginFast(),d2);                                                \
}                                                                         \
                                                                          \
template<class T_expr1, class T_other>                                    \
_bz_inline_et                                                             \
_bz_ArrayExpr<_bz_ArrayExprOp<_bz_ArrayExpr<T_expr1>,                     \
    _bz_typename asExpr<T_other>::T_expr,                                 \
    applic<_bz_typename T_expr1::T_numtype,                               \
        _bz_typename asExpr<T_other>::T_expr::T_numtype> > >              \
name(const _bz_ArrayExpr<T_expr1>& d1,                                    \
    const T_other& d2)                                                    \
{                                                                         \
    return _bz_ArrayExpr<_bz_ArrayExprOp<_bz_ArrayExpr<T_expr1>,          \
        _bz_typename asExpr<T_other>::T_expr,                             \
        applic<_bz_typename T_expr1::T_numtype,                           \
            _bz_typename asExpr<T_other>::T_expr::T_numtype> > >(d1,d2);  \
}                                                                         \
                                                                          \
template<class T1, class T2>                                              \
_bz_inline_et                                                             \
_bz_ArrayExpr<_bz_ArrayExprOp<_bz_typename asExpr<T1>::T_expr,            \
    _bz_typename asExpr<T2>::T_expr,                                      \
    applic<_bz_typename asExpr<T1>::T_expr::T_numtype,                    \
        _bz_typename asExpr<T2>::T_expr::T_numtype> > >                   \
name(const ETBase<T1>& d1, const T2& d2)                                  \
{                                                                         \
    return _bz_ArrayExpr<_bz_ArrayExprOp<_bz_typename asExpr<T1>::T_expr, \
        _bz_typename asExpr<T2>::T_expr,                                  \
        applic<_bz_typename asExpr<T1>::T_expr::T_numtype,                \
            _bz_typename asExpr<T2>::T_expr::T_numtype> > >               \
        (static_cast<const T1&>(d1), d2);                                 \
}                                                                         \
                                                                          \
template<class T1, class T2>                                              \
_bz_inline_et                                                             \
_bz_ArrayExpr<_bz_ArrayExprOp<_bz_typename asExpr<T1>::T_expr,            \
_bz_typename asExpr<T2>::T_expr,                                          \
    applic<_bz_typename asExpr<T1>::T_expr::T_numtype,                    \
        _bz_typename asExpr<T2>::T_expr::T_numtype> > >                   \
name(const T1& d1,                                                        \
    const ETBase<T2>& d2)                                                 \
{                                                                         \
    return _bz_ArrayExpr<_bz_ArrayExprOp<_bz_typename                     \
        asExpr<T1>::T_expr,                                               \
        _bz_typename asExpr<T2>::T_expr,                                  \
        applic<_bz_typename asExpr<T1>::T_expr::T_numtype,                \
            _bz_typename asExpr<T2>::T_expr::T_numtype> > >               \
        (d1, static_cast<const T2&>(d2));                                 \
}                                                                         \
                                                                          \
template<int N1, class T_other>                                           \
_bz_inline_et                                                             \
_bz_ArrayExpr<_bz_ArrayExprOp<IndexPlaceholder<N1>,                       \
    _bz_typename asExpr<T_other>::T_expr,                                 \
    applic<int,                                                           \
        _bz_typename asExpr<T_other>::T_expr::T_numtype> > >              \
name(IndexPlaceholder<N1> d1,                                             \
    const T_other& d2)                                                    \
{                                                                         \
    return _bz_ArrayExpr<_bz_ArrayExprOp<IndexPlaceholder<N1>,            \
        _bz_typename asExpr<T_other>::T_expr,                             \
        applic<int,                                                       \
            _bz_typename asExpr<T_other>::T_expr::T_numtype> > >(d1,d2);  \
}                                                                         \

/*
 * Unary functions and operators
 */

#define BZ_DECLARE_ARRAY_ET_UOP(name, functor)                        \
template<class T1>                                                    \
_bz_inline_et                                                         \
_bz_ArrayExpr<_bz_ArrayExprUnaryOp<                                   \
    _bz_typename asExpr<T1>::T_expr,                                  \
    functor<_bz_typename asExpr<T1>::T_expr::T_numtype> > >           \
name(const ETBase<T1>& d1)                                            \
{                                                                     \
    return _bz_ArrayExpr<_bz_ArrayExprUnaryOp<                        \
        _bz_typename asExpr<T1>::T_expr,                              \
        functor<_bz_typename asExpr<T1>::T_expr::T_numtype> > >       \
      (static_cast<const T1&>(d1));                                   \
}

/*
 * User-defined expression template routines
 */

#define BZ_DECLARE_FUNCTION(name)                                     \
  template<class P_numtype>                                           \
  struct name ## _impl {                                              \
    typedef P_numtype T_numtype;                                      \
    template<class T>                                                 \
    static inline T apply(T x)                                        \
    { return name(x); }                                               \
                                                                      \
    template<class T1>                                                \
    static void prettyPrint(string& str,                              \
        prettyPrintFormat& format, const T1& a)                       \
    {                                                                 \
        str += #name;                                                 \
        str += "(";                                                   \
        a.prettyPrint(str,format);                                    \
        str += ")";                                                   \
    }                                                                 \
  };                                                                  \
                                                                      \
  BZ_DECLARE_ARRAY_ET_UOP(name, name ## _impl)

#define BZ_DECLARE_FUNCTION_RET(name, return_type)                    \
  template<class P_numtype>                                           \
  struct name ## _impl {                                              \
    typedef return_type T_numtype;                                    \
    template<class T>                                                 \
    static inline return_type apply(T x)                              \
    { return name(x); }                                               \
                                                                      \
    template<class T1>                                                \
    static void prettyPrint(string& str,                              \
        prettyPrintFormat& format, const T1& a)                       \
    {                                                                 \
        str += #name;                                                 \
        str += "(";                                                   \
        a.prettyPrint(str,format);                                    \
        str += ")";                                                   \
    }                                                                 \
  };                                                                  \
                                                                      \
  BZ_DECLARE_ARRAY_ET_UOP(name, name ## _impl)


#define BZ_DECLARE_FUNCTION2(name)                                    \
  template<class P_numtype1, class P_numtype2>                        \
  struct name ## _impl {                                              \
    typedef _bz_typename promote_trait<P_numtype1,                    \
        P_numtype2>::T_promote T_numtype;                             \
    template<class T1, class T2>                                      \
    static inline T_numtype apply(T1 x, T2 y)                         \
    { return name(x,y); }                                             \
                                                                      \
    template<class T1, class T2>                                      \
    static void prettyPrint(string& str,                              \
        prettyPrintFormat& format, const T1& a, const T2& b)          \
    {                                                                 \
        str += #name;                                                 \
        str += "(";                                                   \
        a.prettyPrint(str,format);                                    \
        str += ",";                                                   \
        b.prettyPrint(str,format);                                    \
        str += ")";                                                   \
    }                                                                 \
  };                                                                  \
                                                                      \
  BZ_DECLARE_ARRAY_ET(name, name ## _impl)

#define BZ_DECLARE_FUNCTION2_RET(name, return_type)                   \
  template<class P_numtype1, class P_numtype2>                        \
  struct name ## _impl {                                              \
    typedef return_type T_numtype;                                    \
    template<class T1, class T2>                                      \
    static inline T_numtype apply(T1 x, T2 y)                         \
    { return name(x,y); }                                             \
                                                                      \
    template<class T1, class T2>                                      \
    static void prettyPrint(string& str,                              \
        prettyPrintFormat& format, const T1& a, const T2& b)          \
    {                                                                 \
        str += #name;                                                 \
        str += "(";                                                   \
        a.prettyPrint(str,format);                                    \
        str += ",";                                                   \
        b.prettyPrint(str,format);                                    \
        str += ")";                                                   \
    }                                                                 \
  };                                                                  \
                                                                      \
  BZ_DECLARE_ARRAY_ET(name, name ## _impl)

BZ_NAMESPACE_END

#endif
