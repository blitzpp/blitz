/*****************************************************************************
 * qcd.cpp     Blitz++ TinyMatrix<T> example.  
 *
 * $Id$
 *
 * $Log$
 * Revision 1.2  2001/01/26 18:30:51  tveldhui
 * More source code reorganization to reduce compile times.
 *
 * Revision 1.1.1.1  2000/06/19 12:26:17  tveldhui
 * Imported sources
 *
 * Revision 1.2  1997/07/16 19:38:23  tveldhui
 * Update: Alpha release 0.2 (Arrays)
 *
 * Revision 1.1  1997/02/28 23:32:41  tveldhui
 * Initial revision
 *
 *****************************************************************************
 * This example illustrates the TinyMatrix<T,N,M> class.  TinyMatrix can
 * be used for small matrices whose dimensions are known at compile time.
 * The application is from lattice quantum chromodynamics.
 *
 * See: S. Booth, Lattice QCD simulation programs on the Cray T3D,
 * Edinburgh Parallel Computing Centre Technical Report EPCC-TR96-03.  
 * http://www.epcc.ed.ac.uk/t3d/documents/techreports.html
 */

#include <blitz/blitz.h>

#ifdef BZ_HAVE_COMPLEX

#include <blitz/TinyMat.h>
#include <blitz/Vector.h>

#ifdef BZ_NAMESPACES
using namespace blitz;
#endif

/*
 * This example is drawn from a technical report by Stephen Booth of
 * the Edinburgh Parallel Computing Centre.  In his group's implementation 
 * of lattice QCD, most of the CPU time is taken up by a group of routines 
 * which multiplies 2-spinors by SU(3) gauge elements.  In Fortran, this 
 * code looks like:
 *
 * COMPLEX M(V,3,3) res(V,3,2), src(V,3,2)
 *   DO spin=1,2
 *       DO col=1,3
 *           DO site=1,V
 *               res(site,col,spin)=
 *                        M(site,col,1) * src(site,1,spin)
 *                      + M(site,col,2) * src(site,2,spin)
 *                      + M(site,col,3) * src(site,3,spin)
 *           END DO
 *       END DO
 *   END DO
 *
 * This is a situation in which TinyMatrix can be used to good
 * effect: each element of `src' is a 3x2 complex matrix, and
 * each element of `M' is a 3x3 complex matrix.  
 */

typedef TinyMatrix<complex<double>, 3, 3> gauge;
typedef TinyMatrix<complex<double>, 3, 2> spinor;

/*
 * The following two-line function is equivalent to the Fortran version
 * above.
 */

inline void qcdUpdate(Vector<spinor>& res, Vector<gauge>& M, 
    Vector<spinor>& src)
{
    for (int i=0; i < res.length(); ++i)
        res[i] = product(M[i], src[i]);
}

int main()
{
    const int numElements = 100;   // Some number of elements

    Vector<gauge> M(numElements);
    Vector<spinor> res(numElements), src(numElements);

    qcdUpdate(res, M, src);

    return 0;
}

/*
 * Since the dimensions of gauge and spinor are known at compile
 * time, the Blitz++ library unrolls the matrix multiplication
 * loops.  Here is the assembler code generated for qcdUpdate(..) 
 * using KAI C++ on an RS/6000.
 *
 * fm    floating-point multiply
 * fma   floating-point multiply and add
 * lfd   load double-precision floating point
 * stfd  store double-precision floating point
 *
 * Note the use of pre-fetching and quad operand instructions.
 */

#if 0
        l       r10,4(r28)
        l       r9,0(r28)
        cal     r11,100(r0)
        cmpi    0,r10,0
        ai      r7,r27,-40
        ai      r8,r29,-8
        ai      r9,r9,-72
        mtspr   CTR,r11
