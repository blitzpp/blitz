#!/usr/bin/env python

# python version of the makeloops.cpp that generates the benchmark
# loops.

import time, pdb

# definitions of the loops (from loops.data)
loops=[
    ("loop1", ("x","y"),(), ("double", 8), 1, "$x = sqrt($y)"),
    ("loop2", ("x","y"),("u"), ("double", 8), 1, "$x = $y/u"),
    ("loop3", ("x","y"), ("a"), ("double", 8), 2, "$y = $y + a*$x"),
    ("loop5", ("x","a","b"), (), ("double", 8), 1, "$x = $a+$b"),
    ("loop6", ("x","a","b"), (), ("double", 8), 1, "$x = $a*$b"),
    ("loop8", ("a","x"), ("u"), ("double", 8), 1, "$x = u/$a"),
    ("loop9", ("a","x"), (), ("double", 8), 1, "$x = $x+$a"),
    ("loop10", ("x","a","b","c"), ("u"), ("double", 8), 3, "$x = u+$a+$b+$c"),
    ("loop11", ("x","a","b","c","d"), (), ("double", 8), 3, "$x = $a+$b+$c+$d"),
    ("loop12", ("y","x","a","b","c","d"), ("u"), ("double", 8), 4,
     "$y = u+$a; $x = $a+$b+$c+$d"),
    ("loop13", ("y","x","a","b","c","d"), ("u"), ("double", 8), 4,
     "$x = $a+$b+$c+$d; $y = u+$d"),
    ("loop14", ("y","x","a","b"), (), ("double", 8), 2,
     "$x = $a+$b; $y = $a-$b"),
    ("loop15", ("x","a","b","c"), (), ("double", 8), 3, "$x = $c + $a*$b"),
    ("loop16", ("y","x","a","b","c"), ("u"), ("double", 8), 4,
     "$x = $a+$b+$c; $y = $x+$c+u"),
    ("loop17", ("x","a","b","c","d"), (), ("double", 8), 3,
     "$x = ($a+$b)*($c+$d)"),
    ("loop18", ("x","a","b"), ("u","v"), ("double", 8), 3, "$x = (u+$a)*(v+$b)"),
    ("loop19", ("y","x","a","b"), ("u","v"), ("double", 8), 2,
     "$x = u*$a; $y = v*$b"),
    ("loop21", ("x","a","b","c","d"), (), ("double", 8), 3,
     "$x = $a*$b + $c*$d"),
    ("loop22", ("x","a","b","c","d"), (), ("double", 8), 4,
     "$x = $x + $a*$b + $c*$d"),
    ("loop23", ("x","a","b","c","d","y"), (), ("double", 8), 4,
     "$x = $a*$b + $c*$d; $y = $b+$d"),
    ("loop24", ("x","a","b","c","d","y"), (), ("double", 8), 6,
     "$x = $a*$c - $b*$c; $y = $a*$d + $b+$c"),
    ("loop25", ("x","a","b","c","y"), ("u","v","w"), ("double", 8), 6,
     "$x = u*$b; $y = v*$b + w*$a + u*$c"),
    ("loop36", ("x","e"),(), ("double", 8), 1, "$x = exp($e)"),
# and loops with floats to test vectorization impact
    ("floop1", ("x","y"),(), ("float", 4), 1, "$x = sqrt($y)"),
    ("floop2", ("x","y"),("u"), ("float", 4), 1, "$x = $y/u"),
    ("floop3", ("x","y"), ("a"), ("float", 4), 2, "$y = $y + a*$x"),
    ("floop5", ("x","a","b"), (), ("float", 4), 1, "$x = $a+$b"),
    ("floop6", ("x","a","b"), (), ("float", 4), 1, "$x = $a*$b"),
    ("floop8", ("a","x"), ("u"), ("float", 4), 1, "$x = u/$a"),
    ("floop9", ("a","x"), (), ("float", 4), 1, "$x = $x+$a"),
    ("floop10", ("x","a","b","c"), ("u"), ("float", 4), 3, "$x = u+$a+$b+$c"),
    ("floop11", ("x","a","b","c","d"), (), ("float", 4), 3, "$x = $a+$b+$c+$d"),
    ("floop12", ("y","x","a","b","c","d"), ("u"), ("float", 4), 4,
     "$y = u+$a; $x = $a+$b+$c+$d"),
    ("floop13", ("y","x","a","b","c","d"), ("u"), ("float", 4), 4,
     "$x = $a+$b+$c+$d; $y = u+$d"),
    ("floop14", ("y","x","a","b"), (), ("float", 4), 2,
     "$x = $a+$b; $y = $a-$b"),
    ("floop15", ("x","a","b","c"), (), ("float", 4), 3, "$x = $c + $a*$b"),
    ("floop16", ("y","x","a","b","c"), ("u"), ("float", 4), 4,
     "$x = $a+$b+$c; $y = $x+$c+u"),
    ("floop17", ("x","a","b","c","d"), (), ("float", 4), 3,
     "$x = ($a+$b)*($c+$d)"),
    ("floop18", ("x","a","b"), ("u","v"), ("float", 4), 3, "$x = (u+$a)*(v+$b)"),
    ("floop19", ("y","x","a","b"), ("u","v"), ("float", 4), 2,
     "$x = u*$a; $y = v*$b"),
    ("floop21", ("x","a","b","c","d"), (), ("float", 4), 3,
     "$x = $a*$b + $c*$d"),
    ("floop22", ("x","a","b","c","d"), (), ("float", 4), 4,
     "$x = $x + $a*$b + $c*$d"),
    ("floop23", ("x","a","b","c","d","y"), (), ("float", 4), 4,
     "$x = $a*$b + $c*$d; $y = $b+$d"),
    ("floop24", ("x","a","b","c","d","y"), (), ("float", 4), 6,
     "$x = $a*$c - $b*$c; $y = $a*$d + $b+$c"),
    ("floop25", ("x","a","b","c","y"), ("u","v","w"), ("float", 4), 6,
     "$x = u*$b; $y = v*$b + w*$a + u*$c"),
    ("floop36", ("x","e"),(), ("float", 4), 1, "$x = exp($e)")
]

