/***************************************************************************
 * gmres.cpp  The GMRES iterative algorithm for solving large scale
 *            sparse or band-limited linear systems
 *
 * references: 
 * [1]   Youcef Saad and Martin H. Schultz, "GMRES: a generalized minimal 
 *       residual algorithm for solving nonsymmetric linear systems",
 *       SIAM J. Sci. Stat. Comput., Vol. 7, No. 3, July 1986, pp. 856--869
 * [2]   http://netlib2.cs.utk.edu/linalg/html_templates/Templates.html
 * [3]   http://www.netlib.org/utk/papers/templates/node29.html
 *
 * Also check http://www.netlib.org/utk/papers/iterative-survey/
 *
 *
 * Copyright (C) 2000-2006 Idesbald van den Bosch <vandenbosch.mailinglist@gmail.com>
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
 * Suggestions:          vandenbosch.mailinglist@gmail.com
 * Bugs:                 vandenbosch.mailinglist@gmail.com
 *
 * For more information, please see the ... Home Page:
 *
 ****************************************************************************/
#include <iostream>
#include <complex>
#include <cmath>
#include <blitz/array.h>

using namespace blitz;

double norm2 (const Array<complex<double>, 1>& x)
{
  return sqrt(abs(sum(x * conj(x))));
}

void checkMatrixVectorDimensions(const int M, // required number of A lines 
                                 const int N, // required number of A columns 
                                 const Array<complex<double>, 2>& A, 
                                 const Array<complex<double>, 1>& x)
// check dimensions in view of performing A*x or solving A*x = y 
{
  if ( A.extent(0) != M ) {
    cout << "checkMatrixVectorDimensions():" << endl;
    cout << "problem with A dimensions: A.extent(0) = " << A.extent(0) << endl;
    cout << "M = " << M << endl;
    exit(1);
  }
  if ( A.extent(1) != N ) {
    cout << "checkMatrixVectorDimensions():" << endl;
    cout << "problem with A dimensions: A.extent(1) = " << A.extent(1) << endl;
    cout << "N = " << N << endl;
    exit(1);
  }
  if ( x.extent(0) != N ) {
    cout << "checkMatrixVectorDimensions():" << endl;
    cout << "problem with x dimensions: x.extent(0) = " << x.extent(0) << endl;
    cout << "N = " << N << endl;
    exit(1);
  }
}

Array<complex<double>, 1> matrixMultiply (const Array<complex<double>, 2>& A,
                                          const Array<complex<double>, 1>& b)
{
  int i, j;
  const int M = A.extent(0), N = b.extent(0);
  // check dimensions
  checkMatrixVectorDimensions(M, N, A, b);
  Array<complex<double>, 1> result(M);
  result = 0.0;
  for (i=0 ; i<M ; i++) {
    for (j=0 ; j<N ; j++) {
      result(i) += A(i,j) * b(j);
    }
  }
  return result;
}

void triangleUpSolve(Array<complex<double>, 1>& x,
                     const Array<complex<double>, 2>& T,
                     const Array<complex<double>, 1>& y)
/*
 * This function computes the solution of a linear system
 * where T is a upper triangular matrix, i.e. T(i>j, j) = 0.0.
 */
{
  int i, j;
  const int N = y.extent(0);
  // check dimensions: T must be square
  checkMatrixVectorDimensions(N, N, T, y);
  for (i=N-1 ; i>-1 ; i--) {
    // x(i) = 1/T(i, i) * ( y(i) - sum(T(i, i+1:N-1) * x(i+1:N-1)) )
    x(i) = y(i);
    for (j=i+1 ; j<N ; j++) {
      x(i) -= T(i, j) * x(j);
    }
    x(i) /= T(i, i);
  }
}

void rotmat(complex<double>& cs, 
            complex<double>& sn, 
            const complex<double>& a, 
            const complex<double>& b)
// compute the Givens rotation matrix parameters for a and b
{
  complex<double> temp;
  if (b==0.0) {
    cs = 1.0;
    sn = 0.0;
  }
  else if ( abs(b) > abs(a) ) {
    temp = -a/b;
    sn = 1.0 / sqrt(1.0 + temp*temp);
    cs = temp * sn;
  }
  else {
    temp = -b/a;
    cs = 1.0 / sqrt(1.0 + temp*temp);
    sn = temp * cs;
  }
}

void gmres(Array<complex<double>, 1>& x, // INPUT, OUTPUT: initial guess, converged solution
           double & error, // OUTPUT: the error
           int & iter, // OUTPUT: number of iterations needed
           int & flag, // OUTPUT: success flag: 0 if OK
           const Array<complex<double>, 2>& A, // INPUT: complex matrix
           const Array<complex<double>, 1>& b, // INPUT: right-hand side
           const double tol, // INPUT: tolerance on solution
           const int RESTRT, // INPUT: restart number
           const int MAXITER) // INPUT: max number of iterations
