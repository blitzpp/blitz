#define BZ_DISABLE_RESTRICT
#define BZ_ARRAY_2D_NEW_STENCIL_TILING

#include <blitz/array.h>
#include <blitz/timer.h>

#ifdef BZ_HAVE_STD
  #include <fstream>
#else
  #include <fstream.h>
#endif

BZ_USING_NAMESPACE(blitz)

#if defined(BZ_FORTRAN_SYMBOLS_WITH_TRAILING_UNDERSCORES)
 #define echo_f90           echo_f90_
 #define echo_f77           echo_f77_
 #define echo_f90_tuned     echo_f90_tuned_
 #define echo_f77tuned      echo_f77tuned_
#elif defined(BZ_FORTRAN_SYMBOLS_WITH_DOUBLE_TRAILING_UNDERSCORES)
 #define echo_f90           echo_f90__
 #define echo_f77           echo_f77__
 #define echo_f90_tuned     echo_f90_tuned__
 #define echo_f77tuned      echo_f77tuned__
#elif defined(BZ_FORTRAN_SYMBOLS_CAPS)
 #define echo_f90           ECHO_F90
 #define echo_f77           ECHO_F77
 #define echo_f90_tuned     ECHO_F90_TUNED
 #define echo_f77tuned      ECHO_F77TUNED
#endif

extern "C" {
void echo_f90(int& N, int& niters, float& check);
void echo_f77(int& N, int& niters, float& check);
void echo_f90_tuned(int& N, int& niters, float& check);
void echo_f77tuned(int& N, int& niters, float& check);
}

float echo_BlitzInterlacedCycled(int N, int niters);
float echo_BlitzCycled(int N, int niters);
float echo_BlitzRaw(int N, int niters);
float echo_BlitzStencil(int N, int niters);

int main()
{
    Timer timer;
    int N = 650;
    int niters = 60;
    float check;

    cout << "Acoustic 2D Benchmark" << endl << endl;

    double Mflops = (N-2)*(N-2) * 9.0 * niters / 1.0e+6;

    timer.start();
    check = echo_BlitzRaw(N, niters);
    timer.stop();
    cout << "Blitz++ (raw):    " << timer.elapsedSeconds() << " s  check = " 
         << check << " Mflops = " << (Mflops/timer.elapsedSeconds())
         << endl << endl;

    timer.start();
    check = echo_BlitzStencil(N, niters);
    timer.stop();
    cout << "Blitz++ (stencil):    " << timer.elapsedSeconds() << " s  check = "
         << check << " Mflops = " << (Mflops/timer.elapsedSeconds())
         << endl << endl;

#if 0
    timer.start();
    check = echo_BlitzInterlaced(N, niters, c);
    timer.stop();
    cout << "Blitz++ (interlaced):    " << timer.elapsedSeconds() << " s  check = "
         << check << " Mflops = " << (Mflops/timer.elapsedSeconds())
         << endl << endl;
#endif

    timer.start();
    check = echo_BlitzCycled(N, niters);
    timer.stop();
    cout << "Blitz++ (cycled): " << timer.elapsedSeconds() << " s check = "
         << check << " Mflops = " << (Mflops/timer.elapsedSeconds())
         << endl << endl;
    
    timer.start();
    check = echo_BlitzInterlacedCycled(N, niters);
    timer.stop();
    cout << "Blitz++ (interlaced & cycled): " << timer.elapsedSeconds()
         << " s check = " << check 
         << " Mflops = " << (Mflops/timer.elapsedSeconds()) 
				 << endl << endl;

#ifdef FORTRAN_90
    timer.start();
    echo_f90(N, niters, check);
    timer.stop();
    cout << "Fortran 90: " << timer.elapsedSeconds() << " s  check = "
         << check << " Mflops = " << (Mflops/timer.elapsedSeconds()) 
         << endl << endl;

    timer.start();
    echo_f90_tuned(N, niters, check);
    timer.stop();
    cout << "Fortran 90 (tuned): " << timer.elapsedSeconds() << " s  check = "
         << check << " Mflops = " << (Mflops/timer.elapsedSeconds())
         << endl << endl;
#endif

    timer.start();
    echo_f77(N, niters, check);
    timer.stop();
    cout << "Fortran 77: " << timer.elapsedSeconds() << " s  check = "
         << check << " Mflops = " << (Mflops/timer.elapsedSeconds())
         << endl << endl;

    timer.start();
    echo_f77tuned(N, niters, check);
    timer.stop();
    cout << "Fortran 77 (tuned): " << timer.elapsedSeconds() << " s  check = "
         << check << " Mflops = " << (Mflops/timer.elapsedSeconds())
         << endl << endl;

    return 0;
}

void checkArray(Array<float,2>& A, int N)
{
    float check = 0.0;
    for (int i=0; i < N; ++i)
        for (int j=0; j < N; ++j)
            check += ((i+1)*N + j + 1) * A(i,j);

    cout << "Array check: " << check << endl;
}