# handy access functions for readibility
def loopname(loop):
    return loop[0]
def looparrays(loop):
    return loop[1]
def loopscalars(loop):
    return loop[2]
def loopnumtype(loop):
    return loop[3]
def loopflops(loop):
    return loop[4]
def loopexpr(loop):
    return loop[5]

def cc(l):
    return reduce(lambda a,b: a+b, l, "")

def sub_skeleton(skeleton, subs):
    for s in subs:
        skeleton=skeleton.replace("#%s#"%s[0],s[1])
    return skeleton

def fortrandecls(loop):
    arrdecl=cc([", %s* %s"%(loopnumtype(loop)[0], n) for n in looparrays(loop)])
    scaldecl=cc([", const %s& %s"%(loopnumtype(loop)[0], n) for n in loopscalars(loop)])
    decl=cc(["  void %s_%s(const int& N%s%s);\n"%
             (loopname(loop),suffix,arrdecl,scaldecl)
             for suffix in ("f77","f77overhead","f90","f90overhead")])
    return decl

def declandfill(loop, declstub,datamember):
    decl=cc(["        %s;\n        initializeRandomDouble(%s%s, N);\n"%
             (declstub%n, n, datamember) for n in looparrays(loop)])
    return decl

def gencpp(loop):
    """Generate the C++ loop code from loop data by substituting the
    skeleton."""
    numtype=loopnumtype(loop)[0]
    
    subs=[
        ("loopname",loopname(loop)),
        ("LOOPNAME",loopname(loop).upper()),
        ("gentime",time.asctime(time.gmtime())),
        ("fortrandecls", fortrandecls(loop)),
        ("scalarargdecl", cc([", %s %s"%(loopnumtype(loop)[0], n)
                              for n in loopscalars(loop)])),
        ("arrayargs", cc([", %s"%n for n in looparrays(loop)])),
        ("scalarargs", cc([", %s"%n for n in loopscalars(loop)])),
        ("loopexpr", loopexpr(loop)),
        ("declarescalars",
         cc(["%s %s = 0.39123982498157938742;\n"%(numtype, n)
             for n in loopscalars(loop)])),
        ("arraydeclandfill",
         declandfill(loop, "Array<%s,1> %s(N)"%(numtype,"%s"),
                     ".dataFirst()")),
        ("tvdeclandfill",
         declandfill(loop, "TinyVector<%s,N> %s(N)"%(numtype,"%s"),
                     ".dataFirst()")),
        ("valarraydeclandfill",
         declandfill(loop, "valarray<%s> %s(N)"%(numtype,"%s"),""),""),
        ("carraydeclandfill",
         declandfill(loop, "%s* %s = new %s[N]"%(numtype, "%s", numtype),"")),
        ("delcarray",
         cc(["        delete [] %s;\n"%n for n in looparrays(loop)])),
        ("looparrayexpr", loopexpr(loop).replace("$",""))
        ]

    cpp =  sub_skeleton(cpp_skeleton, subs)
    f=open("%s.cpp"%loopname(loop),"w")
    f.write(cpp)

