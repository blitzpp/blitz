#include <blitz/tinymat.h>
#include <blitz/tinyvec.h>

using namespace blitz;

template<class T> void sink(T&) { }

int main()
{
   TinyMatrix<complex<double>,4,4> gamma1, gamma3;
   TinyVector<complex<double>,4> Psi;

   complex<double> i(0,1);

   gamma1 = 0, i, 0, 0,
            i, 0, 0, 0,
            0, 0, 0, -i,
            0, 0, -i, 0;

   gamma3 = 0, 1, 0, 0,
            -1, 0, 0, 0,
            0, 0, 0, 1,
            0, 0, -1, 0;

   sink(Psi);

   TinyVector<complex<double>,4> tmp, result;
   tmp = product(gamma3,Psi);
   result = product(gamma1,tmp);

   sink(result);
   return 0;
}

