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
 #define loop17_f77 loop17_f77_
 #define loop17_f77overhead loop17_f77overhead_
 #define loop17_f90 loop17_f90_
 #define loop17_f90overhead loop17_f90overhead_
#endif

#ifdef BZ_FORTRAN_SYMBOLS_WITH_DOUBLE_TRAILING_UNDERSCORES
 #define loop17_f77 loop17_f77__
 #define loop17_f77overhead loop17_f77overhead__
 #define loop17_f90 loop17_f90__
 #define loop17_f90overhead loop17_f90overhead__
#endif

#ifdef BZ_FORTRAN_SYMBOLS_CAPS
 #define loop17_f77 LOOP17_F77
 #define loop17_f77overhead LOOP17_F77OVERHEAD
 #define loop17_f90 LOOP17_F90
 #define loop17_f90overhead LOOP17_F90OVERHEAD
#endif

extern "C" {
  void loop17_f77(const int& N, double* x, double* a, double* b, double* c, double* d);

  void loop17_f77overhead(const int& N, double* x, double* a, double* b, double* c, double* d);

  void loop17_f90(const int& N, double* x, double* a, double* b, double* c, double* d);

  void loop17_f90overhead(const int& N, double* x, double* a, double* b, double* c, double* d);

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

    BenchmarkExt<int> bench("loop17: $x=($a+$b)*($c+$d)", numBenchmarks);

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
        flops[i] = 3 * parameters[i];
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

    bench.saveMatlabGraph("loop17.m");

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

        Vector<double> x(N);
        initializeRandomDouble(x.data(), N);
        Vector<double> a(N);
        initializeRandomDouble(a.data(), N);
        Vector<double> b(N);
        initializeRandomDouble(b.data(), N);
        Vector<double> c(N);
        initializeRandomDouble(c.data(), N);
        Vector<double> d(N);
        initializeRandomDouble(d.data(), N);

        bench.start();
        for (long i=0; i < iters; ++i)
        {
            x=(a+b)*(c+d);
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

        Array<double, 1> x(N);
        initializeRandomDouble(x.dataFirst(), N);
        Array<double, 1> a(N);
        initializeRandomDouble(a.dataFirst(), N);
        Array<double, 1> b(N);
        initializeRandomDouble(b.dataFirst(), N);
        Array<double, 1> c(N);
        initializeRandomDouble(c.dataFirst(), N);
        Array<double, 1> d(N);
        initializeRandomDouble(d.dataFirst(), N);

        bench.start();
        for (long i=0; i < iters; ++i)
        {
            x=(a+b)*(c+d);
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

        valarray<double> x(N);
        initializeArray(x, N);
        valarray<double> a(N);
        initializeArray(a, N);
        valarray<double> b(N);
        initializeArray(b, N);
        valarray<double> c(N);
        initializeArray(c, N);
        valarray<double> d(N);
        initializeArray(d, N);

        bench.start();
        for (long i=0; i < iters; ++i)
        {
            x=(a+b)*(c+d);
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

        double* x = new double[N];
        initializeRandomDouble(x, N);
        double* a = new double[N];
        initializeRandomDouble(a, N);
        double* b = new double[N];
        initializeRandomDouble(b, N);
        double* c = new double[N];
        initializeRandomDouble(c, N);
        double* d = new double[N];
        initializeRandomDouble(d, N);

        bench.start();
        for (int iter=0; iter < iters; ++iter)
            loop17_f77(N, x, a, b, c, d);
        bench.stop();

        bench.startOverhead();
        for (int iter=0; iter < iters; ++iter)
            loop17_f77overhead(N, x, a, b, c, d);

        bench.stopOverhead();
        delete [] x;
        delete [] a;
        delete [] b;
        delete [] c;
        delete [] d;
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

        double* x = new double[N];
        initializeRandomDouble(x, N);
        double* a = new double[N];
        initializeRandomDouble(a, N);
        double* b = new double[N];
        initializeRandomDouble(b, N);
        double* c = new double[N];
        initializeRandomDouble(c, N);
        double* d = new double[N];
        initializeRandomDouble(d, N);

        bench.start();
        for (int iter=0; iter < iters; ++iter)
            loop17_f90(N, x, a, b, c, d);
        bench.stop();

        bench.startOverhead();
        for (int iter=0; iter < iters; ++iter)
            loop17_f90overhead(N, x, a, b, c, d);

        bench.stopOverhead();
        delete [] x;
        delete [] a;
        delete [] b;
        delete [] c;
        delete [] d;
    }

    bench.endImplementation();
}