void setInitialConditions(Array<float,2>& c, Array<float,2>& P1, 
    Array<float,2>& P2, Array<float,2>& P3, int N);


float echo_BlitzRaw(int N, int niters)
{
    Array<float,2> P1(N,N), P2(N,N), P3(N,N), c(N,N);
    Range I(1,N-2), J(1,N-2);

    setInitialConditions(c, P1, P2, P3, N);
    checkArray(P2, N);
    checkArray(c, N);

    for (int iter=0; iter < niters; ++iter)
    {
        P3(I,J) = (2-4*c(I,J)) * P2(I,J)
          + c(I,J)*(P2(I-1,J) + P2(I+1,J) + P2(I,J-1) + P2(I,J+1))
          - P1(I,J);

        P1 = P2;
        P2 = P3;
    }

#if 0
ofstream ofs("testecho.m");
ofs << "A = [";
for (int i=0; i < N; ++i)
{
  for (int j=0; j < N; ++j)
  {
    ofs << int(8192*P2(i,j)+1024*c(i,j)) << " ";
  }
  if (i < N-1)
    ofs << ";" << endl;
}
ofs << "];" << endl;
#endif

    return P1(N/2-1,(7*N)/8-1);
}

float echo_BlitzCycled(int N, int niters)
{
    Array<float,2> P1(N,N), P2(N,N), P3(N,N), c(N,N);
    Range I(1,N-2), J(1,N-2);

    setInitialConditions(c, P1, P2, P3, N);
    checkArray(P2, N);
    checkArray(c, N);

    for (int iter=0; iter < niters; ++iter)
    {
        P3(I,J) = (2-4*c(I,J)) * P2(I,J)
          + c(I,J)*(P2(I-1,J) + P2(I+1,J) + P2(I,J-1) + P2(I,J+1))
          - P1(I,J);

        cycleArrays(P1,P2,P3);
    }

    return P1(N/2-1,(7*N)/8-1);
}

float echo_BlitzInterlacedCycled(int N, int niters)
{
    Array<float,2> P1, P2, P3, c;
    allocateArrays(shape(N,N), P1, P2, P3, c);
    Range I(1,N-2), J(1,N-2);

    setInitialConditions(c, P1, P2, P3, N);
    checkArray(P2, N);
    checkArray(c, N);

    for (int iter=0; iter < niters; ++iter)
    {
        P3(I,J) = (2-4*c(I,J)) * P2(I,J)
          + c(I,J)*(P2(I-1,J) + P2(I+1,J) + P2(I,J-1) + P2(I,J+1))
          - P1(I,J);

        cycleArrays(P1,P2,P3);
    }

    return P1(N/2-1,(7*N)/8-1);
}

BZ_DECLARE_STENCIL4(acoustic2D,P1,P2,P3,c)
  P3 = 2 * P2 + c * Laplacian2D(P2) - P1;
BZ_STENCIL_END

float echo_BlitzStencil(int N, int niters)
{
    Array<float,2> P1, P2, P3, c;
    allocateArrays(shape(N,N), P1, P2, P3, c);

    setInitialConditions(c, P1, P2, P3, N);
    checkArray(P2, N);
    checkArray(c, N);

    for (int iter=0; iter < niters; ++iter)
    {
        applyStencil(acoustic2D(), P1, P2, P3, c);
        cycleArrays(P1,P2,P3);
    }

    return P1(N/2-1,(7*N)/8-1);
}

void setInitialConditions(Array<float,2>& c, Array<float,2>& P1,
    Array<float,2>& P2, Array<float,2>& P3, int N)
{
    // Set the velocity field
    c = 0.2;

    // Solid block with which the pulse collides
    int blockLeft = 0;
    int blockRight = int(2*N/5.0-1);
    int blockTop = int(N/3-1);
    int blockBottom = int(2*N/3.0-1);
    c(Range(blockTop,blockBottom),Range(blockLeft,blockRight)) = 0.5;

    // Channel directing the pulse leftwards
    int channelLeft = int(4*N/5.0-1);
    int channelRight = N-1;
    int channel1Height = int(3*N/8.0-1);
    int channel2Height = int(5*N/8.0-1);
    c(channel1Height,Range(channelLeft,channelRight)) = 0.0;
    c(channel2Height,Range(channelLeft,channelRight)) = 0.0;

    // Initial pressure distribution: gaussian pulse inside the channel
    BZ_USING_NAMESPACE(blitz::tensor)
    int cr = int(N/2-1);
    int cc = int(7.0*N/8.0-1);
    float s2 = 64.0 * 9.0 / pow2(N/2.0);
    cout << "cr = " << cr << " cc = " << cc << " s2 = " << s2 << endl;
    P1 = 0.0;
    P2 = exp(-(pow2(i-cr)+pow2(j-cc)) * s2);
    P3 = 0.0;
}