__L740:                                 # 0x00000740 (H.10.NO_SYMBOL+0x740)
        lfd     fp2,68(r7)
        lfd     fp25,116(r9)
        lfd     fp26,108(r9)
        fm      fp3,fp2,fp25
        lfd     fp6,60(r7)
        fm      fp0,fp26,fp2
        lfd     fp1,84(r7)
        fms     fp9,fp6,fp26,fp3
        lfd     fp23,148(r9)
        fma     fp10,fp6,fp25,fp0
        lfd     fp24,140(r9)
        fm      fp3,fp1,fp23
        lfd     fp7,76(r7)
        fm      fp0,fp24,fp1
        lfd     fp5,52(r7)
        fms     fp3,fp7,fp24,fp3
        lfd     fp28,84(r9)
        fma     fp0,fp7,fp23,fp0
        lfd     fp27,76(r9)
        fm      fp4,fp5,fp28
        lfd     fp8,44(r7)
        fa      fp3,fp9,fp3
        fms     fp9,fp8,fp27,fp4
        fm      fp4,fp27,fp5
        fa      fp0,fp10,fp0
        fa      fp3,fp9,fp3
        fma     fp4,fp8,fp28,fp4
        stfd    fp3,12(r8)
        fa      fp0,fp0,fp4
        stfd    fp0,20(r8)
        lfd     fp30,124(r9)
        lfd     fp13,132(r9)
        fm      fp0,fp2,fp30
        lfd     fp12,156(r9)
        fm      fp4,fp2,fp13
        lfd     fp29,164(r9)
        fma     fp3,fp6,fp13,fp0
        lfd     fp31,92(r9)
        fm      fp0,fp1,fp12
        lfdu    fp11,100(r9)
        fm      fp2,fp1,fp29
        fma     fp1,fp7,fp29,fp0
        fm      fp0,fp5,fp31
        fms     fp4,fp6,fp30,fp4
        fms     fp2,fp7,fp12,fp2
        fm      fp5,fp5,fp11
        fa      fp1,fp3,fp1
        fma     fp0,fp8,fp11,fp0
        fa      fp2,fp4,fp2
        fms     fp3,fp8,fp31,fp5
        fa      fp0,fp0,fp1
        fa      fp1,fp2,fp3
        stfd    fp0,36(r8)
        stfd    fp1,28(r8)
        lfd     fp9,132(r7)
        lfd     fp22,116(r7)
        fm      fp1,fp23,fp9
        lfd     fp7,100(r7)
        fm      fp3,fp25,fp22
        lfd     fp8,108(r7)
        fm      fp0,fp26,fp22
        lfd     fp10,124(r7)
        fm      fp2,fp24,fp9
        lfd     fp5,92(r7)
        fms     fp3,fp26,fp8,fp3
        fms     fp1,fp24,fp10,fp1
        fma     fp0,fp25,fp8,fp0
        fma     fp2,fp23,fp10,fp2
        fm      fp4,fp28,fp7
        fm      fp6,fp27,fp7
        fa      fp1,fp3,fp1
        fa      fp0,fp0,fp2
        fma     fp3,fp28,fp5,fp6
        fms     fp2,fp27,fp5,fp4
        fa      fp0,fp0,fp3
        fa      fp1,fp1,fp2
        fm      fp2,fp13,fp22
        stfd    fp1,44(r8)
        stfd    fp0,52(r8)
        fms     fp1,fp30,fp8,fp2
        fm      fp0,fp29,fp9
        fm      fp3,fp12,fp9
        fm      fp2,fp30,fp22
        fms     fp0,fp12,fp10,fp0
        fma     fp4,fp29,fp10,fp3
        fma     fp2,fp13,fp8,fp2
        fm      fp3,fp31,fp7
        fa      fp0,fp1,fp0
        fm      fp6,fp11,fp7
        fa      fp1,fp2,fp4
        fma     fp2,fp11,fp5,fp3
        fms     fp3,fp31,fp5,fp6
        fa      fp1,fp1,fp2
        fa      fp0,fp0,fp3
        stfd    fp1,68(r8)
        stfd    fp0,60(r8)
        lfd     fp7,164(r7)
        lfd     fp2,180(r7)
        fm      fp4,fp25,fp7
        lfd     fp0,156(r7)
        fm      fp5,fp23,fp2
        lfd     fp1,172(r7)
        fm      fp3,fp26,fp7
        fms     fp6,fp26,fp0,fp4
        fms     fp5,fp24,fp1,fp5
        fma     fp4,fp25,fp0,fp3
        fa      fp3,fp6,fp5
        fm      fp9,fp24,fp2
        lfd     fp8,140(r7)
        fm      fp6,fp13,fp7
        lfdu    fp5,148(r7)
        fm      fp7,fp30,fp7
        fma     fp25,fp23,fp1,fp9
        fm      fp9,fp29,fp2
        fm      fp26,fp28,fp5
        fm      fp10,fp27,fp5
        fma     fp7,fp13,fp0,fp7
        fm      fp2,fp12,fp2
        fms     fp13,fp27,fp8,fp26
        fms     fp9,fp12,fp1,fp9
        fa      fp4,fp4,fp25
        fma     fp10,fp28,fp8,fp10
        fma     fp1,fp29,fp1,fp2
        fms     fp0,fp30,fp0,fp6
        fa      fp2,fp13,fp3
        fm      fp6,fp11,fp5
        fa      fp3,fp10,fp4
        fm      fp4,fp31,fp5
        fa      fp0,fp0,fp9
        fms     fp5,fp31,fp8,fp6
        fma     fp4,fp11,fp8,fp4
        stfd    fp2,76(r8)
        stfd    fp3,84(r8)
        fa      fp1,fp7,fp1
        fa      fp0,fp5,fp0
        fa      fp1,fp4,fp1
        stfd    fp0,92(r8)
        stfdu   fp1,100(r8)
        bc      BO_dCTR_NZERO,CR0_LT,__L740

#endif

#else // BZ_HAVE_COMPLEX

#include <iostream.h>

int main()
{
    cout << "This example requires <complex> from the ISO/ANSI C++ standard."
         << endl;

    return 0;
}

#endif
