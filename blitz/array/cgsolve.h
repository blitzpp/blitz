// -*- C++ -*-
/***************************************************************************
 * blitz/array/cgsolve.h  Basic conjugate gradient solver for linear systems
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
#ifndef BZ_CGSOLVE_H
#define BZ_CGSOLVE_H

namespace blitz {

template<typename T_numtype>
void dump(const char* name, Array<T_numtype,3>& A)
{
    T_numtype normA = 0;

    for (int i=A.lbound(0); i <= A.ubound(0); ++i)
    {
      for (int j=A.lbound(1); j <= A.ubound(1); ++j)
      {
        for (int k=A.lbound(2); k <= A.ubound(2); ++k)
        {
            T_numtype tmp = A(i,j,k);
            normA += BZ_MATHFN_SCOPE(fabs)(tmp);
        }
      }
    }

    normA /= A.numElements();
    cout << "Average magnitude of " << name << " is " << normA << endl;
}

template<typename T_stencil, typename T_numtype, int N_rank, typename T_BCs>
int conjugateGradientSolver(T_stencil stencil,
    Array<T_numtype,N_rank>& x,
    Array<T_numtype,N_rank>& rhs, double haltrho, 
    const T_BCs& boundaryConditions)
{
    // NEEDS_WORK: only apply CG updates over interior; need to handle
    // BCs separately.

    // x = unknowns being solved for (initial guess assumed)
    // r = residual
    // p = descent direction for x
    // q = descent direction for r

    RectDomain<N_rank> interior = interiorDomain(stencil, x, rhs);

cout << "Interior: " << interior.lbound() << ", " << interior.ubound()
     << endl;

    // Calculate initial residual
    Array<T_numtype,N_rank> r = rhs.copy();
    r *= -1.0;

    boundaryConditions.applyBCs(x);

    applyStencil(stencil, r, x);

 dump("r after stencil", r);
 cout << "Slice through r: " << endl << r(23,17,Range::all()) << endl;
 cout << "Slice through x: " << endl << x(23,17,Range::all()) << endl;
 cout << "Slice through rhs: " << endl << rhs(23,17,Range::all()) << endl;

    r *= -1.0;

 dump("r", r);

    // Allocate the descent direction arrays
    Array<T_numtype,N_rank> p, q;
    allocateArrays(x.shape(), p, q);

    int iteration = 0;
    int converged = 0;
    T_numtype rho = 0.;
    T_numtype oldrho = 0.;

    const int maxIterations = 1000;

    // Get views of interior of arrays (without boundaries)
    Array<T_numtype,N_rank> rint = r(interior);
    Array<T_numtype,N_rank> pint = p(interior);
    Array<T_numtype,N_rank> qint = q(interior);
    Array<T_numtype,N_rank> xint = x(interior);

    while (iteration < maxIterations)
    {
        rho = sum(r * r);

        if ((iteration % 20) == 0)
            cout << "CG: Iter " << iteration << "\t rho = " << rho << endl;

        // Check halting condition
        if (rho < haltrho)
        {
            converged = 1;
            break;
        }

        if (iteration == 0)
        {
            p = r;
        }
        else {
            T_numtype beta = rho / oldrho;
            p = beta * p + r;
        }

        q = 0.;
//        boundaryConditions.applyBCs(p);
        applyStencil(stencil, q, p);

        T_numtype pq = sum(p*q);

        T_numtype alpha = rho / pq;

        x += alpha * p;
        r -= alpha * q;

        oldrho = rho;
        ++iteration;
    }

    if (!converged)
        cout << "Warning: CG solver did not converge" << endl;

    return iteration;
}

}

#endif // BZ_CGSOLVE_H
