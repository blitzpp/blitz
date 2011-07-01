/***************************************************************************
 * blitz/tinyvec.cc  Declaration of TinyVector methods
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

#ifndef BZ_TVEVALUATE_H
#define BZ_TVEVALUATE_H

#include <blitz/tinyvec2.h>
#include <blitz/update.h>
#include <blitz/blitz.h>
#include <blitz/meta/vecassign.h>

BZ_NAMESPACE(blitz)


/** The _tv_evaluator class has a template argument that indicates
    whether the loop should be unrolled or not. The default
    implementation does not unroll. This arrangement avoids
    instantiating very long meta-unrolls of very long TinyVectors. */
template<bool unroll, int N_length>
struct _tv_evaluator {

  /** This version of the evaluation function assumes that the
      TinyVectors have appropriate alignment (as will always be the
      case if they are actual TinyVector objects and not created using
      reinterpret_cast in the chunked_updater. */
  template<typename T_numtype, typename T_expr, typename T_update>
  static _bz_forceinline void
  evaluate_aligned(T_numtype* data, const T_expr& expr, T_update) {
#pragma ivdep
#pragma vector aligned
    for (int i=0; i < N_length; ++i)
      T_update::update(data[i], expr.fastRead(i));
  }

  /** This version of the evaluation function is used when vectorizing
      expressions that we know can't be aligned. The only difference
      with evaluate_aligned is the compiler pragma that tells the
      compiler it is unaligned. */
  template<typename T_numtype, typename T_expr, typename T_update>
  static _bz_forceinline void
  evaluate_unaligned(T_numtype* data, const T_expr& expr, T_update) {
#pragma ivdep
#pragma vector unaligned
  for (int i=0; i < N_length; ++i)
    T_update::update(data[i], expr.fastRead(i));
  }
};
  
/** Specialization of the _tv_evaluator class that does meta-unroll
    the evaluation. */
template<int N_length>
struct _tv_evaluator<true, N_length> {

  /** This version of the evaluation function assumes that the
      TinyVectors have appropriate alignment (as will always be the
      case if they are actual TinyVector objects and not created using
      reinterpret_cast in the chunked_updater. */
  template<typename T_numtype, typename T_expr, typename T_update>
  static _bz_forceinline void
  evaluate_aligned(T_numtype* data, const T_expr& expr, T_update) {
    //#pragma ivdep
    //#pragma vector aligned
  _bz_meta_vecAssign<N_length, 0>::fastAssign(data, expr, T_update());
  }

  /** This version of the evaluation function is used when vectorizing
      expressions that we know can't be aligned. The only difference
      with evaluate_aligned is the compiler pragma that tells the
      compiler it is unaligned. */
  template<typename T_numtype, typename T_expr, typename T_update>
  static _bz_forceinline void
  evaluate_unaligned(T_numtype* data, const T_expr& expr, T_update) {
    //#pragma ivdep
    //#pragma vector unaligned
  _bz_meta_vecAssign<N_length, 0>::fastAssign(data, expr, T_update());
  }
};


/** This function intercepts TinyVector-only expressions and uses a
    much simpler evaluation that is more likely to get totally
    inlined */
template<typename P_numtype, int N_length>
template<typename T_expr, typename T_update>
_bz_forceinline
void
TinyVector<P_numtype,N_length>::_tv_evaluate(const T_expr& expr, T_update)
{
  if ((T_expr::numArrayOperands>0) || 
      (T_expr::numTMOperands>0) ||
      (T_expr::numIndexPlaceholders>0) ) {
    // not TV-only, punt to general evaluate
    _bz_evaluate(*this, expr, T_update());
    return;
  }

  // TV-only. Since TinyVectors can't have funny storage, ordering,
  // stride, or anything, it's now just a matter of evaluating it like
  // in the old vecassign.

  // since we can't resize tinyvectors, there are two options: all
  // vectors have our size or the expression is malformed.
    // Check that all arrays have the same shape
#ifdef BZ_DEBUG
    if (!expr.shapeCheck(shape()))
    {
      if (assertFailMode == false)
      {
        cerr << "[Blitz++] Shape check failed: Module " << __FILE__
             << " line " << __LINE__ << endl
             << "          Expression: ";
        prettyPrintFormat format(true);   // Use terse formatting
        BZ_STD_SCOPE(string) str;
        expr.prettyPrint(str, format);
        cerr << str << endl ;
      }
    }
#endif

  BZPRECHECK(expr.shapeCheck(shape()),
	     "Shape check failed." << endl << "Expression:");

  BZPRECONDITION(expr.isUnitStride(0));
  BZPRECONDITION(T_expr::rank_<=1);
  BZPRECONDITION(T_expr::numIndexPlaceholders==0);

  // now call the aligned evaluation function
  const bool unroll = N_length < BZ_TV_EVALUATE_UNROLL_LENGTH;
  _tv_evaluator<unroll, N_length>::evaluate_aligned(data(), expr, T_update());
}

BZ_NAMESPACE_END

#endif // BZ_TVEVALUATE_H
