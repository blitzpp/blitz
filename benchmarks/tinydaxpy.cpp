// TinyVector<T,N> DAXPY benchmark

#define BZ_DISABLE_KCC_COPY_PROPAGATION_KLUDGE

#include <blitz/tinyvec-et.h>
#include <blitz/timer.h>
#include <blitz/rand-uniform.h>

BZ_USING_NAMESPACE(blitz)

Random<Uniform> rnd(1.0, 2.0);

template<class T>
void optimizationSink(T&);

template<int N_rank>
void tinyDAXPYBenchmark(TinyVector<double,N_rank>, int iters, double a)
{
    Timer timer;
   
    TinyVector<double,N_rank> ta, tb, tc, td, te, tf, tg, th, ti, tj;
    for (int i=0; i < N_rank; ++i)
    {
        ta[i] = rnd.random();
        tb[i] = rnd.random();
        tc[i] = rnd.random();
        td[i] = rnd.random();
        te[i] = rnd.random();
        tf[i] = rnd.random();
        tg[i] = rnd.random();
        th[i] = rnd.random();
        ti[i] = rnd.random();
        tj[i] = rnd.random();
    }

    double b = -a;

    double numFlops = 0;

    if (N_rank < 20)
    {
      timer.start();
      for (int i=0; i < iters; ++i)
      {
        ta += a * tb;
        tc += a * td;
        te += a * tf;
        tg += a * th;
        ti += a * tj;
        tb += b * ta;
        td += b * tc;
        tf += b * te;
        th += b * tg;
        tj += b * ti;
        ta += a * tb;
        tc += a * td;
        te += a * tf;
        tg += a * th;
        ti += a * tj;
        tb += b * ta;
        td += b * tc;
        tf += b * te;
        th += b * tg;
        tj += b * ti;
      }
      timer.stop();
      numFlops = 40.0 * N_rank * double(iters);
    }
    else {
      timer.start();
      for (int i=0; i < iters; ++i)
      {
        ta += a * tb;
        tb += b * ta;
      }
      timer.stop();
      numFlops = 4.0 * N_rank * double(iters);
    }

    optimizationSink(ta);
    optimizationSink(tb);
    optimizationSink(tc);
    optimizationSink(td);
    optimizationSink(te);
    optimizationSink(tf);
    optimizationSink(tg);
    optimizationSink(th);
    optimizationSink(ti);
    optimizationSink(tj);

    timer.stop();
    float Mflops = numFlops / (1.0e+6) / timer.elapsedSeconds();

    if (iters > 1)  
    {
    cout << setw(5) << N_rank << '\t' << Mflops << endl;
    }
}

double a = 0.3429843;

template<class T>
void optimizationSink(T&)
{
}

int main()
{
    cout << "TinyVector<double,N> DAXPY benchmark" << endl
         << setw(5) << "N" << '\t' << "Mflops/s" << endl;
    tinyDAXPYBenchmark(TinyVector<double,1>(), 800000, a);
    tinyDAXPYBenchmark(TinyVector<double,2>(), 800000, a);
    tinyDAXPYBenchmark(TinyVector<double,3>(), 800000, a);
    tinyDAXPYBenchmark(TinyVector<double,4>(), 700000, a);
    tinyDAXPYBenchmark(TinyVector<double,5>(), 600000, a);
    tinyDAXPYBenchmark(TinyVector<double,6>(), 500000, a);
    tinyDAXPYBenchmark(TinyVector<double,7>(), 500000, a);
    tinyDAXPYBenchmark(TinyVector<double,8>(), 500000, a);
    tinyDAXPYBenchmark(TinyVector<double,9>(), 500000, a);
    tinyDAXPYBenchmark(TinyVector<double,10>(), 500000, a);

    return 0;
}

