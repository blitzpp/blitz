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
 #define loop16_f77 loop16_f77_
 #define loop16_f77overhead loop16_f77overhead_
 #define loop16_f90 loop16_f90_
 #define loop16_f90overhead loop16_f90overhead_
#endif

#ifdef BZ_FORTRAN_SYMBOLS_WITH_DOUBLE_TRAILING_UNDERSCORES
 #define loop16_f77 loop16_f77__
 #define loop16_f77overhead loop16_f77overhead__
 #define loop16_f90 loop16_f90__
 #define loop16_f90overhead loop16_f90overhead__
#endif

#ifdef BZ_FORTRAN_SYMBOLS_CAPS
 #define loop16_f77 LOOP16_F77
 #define loop16_f77overhead LOOP16_F77OVERHEAD
 #define loop16_f90 LOOP16_F90
 #define loop16_f90overhead LOOP16_F90OVERHEAD
#endif

extern "C" {
  void loop16_f77(const int& N, double* x, double* a, double* b, double* c, double* y, const double& u);

  void loop16_f77overhead(const int& N, double* x, double* a, double* b, double* c, double* y, const double& u);

  void loop16_f90(const int& N, double* x, double* a, double* b, double* c, double* y, const double& u);

  void loop16_f90overhead(const int& N, double* x, double* a, double* b, double* c, double* y, const double& u);

}

void VectorVersion(BenchmarkExt<int>& bench, double u);
void ArrayVersion(BenchmarkExt<int>& bench, double u);
void F77Version(BenchmarkExt<int>& bench, double u);
void F90Version(BenchmarkExt<int>& bench, double u);

#ifdef BENCHMARK_VALARRAY
void ValarrayVersion(BenchmarkExt<int>& bench, double u);
#endif

void sink() {}

int main()
{
#ifdef BENCHMARK_VALARRAY
    int numBenchmarks = 5;
#else
    int numBenchmarks = 4;
#endif

    BenchmarkExt<int> bench("loop16: $x=$a+$b+$c;$y=$x+$c+u", numBenchmarks);

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
        flops[i] = 4 * parameters[i];
    }

    bench.setParameterVector(parameters);
    bench.setIterations(iters);
    bench.setFlopsPerIteration(flops);

    bench.beginBenchmarking();

    double u = 0.39123982498157938742;

    VectorVersion(bench, u);
    ArrayVersion(bench, u);
    F77Version(bench, u);
    F90Version(bench, u);
#ifdef BENCHMARK_VALARRAY
    ValarrayVersion(bench, u);
#endif

    bench.endBenchmarking();

    bench.saveMatlabGraph("loop16.m");

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
        Vector<double> y(N);
        initializeRandomDouble(y.data(), N);

        bench.start();
        for (long i=0; i < iters; ++i)
        {
            x=a+b+c;y=x+c+u;
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
        Array<double, 1> y(N);
        initializeRandomDouble(y.dataFirst(), N);

        bench.start();
        for (long i=0; i < iters; ++i)
        {
            x=a+b+c;y=x+c+u;
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
        valarray<double> y(N);
        initializeArray(y, N);

        bench.start();
        for (long i=0; i < iters; ++i)
        {
            x=a+b+c;y=x+c+u;
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
        double* y = new double[N];
        initializeRandomDouble(y, N);

        bench.start();
        for (int iter=0; iter < iters; ++iter)
            loop16_f77(N, x, a, b, c, y, u);
        bench.stop();

        bench.startOverhead();
        for (int iter=0; iter < iters; ++iter)
            loop16_f77overhead(N, x, a, b, c, y, u);

        bench.stopOverhead();
        delete [] x;
        delete [] a;
        delete [] b;
        delete [] c;
        delete [] y;
    }

    bench.endImplementation();
}

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
        double* y = new double[N];
        initializeRandomDouble(y, N);

        bench.start();
        for (int iter=0; iter < iters; ++iter)
            loop16_f90(N, x, a, b, c, y, u);
        bench.stop();

        bench.startOverhead();
        for (int iter=0; iter < iters; ++iter)
            loop16_f90overhead(N, x, a, b, c, y, u);

        bench.stopOverhead();
        delete [] x;
        delete [] a;
        delete [] b;
        delete [] c;
        delete [] y;
    }

    bench.endImplementation();
}