def genf77(loop):
    """Generate the fortran code from loop data."""

    f77expr = loopexpr(loop)
    for n in looparrays(loop):
        f77expr=f77expr.replace("$%s"%n,"%s(i)"%n)

    subs=[
        ("loopname",loopname(loop)),
        ("f77args", cc([", %s"%n for n in looparrays(loop)])+
         cc([", %s"%n for n in loopscalars(loop)])),
        ("f77decls", "%s(N)"%looparrays(loop)[0] +
         cc([", %s(N)"%n for n in looparrays(loop)[1:]])+
         cc([", %s"%n for n in loopscalars(loop)])),
        ("numtypesize",`loopnumtype(loop)[1]`),
        ("f77loopexpr", f77expr)
        ]

    f77 = sub_skeleton(f77_skeleton, subs)
    f=open("%sf.f"%loopname(loop),"w")
    f.write(f77)
    
def genf90(loop):
    """Generate the fortran code from loop data."""

    subs=[
        ("loopname",loopname(loop)),
        ("f77args", cc([", %s"%n for n in looparrays(loop)])+
         cc([", %s"%n for n in loopscalars(loop)])),
        ("f77decls", "%s(N)"%looparrays(loop)[0] +
         cc([", %s(N)"%n for n in looparrays(loop)[1:]])+
         cc([", %s"%n for n in loopscalars(loop)])),
        ("numtypesize",`loopnumtype(loop)[1]`),
        ("f90loopexpr",  loopexpr(loop).replace("$",""))
        ]

    f90 = sub_skeleton(f90_skeleton, subs)
    f=open("%sf90.f90"%loopname(loop),"w")
    f.write(f90)

