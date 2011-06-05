/***************************************************************************
 * blitz/array/ops.cc  Basic operators for arrays.
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
#ifndef BZ_TM2OPS_CC
#define BZ_TM2OPS_CC

#include <blitz/update.h>
#include <blitz/array/asexpr.h>
#include <blitz/globeval.cc>

BZ_NAMESPACE(blitz)

/*
 * Constant operands
 */

template<typename P_numtype, int N_rows, int N_columns>
TinyMatrix<P_numtype, N_rows, N_columns>&
TinyMatrix<P_numtype, N_rows, N_columns>::initialize(T_numtype x)
{
    (*this) = _bz_ArrayExpr<_bz_ArrayExprConstant<T_numtype> >(x);
    return *this;
}

template<typename P_numtype, int N_rows, int N_columns>
template<typename T_expr>
inline
TinyMatrix<P_numtype, N_rows, N_columns>&
TinyMatrix<P_numtype, N_rows, N_columns>::operator=(const ETBase<T_expr>& expr)
{
  _bz_evaluate(*this, _bz_typename asExpr<T_expr>::T_expr(expr.unwrap()), 
	       _bz_update<T_numtype, _bz_typename asExpr<T_expr>::T_expr::T_result>());
    return *this;
}

#define BZ_TM2_UPDATE(op,name)						\
  template<typename P_numtype, int N_rows, int N_columns>		\
  template<typename T>							\
  inline TinyMatrix<P_numtype, N_rows, N_columns>&			\
  TinyMatrix<P_numtype, N_rows, N_columns>::operator op(const T& expr)	\
  {									\
  _bz_evaluate(*this, _bz_typename asExpr<T>::T_expr(expr),		\
	       name<T_numtype, _bz_typename asExpr<T>::T_expr::T_result>()); \
  return *this;								\
  }

BZ_TM2_UPDATE(+=, _bz_plus_update)
BZ_TM2_UPDATE(-=, _bz_minus_update)
BZ_TM2_UPDATE(*=, _bz_multiply_update)
BZ_TM2_UPDATE(/=, _bz_divide_update)
BZ_TM2_UPDATE(%=, _bz_mod_update)
BZ_TM2_UPDATE(^=, _bz_xor_update)
BZ_TM2_UPDATE(&=, _bz_bitand_update)
BZ_TM2_UPDATE(|=, _bz_bitor_update)
BZ_TM2_UPDATE(<<=, _bz_shiftl_update)
BZ_TM2_UPDATE(>>=, _bz_shiftr_update)


BZ_NAMESPACE_END

#endif // BZ_TM2OPS_CC
