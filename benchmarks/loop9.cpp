// Generated code (makeloops.cpp) -- do not edit.

// In KAI C++ 3.2, restrict causes problems for copy propagation.
// Temporary fix: disable restrict

#define BZ_DISABLE_RESTRICT

#include <blitz/vector.h>
#include <blitz/array.h>
#include <blitz/rand-uniform.h>
#include <blitz/benchext.h>

// Generated: makeloops.cpp Jul 30 1998

#ifdef BENCHMARK_VALARRAY
#include <valarray>
#endif

BZ_USING_NAMESPACE(blitz)

#ifdef BZ_FORTRAN_SYMBOLS_WITH_TRAILING_UNDERSCORES
 #define loop9_f77 loop9_f77_
 #define loop9_f77overhead loop9_f77overhead_
 #define loop9_f90 loop9_f90_
 #define loop9_f90overhead loop9_f90overhead_
#endif

#ifdef BZ_FORTRAN_SYMBOLS_WITH_DOUBLE_TRAILING_UNDERSCORES
 #define loop9_f77 loop9_f77__
 #define loop9_f77overhead loop9_f77overhead__
 #define loop9_f90 loop9_f90__
 #define loop9_f90overhead loop9_f90overhead__
#endif

#ifdef BZ_FORTRAN_SYMBOLS_CAPS
 #define loop9_f77 LOOP9_F77
 #define loop9_f77overhead LOOP9_F77OVERHEAD
 #define loop9_f90 LOOP9_F90
 #define loop9_f90overhead LOOP9_F90OVERHEAD
#endif

extern "C" {
  void loop9_f77(const int& N, double* a, double* x);

  void loop9_f77overhead(const int& N, double* a, double* x);

  void loop9_f90(const int& N, double* a, double* x);

  void loop9_f90overhead(const int& N, double* a, double* x);

}

void VectorVersion(BenchmarkExt<int>& bench);
void ArrayVersion(BenchmarkExt<int>& bench);
void F77Version(BenchmarkExt<int>& bench);
void F90Version(BenchmarkExt<int>& bench);

#ifdef BENCHMARK_VALARRAY
void ValarrayVersion(BenchmarkExt<int>& bench);
#endif

void sink() {}

int main()
{
#ifdef BENCHMARK_VALARRAY
    int numBenchmarks = 5;
#else
    int numBenchmarks = 4;
#endif

    BenchmarkExt<int> bench("loop9: $x=$x+$a", numBenchmarks);

    const int numSizes = 23;
    bench.setNumParameters(numSizes);
    bench.setRateDescription("Mflops/s");

    Vector<int> parameters(numSizes);
    Vector<long> iters(numSizes);
    Vector<double> flops(numSizes);

    for (int i=0; i < numSizes; ++i)
    {
        parameters[i] = (int)pow(10.0, (i+1)/4.0);
        iters[i] = 10000000L / parameters[i];
        if (iters[i] < 2)
            iters[i] = 2;
        flops[i] = 1 * parameters[i];
    }

    bench.setParameterVector(parameters);
    bench.setIterations(iters);
    bench.setFlopsPerIteration(flops);

    bench.beginBenchmarking();


    VectorVersion(bench);
    ArrayVersion(bench);
    F77Version(bench);
    F90Version(bench);
#ifdef BENCHMARK_VALARRAY
    ValarrayVersion(bench);
#endif

    bench.endBenchmarking();

    bench.saveMatlabGraph("loop9.m");

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

void VectorVersion(BenchmarkExt<int>& bench)
{
    bench.beginImplementation("Vector<T>");

    while (!bench.doneImplementationBenchmark())
    {
        int N = bench.getParameter();
        cout << "Vector<T>: N = " << N << endl;
        cout.flush();

        long iters = bench.getIterations();

        Vector<double> a(N);
        initializeRandomDouble(a.data(), N);
        Vector<double> x(N);
        initializeRandomDouble(x.data(), N);

        bench.start();
        for (long i=0; i < iters; ++i)
        {
            x=x+a;
            sink();
        }
        bench.stop();

        bench.startOverhead();
        for (long i=0; i < iters; ++i)
            sink();
        bench.stopOverhead();
    }

    bench.endImplementation();
}

void ArrayVersion(BenchmarkExt<int>& bench)
{
    bench.beginImplementation("Array<T,1>");

    while (!bench.doneImplementationBenchmark())
    {
        int N = bench.getParameter();
        cout << "Array<T,1>: N = " << N << endl;
        cout.flush();

        long iters = bench.getIterations();

        Array<double, 1> a(N);
        initializeRandomDouble(a.dataFirst(), N);
        Array<double, 1> x(N);
        initializeRandomDouble(x.dataFirst(), N);

        bench.start();
        for (long i=0; i < iters; ++i)
        {
            x=x+a;
            sink();
        }
        bench.stop();

        bench.startOverhead();
        for (long i=0; i < iters; ++i)
            sink();
        bench.stopOverhead();
    }

    bench.endImplementation();
}

#ifdef BENCHMARK_VALARRAY
void ValarrayVersion(BenchmarkExt<int>& bench)
{
    bench.beginImplementation("valarray<T>");

    while (!bench.doneImplementationBenchmark())
    {
        int N = bench.getParameter();
        cout << "valarray<T>: N = " << N << endl;
        cout.flush();

        long iters = bench.getIterations();

        valarray<double> a(N);
        initializeArray(a, N);
        valarray<double> x(N);
        initializeArray(x, N);

        bench.start();
        for (long i=0; i < iters; ++i)
        {
            x=x+a;
            sink();
        }
        bench.stop();

        bench.startOverhead();
        for (long i=0; i < iters; ++i)
            sink();
        bench.stopOverhead();
    }

    bench.endImplementation();
}

#endif
void F77Version(BenchmarkExt<int>& bench)
{
    bench.beginImplementation("Fortran 77");

    while (!bench.doneImplementationBenchmark())
    {
        int N = bench.getParameter();

        cout << "Fortran 77: N = " << N << endl;
        cout.flush();

        int iters = bench.getIterations();

        double* a = new double[N];
        initializeRandomDouble(a, N);
        double* x = new double[N];
        initializeRandomDouble(x, N);

        bench.start();
        for (int iter=0; iter < iters; ++iter)
            loop9_f77(N, a, x);
        bench.stop();

        bench.startOverhead();
        for (int iter=0; iter < iters; ++iter)
            loop9_f77overhead(N, a, x);

        bench.stopOverhead();
        delete [] a;
        delete [] x;
    }

    bench.endImplementation();
}

void F90Version(BenchmarkExt<int>& bench)
{
    bench.beginImplementation("Fortran 90");

    while (!bench.doneImplementationBenchmark())
    {
        int N = bench.getParameter();

        cout << "Fortran 90: N = " << N << endl;
        cout.flush();

        int iters = bench.getIterations();

        double* a = new double[N];
        initializeRandomDouble(a, N);
        double* x = new double[N];
        initializeRandomDouble(x, N);

        bench.start();
        for (int iter=0; iter < iters; ++iter)
            loop9_f90(N, a, x);
        bench.stop();

        bench.startOverhead();
        for (int iter=0; iter < iters; ++iter)
            loop9_f90overhead(N, a, x);

        bench.stopOverhead();
        delete [] a;
        delete [] x;
    }

    bench.endImplementation();
}

