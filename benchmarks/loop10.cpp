// Generated code (makeloops.cpp) -- do not edit.

// In KAI C++ 3.2, restrict causes problems for copy propagation.
// Temporary fix: disable restrict

#define BZ_DISABLE_RESTRICT

#include <blitz/vector.h>
#include <blitz/array.h>
#include <blitz/rand-uniform.h>
#include <blitz/benchext.h>

// Generated: makeloops.cpp Dec 11 2002

#ifdef BZ_HAVE_VALARRAY
 #define BENCHMARK_VALARRAY
#endif

#ifdef BENCHMARK_VALARRAY
#include <valarray>
#endif

BZ_USING_NAMESPACE(blitz)

#if defined(BZ_FORTRAN_SYMBOLS_WITH_TRAILING_UNDERSCORES)
 #define loop10_f77 loop10_f77_
 #define loop10_f77overhead loop10_f77overhead_
 #define loop10_f90 loop10_f90_
 #define loop10_f90overhead loop10_f90overhead_
#elif defined(BZ_FORTRAN_SYMBOLS_WITH_DOUBLE_TRAILING_UNDERSCORES)
 #define loop10_f77 loop10_f77__
 #define loop10_f77overhead loop10_f77overhead__
 #define loop10_f90 loop10_f90__
 #define loop10_f90overhead loop10_f90overhead__
#elif defined(BZ_FORTRAN_SYMBOLS_CAPS)
 #define loop10_f77 LOOP10_F77
 #define loop10_f77overhead LOOP10_F77OVERHEAD
 #define loop10_f90 LOOP10_F90
 #define loop10_f90overhead LOOP10_F90OVERHEAD
#endif

extern "C" {
  void loop10_f77(const int& N, double* x, double* a, double* b, double* c, const double& u);

  void loop10_f77overhead(const int& N, double* x, double* a, double* b, double* c, const double& u);

  void loop10_f90(const int& N, double* x, double* a, double* b, double* c, const double& u);

  void loop10_f90overhead(const int& N, double* x, double* a, double* b, double* c, const double& u);

}

void VectorVersion(BenchmarkExt<int>& bench, double u);
void ArrayVersion(BenchmarkExt<int>& bench, double u);
void F77Version(BenchmarkExt<int>& bench, double u);
#ifdef FORTRAN_90
void F90Version(BenchmarkExt<int>& bench, double u);
#endif
#ifdef BENCHMARK_VALARRAY
void ValarrayVersion(BenchmarkExt<int>& bench, double u);
#endif

void sink() {}

int main()
{
    int numBenchmarks = 5;
#ifndef BENCHMARK_VALARRAY
    numBenchmarks--;   // No  valarray
#endif
#ifndef FORTRAN_90
    numBenchmarks--;   // No fortran 90
#endif

    BenchmarkExt<int> bench("loop10: $x=u+$a+$b+$c", numBenchmarks);

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

    double u = 0.39123982498157938742;

    VectorVersion(bench, u);
    ArrayVersion(bench, u);
    F77Version(bench, u);
#ifdef FORTRAN_90
    F90Version(bench, u);
#endif
#ifdef BENCHMARK_VALARRAY
    ValarrayVersion(bench, u);
#endif

    bench.endBenchmarking();

    bench.saveMatlabGraph("loop10.m");

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

void VectorVersion(BenchmarkExt<int>& bench, double u)
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

        bench.start();
        for (long i=0; i < iters; ++i)
        {
            x=u+a+b+c;
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

void ArrayVersion(BenchmarkExt<int>& bench, double u)
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

        bench.start();
        for (long i=0; i < iters; ++i)
        {
            x=u+a+b+c;
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
void ValarrayVersion(BenchmarkExt<int>& bench, double u)
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

        bench.start();
        for (long i=0; i < iters; ++i)
        {
            x=u+a+b+c;
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
void F77Version(BenchmarkExt<int>& bench, double u)
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

        bench.start();
        for (int iter=0; iter < iters; ++iter)
            loop10_f77(N, x, a, b, c, u);
        bench.stop();

        bench.startOverhead();
        for (int iter=0; iter < iters; ++iter)
            loop10_f77overhead(N, x, a, b, c, u);

        bench.stopOverhead();
        delete [] x;
        delete [] a;
        delete [] b;
        delete [] c;
    }

    bench.endImplementation();
}

#ifdef FORTRAN_90
void F90Version(BenchmarkExt<int>& bench, double u)
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

        bench.start();
        for (int iter=0; iter < iters; ++iter)
            loop10_f90(N, x, a, b, c, u);
        bench.stop();

        bench.startOverhead();
        for (int iter=0; iter < iters; ++iter)
            loop10_f90overhead(N, x, a, b, c, u);

        bench.stopOverhead();
        delete [] x;
        delete [] a;
        delete [] b;
        delete [] c;
    }

    bench.endImplementation();
}
#endif

