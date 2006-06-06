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

using namespace blitz;

void gmres(blitz::Array<complex<double>, 1>& x, // OUTPUT: converged solution
           double & error, // OUTPUT: the error
           int & iter, // OUTPUT: number of iterations needed
           int & flag, // OUTPUT: success flag: 0 if OK
           const blitz::Array<complex<double>, 2>& A, // INPUT: complex matrix
           const blitz::Array<complex<double>, 1>& b, // INPUT: right-hand side
           const double tol, // INPUT: tolerance on solution
           const int RESTRT, // INPUT: restart number
           const int MAXITER); // INPUT: max number of iterations


