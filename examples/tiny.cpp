/***************************************************************************
 * tiny.cpp    Blitz++ TinyVector<T,N> ray reflection example
 * 
 * $Id$
 *
 * $Log$
 * Revision 1.3  2002/07/02 19:49:02  jcumming
 * Updated to use new header file names that avoid capitalization.
 *
 * Revision 1.2  2001/01/26 18:30:51  tveldhui
 * More source code reorganization to reduce compile times.
 *
 * Revision 1.1.1.1  2000/06/19 12:26:17  tveldhui
 * Imported sources
 *
 * Revision 1.2  1997/07/16 19:38:23  tveldhui
 * Update: Alpha release 0.2 (Arrays)
 *
 * Revision 1.1  1997/02/02 21:14:42  tveldhui
 * Initial revision
 *
 ****************************************************************************
 *
 * This example illustrates the TinyVector<T,N> class.  TinyVectors can be
 * used for small vectors whose sizes are known at compile time.  Most
 * operations on TinyVectors have their loops unravelled inline using template 
 * metaprograms.
 *
 * The routine reflect(..) calculates the reflection of a monochrome ray 
 * of light bouncing off a perfectly reflective, smooth surface.  
 */

#include <blitz/tinyvec-et.h>

#ifdef BZ_NAMESPACES
using namespace blitz;
#endif

void reflect(TinyVector<double,3>& reflection, const TinyVector<double,3>& ray,
    const TinyVector<double,3>& surfaceNormal)
{
    // The surface normal must be unit length to use this equation.

    reflection = ray - 2 * dot(ray,surfaceNormal) * surfaceNormal;
}

int main()
{
    TinyVector<double,3> x, y, z;

    // y will be the incident ray
    y[0] = 1;
    y[1] = 0;
    y[2] = -1;

    // z is the surface normal 
    z[0] = 0;
    z[1] = 0;
    z[2] = 1;

    reflect(x, y, z);

    cout << "Reflected ray is: [ " << x[0] << " " << x[1] << " " << x[2]
         << " ]" << endl;
}

// Here's the assembly generated for reflect() using KCC +K3 -O2 on an
// IBM RS/6000:

// .reflect__(mangled-name)
//        lfd     fp0,16(r4)
//        lfd     fp1,16(r5)
//        lfd     fp3,8(r4)
//        fm      fp1,fp0,fp1
//        lfd     fp0,8(r5)
//        lfd     fp2,0(r4)
//        fma     fp0,fp3,fp0,fp1
//        lfd     fp1,0(r5)
//        fma     fp0,fp2,fp1,fp0
//        fa      fp0,fp0,fp0
//        fnms    fp1,fp1,fp0,fp2
//        stfd    fp1,0(r3)
//        lfd     fp1,8(r4)
//        lfd     fp2,8(r5)
//        fnms    fp1,fp0,fp2,fp1
//        stfd    fp1,8(r3)
//        lfd     fp1,16(r4)
//        lfd     fp2,16(r5)
//        fnms    fp0,fp0,fp2,fp1
//        stfd    fp0,16(r3)
//        bcr     BO_ALWAYS,CR0_LT

