/*****************************************************************************
 * erf.cpp        Blitz++ Vector<T> example
 *
 * $Id$
 *
 * $Log$
 * Revision 1.3  2002/07/02 19:49:02  jcumming
 * Updated to use new header file names that avoid capitalization.
 *
 * Revision 1.2  2001/01/26 18:30:50  tveldhui
 * More source code reorganization to reduce compile times.
 *
 * Revision 1.1.1.1  2000/06/19 12:26:17  tveldhui
 * Imported sources
 *
 * Revision 1.1  1997/07/16 19:38:23  tveldhui
 * Update: Alpha release 0.2 (Arrays)
 *
 *****************************************************************************
 */

#include <blitz/blitz.h>

#ifdef BZ_HAVE_IEEE_MATH

#include <blitz/vector-et.h>

// This program uses erf(), which is not part of ANSI C/C++.  In order
// to compile this example, you must have a Posix or X/Open-compliant 
// compiler, and #define an appropriate source level (-D_XOPEN_SOURCE or
// -D_POSIX_SOURCE).  You will need to run compiler/bzconfig with
// this flag defined as well, so that the Blitz++ flag BZ_HAVE_IEEE_MATH
// will be set properly in <blitz/config.h>.

#ifdef BZ_NAMESPACES
using namespace blitz;
#endif

int main()
{
    // Integrate the expression
    //            x
    //   2        /
    // -------    | exp(-t^2) dt
    // sqrt(Pi)   /
    //           0
    // to estimate the error function erf(x) on the interval [0,1].
    //
    // Three methods are compared:
    //  1. Naive summation
    //  2. Two-point trapezoid
    //  3. Three-point Simpson's

    const double m_2_sqrtpi = 1.12837916709551257389615890312154517;
    const int numSamples = 1024;       // Number of samples
    double dt = 1.0 / numSamples;      // Distance between samples
    Range R(0, numSamples - 1);        // Index set for sample vectors
    Range displayRange(0, 900, 100);   // Indices to output to screen

    // For comparison purposes, use the built-in erf(x) function.
    Vector<double> z = erf(R * dt);
    cout << "  Built-in: " << z(displayRange+1) << endl;


    // Naive summation
    Vector<double> z1 = accumulate(m_2_sqrtpi * exp(-sqr(R * dt)) * dt);
    cout << "     Naive: " << z1(displayRange+1) << endl;

    // Calculate the rms error
    double error1 = sqrt(mean(sqr(z1 - z)));
    cout << "RMS Error: " << error1 << endl;


    // For the following rules, it's easier to work with a
    // sampled integrand.
    Vector<double> a = m_2_sqrtpi * exp(-sqr(R * dt));


    // Two-point trapezoid
    Range J(1, numSamples-1);
    Vector<double> z2 = accumulate(dt / 2.0 * (a(J) + a(J-1)));

    cout << " Trapezoid: " << z2(displayRange) << endl;
    cout << "RMS Error: " << sqrt(mean(sqr(z2-z(J)))) << endl;


    // Three-point Simpson's (parabolic)
    Range I(1, numSamples-2);
    Vector<double> z3 = accumulate(dt / 6.0 * (a(I-1) + 4 * a(I) + a(I+1)));

    cout << " Parabolic: " << z3(displayRange) << endl;
    cout << "RMS Error: " << sqrt(mean(sqr(z3 - z(I)))) << endl;


    return 0;
}

#else

#include <iostream.h>

int main()
{
    cout << "This example requires IEEE math functions." << endl;
    return 0;
}

#endif  // BZ_HAVE_IEEE_MATH