/*************************************************************************
 * gmres solves the non-symmetric linear system Ax = b using the 
 * Generalized Minimum Residual method
 *
 * The flag output 0 indicates convergence within MAXITER
 * iterations. If no convergence within MAXITER iterations: flag = 1.
 *
 * Upon successful return, other output arguments have the following values:
 *
 *        x  --  approximate solution to A*x = b
 *     iter  --  the number of iterations performed before the
 *               tolerance was reached
 *    error  --  the residual after the final iteration
 **************************************************************************/
{
  Range all = Range::all();
  flag = 0;
  int i, k;
  const int N = b.extent(0), m = RESTRT; // size of the system
  // dimensions and other checks
  checkMatrixVectorDimensions(N, N, A, x);
  if (RESTRT < 1) {
    cout << "bad restart value. RESTRT = " << RESTRT << endl;
    exit(1);
  }
  if (MAXITER < 1) {
    cout << "bad maxiter value. MAXITER = " << MAXITER << endl;
    exit(1);
  }

  double bnorm2 = norm2(b), rnorm2;
  if (bnorm2==0.0) bnorm2 = 1.0;
  complex<double> temp;
  Array<complex<double>, 1> r(N);

  // r = precondSolve(M, b, A, x) 
  //   = M^(-1) * ( b-A*x )
  // this will be done in a later version of the code
  r = b - matrixMultiply(A, x);
  error = norm2(r) / bnorm2;
  if (error<tol) return;

  // workspaces definitions
  Array<complex<double>, 1> cs(m), sn(m), e1(m+1), s(m+1), w(N), y;
  Array<complex<double>, 2> V(N, m+1), H(m+1, m);
  e1 = 0.0;
  e1(0) = 1.0;

  for (iter=0 ; iter<MAXITER ; iter++) {
    // r = precondSolve(M, b, A, x) 
    //   = M^(-1) * ( b-A*x )
    // this will be done in a later version of the code
    r = b - matrixMultiply(A, x);
    rnorm2 = norm2(r);
    V(all, 0) = r/rnorm2;
    s = rnorm2 * e1;

    for (i=0 ; i<m ; i++){
      // if preconditioning: w = M^(-1) * (A*V(all, i))
      w = matrixMultiply(A, V(all, i));

      // construct orthonormal basis using Gram-Schmidt
      for (k=0 ; k<i+1 ; k++) {
        H(k, i) = sum(w * conj(V(all, k)));
        w -= H(k, i) * V(all, k);
      }
      H(i+1, i) = norm2( w );
      V(all, i+1) = w / H(i+1, i);

      // now we apply the GIVENS rotations
      for (k=0 ; k<i ; k++) {
        temp = conj(cs(k)) * H(k, i) - conj(sn(k)) * H(k+1, i);
        H(k+1, i) = sn(k) * H(k, i) + cs(k) * H(k+1, i);
        H(k, i) = temp;
      }

      // form i-th rotation matrix
      rotmat(cs(i), sn(i), H(i, i), H(i+1, i));
      H(i, i) = conj(cs(i)) * H(i, i) - conj(sn(i)) * H(i+1, i);
      H(i+1,i) = 0.0;

      // approximate residual norm
      temp = conj(cs(i)) * s(i) - conj(sn(i)) * s(i+1);
      s(i+1) = sn(i) * s(i) + cs(i) * s(i+1);
      s(i) = temp;
      error = abs(s(i+1)) / bnorm2;

      // update approximation x
      if ( error<=tol ) {
        y.resize(i+1); // Range: 0..i
        triangleUpSolve( y, H(Range(0, i), Range(0, i)), s(Range(0, i)) );
        x += matrixMultiply(V(all, Range(0, i)), y);
        return;
      }
    } // end for (i =...)
    
    if ( error<=tol ) return;
    y.resize(m); // Range: 0..m-1
    triangleUpSolve( y, H(Range(0, m-1), Range(0, m-1)), s(Range(0, m-1)) );
    x += matrixMultiply(V(all, Range(0, m-1)), y);
    // r = precondSolve(M, b, A, x) 
    //   = M^(-1) * ( b-A*x )
    // this will be done in a later version of the code
    r = b - matrixMultiply(A, x);
    // check convergence
    error = abs(s(m)) / bnorm2;
    if ( error<=tol ) return;
  } // end for (iter =...)

  // bad ending...
  if (error>tol) flag = 1;
}




