// Array stencil benchmark

#include <blitz/array.h>
#include <blitz/benchext.h>
#include <blitz/rand-uniform.h>

BZ_USING_NAMESPACE(blitz)

#ifdef BZ_FORTRAN_SYMBOLS_WITH_TRAILING_UNDERSCORES
  #define stencilf stencilf_
  #define stencilftiled stencilftiled_
  #define stencilf90 stencilf90_
#endif

#ifdef BZ_FORTRAN_SYMBOLS_CAPS
  #define stencilf       STENCILF
  #define stencilftiled  STENCILFTILED
  #define stencilf90     STENCILF90
#endif

extern "C" {
    void stencilf(double* A, double* B, int& N, int& iters);
    void stencilftiled(double* A, double* B, int& N, int& iters);
    void stencilf90(double* A, double* B, int& N, int& iters);
}

void stencilFortran90Version(BenchmarkExt<int>& bench);
void stencilFortran77Version(BenchmarkExt<int>& bench);
void stencilFortran77VersionTiled(BenchmarkExt<int>& bench);
void stencilBlitzVersion(BenchmarkExt<int>& bench);

int main()
{
    BenchmarkExt<int> bench("Array stencil", 4);

    const int numSizes = 16;

    bench.setNumParameters(numSizes);
    bench.setRateDescription("Mflops/s");

    Vector<int> parameters(numSizes);
    Vector<long> iters(numSizes);
    Vector<double> flops(numSizes);

    for (int i=0; i < numSizes; ++i)
    {
        parameters[i] = (i+1) * 8;
        iters[i] = 32*8*8*8/(i+1)/(i+1)/(i+1)/4;
        if (iters[i] < 2)
            iters[i] = 2;
        int npoints = parameters[i] - 2;
        flops[i] = npoints * npoints * npoints * 7 * 2;
    }

    bench.setParameterVector(parameters);
    bench.setIterations(iters);
    bench.setFlopsPerIteration(flops);

    bench.beginBenchmarking();
    stencilFortran90Version(bench);
    stencilBlitzVersion(bench);
    stencilFortran77Version(bench);
    stencilFortran77VersionTiled(bench);
    bench.endBenchmarking();

    bench.saveMatlabGraph("stencil.m");

    return 0;
}

void initializeRandomDouble(double* data, int numElements, int stride = 1)
{
    static Random<Uniform> rnd;

    for (int i=0; i < numElements; ++i)
        data[i*stride] = rnd.random();
}

void stencilBlitzVersion(BenchmarkExt<int>& bench)
{
    bench.beginImplementation("Blitz++");

    while (!bench.doneImplementationBenchmark())
    {
        int N = bench.getParameter();

        cout << "Blitz++: N = " << N << endl;
        cout.flush();

        long iters = bench.getIterations();

        Array<double,3> A(N,N,N), B(N,N,N);
        initializeRandomDouble(A.data(), N*N*N, A.stride(thirdDim));
        initializeRandomDouble(B.data(), N*N*N, B.stride(thirdDim));
        TinyVector<int,2> size = N-2;
        generateFastTraversalOrder(size);
        double c = 1/7.;
       
        bench.start();
        for (long i=0; i < iters; ++i)
        {
            Range I(1,N-2), J(1,N-2), K(1,N-2);

            A(I,J,K) = c * (B(I,J,K) + B(I+1,J,K) + B(I-1,J,K) + B(I,J+1,K)
                + B(I,J-1,K) + B(I,J,K+1) + B(I,J,K-1));

            B(I,J,K) = c * (A(I,J,K) + A(I+1,J,K) + A(I-1,J,K) + A(I,J+1,K)
                + A(I,J-1,K) + A(I,J,K+1) + A(I,J,K-1));
        }
        bench.stop();
    }

    bench.endImplementation();
}

void stencilFortran77Version(BenchmarkExt<int>& bench)
{
    bench.beginImplementation("Fortran 77");

    while (!bench.doneImplementationBenchmark())
    {
        int N = bench.getParameter();

        cout << "Fortran 77: N = " << N << endl;
        cout.flush();

        int iters = (int)bench.getIterations();

        size_t arraySize = size_t(N) * size_t(N) * N;
       
        double* A = new double[arraySize];
        double* B = new double[arraySize];

        initializeRandomDouble(A, arraySize);
        initializeRandomDouble(B, arraySize);

        bench.start();
        stencilf(A, B, N, iters);
        bench.stop();

        delete [] A;
        delete [] B;
    }

    bench.endImplementation();
}

void stencilFortran77VersionTiled(BenchmarkExt<int>& bench)
{
    bench.beginImplementation("Fortran 77 (tiled)");

    while (!bench.doneImplementationBenchmark())
    {
        int N = bench.getParameter();

        cout << "Fortran 77: N = " << N << endl;
        cout.flush();

        int iters = (int)bench.getIterations();

        size_t arraySize = size_t(N) * size_t(N) * N;

        double* A = new double[arraySize];
        double* B = new double[arraySize];

        initializeRandomDouble(A, arraySize);
        initializeRandomDouble(B, arraySize);

        bench.start();
        stencilftiled(A, B, N, iters);
        bench.stop();

        delete [] A;
        delete [] B;
    }

    bench.endImplementation();
}

void stencilFortran90Version(BenchmarkExt<int>& bench)
{
   bench.beginImplementation("Fortran 90");

    while (!bench.doneImplementationBenchmark())
    {
        int N = bench.getParameter();

        cout << "Fortran 90: N = " << N << endl;
        cout.flush();

        int iters = (int)bench.getIterations();

        size_t arraySize = size_t(N) * size_t(N) * N;

        double* A = new double[arraySize];
        double* B = new double[arraySize];

        initializeRandomDouble(A, arraySize);
        initializeRandomDouble(B, arraySize);

        bench.start();
        stencilf90(A, B, N, iters);
        bench.stop();

        delete [] A;
        delete [] B;
    }

    bench.endImplementation();
}