cpp_skeleton = """
// #loopname# generated by makeloops.py #gentime#

#include <blitz/vector2.h>
#include <blitz/array.h>
#include <blitz/rand-uniform.h>
#include <blitz/benchext.h>

#ifdef BZ_HAVE_VALARRAY
 #define BENCHMARK_VALARRAY
#endif

#ifdef BENCHMARK_VALARRAY
#include <valarray>
#endif

BZ_NAMESPACE(blitz)
extern void sink();
BZ_NAMESPACE_END

BZ_USING_NAMESPACE(blitz)
BZ_USING_NAMESPACE(std)

#if defined(BZ_FORTRAN_SYMBOLS_WITH_TRAILING_UNDERSCORES)
 #define #loopname#_f77 #loopname#_f77_
 #define #loopname#_f77overhead #loopname#_f77overhead_
 #define #loopname#_f90 #loopname#_f90_
 #define #loopname#_f90overhead #loopname#_f90overhead_
#elif defined(BZ_FORTRAN_SYMBOLS_WITH_DOUBLE_TRAILING_UNDERSCORES)
 #define #loopname#_f77 #loopname#_f77__
 #define #loopname#_f77overhead #loopname#_f77overhead__
 #define #loopname#_f90 #loopname#_f90__
 #define #loopname#_f90overhead #loopname#_f90overhead__
#elif defined(BZ_FORTRAN_SYMBOLS_CAPS)
 #define #loopname#_f77 #LOOPNAME#_F77
 #define #loopname#_f77overhead #LOOPNAME#_F77OVERHEAD
 #define #loopname#_f90 #LOOPNAME#_F90
 #define #loopname#_f90overhead #LOOPNAME#_F90OVERHEAD
#endif

extern "C" {
#fortrandecls#
}

void VectorVersion(BenchmarkExt<int>& bench#scalarargdecl#);
void ArrayVersion(BenchmarkExt<int>& bench#scalarargdecl#);
void doTinyVectorVersion(BenchmarkExt<int>& bench#scalarargdecl#);
void F77Version(BenchmarkExt<int>& bench#scalarargdecl#);
#ifdef FORTRAN_90
void F90Version(BenchmarkExt<int>& bench#scalarargdecl#);
#endif
#ifdef BENCHMARK_VALARRAY
void ValarrayVersion(BenchmarkExt<int>& bench#scalarargdecl#);
#endif

const int numSizes = 20;
const int Nmax=1<<(numSizes-1);
const int tvNmax=7;

int main()
{
    int numBenchmarks = 5;
#ifndef BENCHMARK_VALARRAY
    numBenchmarks--;   // No  valarray
#endif
#ifndef FORTRAN_90
    numBenchmarks--;   // No fortran 90
#endif

    BenchmarkExt<int> bench("#loopname#: #loopexpr#", numBenchmarks);

    bench.setNumParameters(numSizes);

    Vector<int> parameters(numSizes);
    Vector<long> iters(numSizes);
    Vector<double> flops(numSizes);

    for (int i=0; i < numSizes; ++i)
    {
      parameters(i) = Nmax>>i;
      iters(i) = 50000000L / parameters(i);
	
        if (iters(i) < 2)
            iters(i) = 2;
        flops(i) = 2 * parameters(i);
    }

    bench.setParameterVector(parameters);
    bench.setIterations(iters);
    bench.setFlopsPerIteration(flops);

    bench.beginBenchmarking();

#declarescalars#

    //VectorVersion(bench #scalarargs#);
    ArrayVersion(bench #scalarargs#);
    doTinyVectorVersion(bench #scalarargs#);
    F77Version(bench #scalarargs#);
#ifdef FORTRAN_90
    F90Version(bench #scalarargs#);
#endif
#ifdef BENCHMARK_VALARRAY
    ValarrayVersion(bench #scalarargs#);
#endif

    bench.endBenchmarking();

    bench.saveMatlabGraph("#loopname#.m");
    return 0;
}

template<class T>
void initializeRandomDouble(T data, int numElements, int stride = 1)
{
    static Random<Uniform> rnd;

    for (int i=0; i < numElements; ++i)
        data[size_t(i*stride)] = rnd.random();
}

template<class T>
void initializeArray(T& array, int numElements)
{
    static Random<Uniform> rnd;

    for (size_t i=0; i < numElements; ++i)
        array[i] = rnd.random();
}

void ArrayVersion(BenchmarkExt<int>& bench#scalarargdecl#)
{
    bench.beginImplementation("Array<T,1>");

    while (!bench.doneImplementationBenchmark())
    {
        int N = bench.getParameter();
        long iters = bench.getIterations();

        cout << "Array<T,1>: N = " << N << endl;

#arraydeclandfill#

        bench.start();
        for (long i=0; i < iters; ++i)
        {
            #looparrayexpr#;
            sink();
        }
        bench.stop();

        bench.startOverhead();
        for (long i=0; i < iters; ++i) {
            sink();
	}

        bench.stopOverhead();
    }

    bench.endImplementation();
}
  

template<int N>
void TinyVectorVersion(BenchmarkExt<int>& bench#scalarargdecl#)
{
        cout << "Tinyvector<T, " << N << ">" << endl;
        const int sz = bench.getParameter();
        assert(N==sz);
                           
        long iters = bench.getIterations();

#tvdeclandfill#

        bench.start();
        for (long i=0; i < iters; ++i)
        {
            #looparrayexpr#;
            sink();
        }
        bench.stop();

        bench.startOverhead();
        for (long i=0; i < iters; ++i) {
            sink();
	}
        bench.stopOverhead();

	TinyVectorVersion<N>>1>(bench#scalarargs#);
}

// end recursion
template<>
void TinyVectorVersion<0>(BenchmarkExt<int>& bench#scalarargdecl#)
{}

void doTinyVectorVersion(BenchmarkExt<int>& bench#scalarargdecl#)
{
  bench.beginImplementation("TinyVector<T>");
  // can't run tinyvector with full length because meta-unrolling
  // kills compiler...
  int N=Nmax;
  while(N> 1<<tvNmax) {
   bench.getParameter();
   bench.getIterations();
   bench.skip();
   N>>=1;
  }

  TinyVectorVersion< 1<<tvNmax >(bench#scalarargs#);
  bench.endImplementation();
}


#ifdef BENCHMARK_VALARRAY
void ValarrayVersion(BenchmarkExt<int>& bench#scalarargdecl#)
{
    bench.beginImplementation("valarray<T>");

    while (!bench.doneImplementationBenchmark())
    {
        int N = bench.getParameter();
        cout << "valarray<T>: N = " << N << endl;

        long iters = bench.getIterations();

#valarraydeclandfill#

        bench.start();
        for (long i=0; i < iters; ++i)
        {
            #looparrayexpr#;
            sink();
        }
        bench.stop();

        bench.startOverhead();
        for (long i=0; i < iters; ++i) {
	  sink();
	}
        bench.stopOverhead();
    }

    bench.endImplementation();
}
#endif

void F77Version(BenchmarkExt<int>& bench#scalarargdecl#)
{
    bench.beginImplementation("Fortran 77");

    while (!bench.doneImplementationBenchmark())
    {
        int N = bench.getParameter();
        cout << "Fortran 77: N = " << N << endl;

        int iters = bench.getIterations();

#carraydeclandfill#        

        bench.start();
        for (int iter=0; iter < iters; ++iter)
            #loopname#_f77(N#arrayargs##scalarargs#);
        bench.stop();

        bench.startOverhead();
        for (int iter=0; iter < iters; ++iter)
            #loopname#_f77overhead(N#arrayargs##scalarargs#);

        bench.stopOverhead();

#delcarray#
    }

    bench.endImplementation();
}

#ifdef FORTRAN_90
void F90Version(BenchmarkExt<int>& bench#scalarargdecl#)
{
    bench.beginImplementation("Fortran 90");

    while (!bench.doneImplementationBenchmark())
    {
        int N = bench.getParameter();
        cout << "Fortran 90: N = " << N << endl;

        int iters = bench.getIterations();

#carraydeclandfill#

        bench.start();
        for (int iter=0; iter < iters; ++iter)
            #loopname#_f90(N#arrayargs##scalarargs#);
        bench.stop();

        bench.startOverhead();
        for (int iter=0; iter < iters; ++iter)
            #loopname#_f90overhead(N#arrayargs##scalarargs#);

        bench.stopOverhead();
#delcarray#
    }

    bench.endImplementation();
}
#endif

"""

f77_skeleton = """
      SUBROUTINE #loopname#_F77(N#f77args#)
      INTEGER i, N
      REAL*#numtypesize# #f77decls#

      DO i=1,N
          #f77loopexpr#
      END DO
      RETURN
      END


      SUBROUTINE #loopname#_F77Overhead(N#f77args#)
      INTEGER i, N
      REAL*#numtypesize# #f77decls#
      RETURN
      END
"""

f90_skeleton = """
      SUBROUTINE #loopname#_F90(N, x, y, a)
      INTEGER i, N
      REAL*#numtypesize# #f77decls#

      #f90loopexpr#
      RETURN
      END


      SUBROUTINE #loopname#_F90Overhead(N, x, y, a)
      INTEGER i, N
      REAL*#numtypesize# #f77decls#

      RETURN
      END
"""

for l in loops:
    print "generating code for %s"%loopname(l)
    gencpp(l)
    genf77(l)
    genf90(l)

