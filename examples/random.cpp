/*****************************************************************************
 * random.cpp        Blitz++ random numbers example
 */

#include <random/uniform.h>
#include <blitz/numinquire.h>
#include <time.h>
#include <iostream>
#include <iomanip>

using namespace ranlib;
using namespace blitz;

template<class T>
void printRandoms()
{
  Uniform<T> x;
  //x.seed((unsigned int)time(0));
  x.seed(5);
  int N=5;
  for (int i = 0; i < N; ++i) 
    cout << setprecision(digits10(T())) << x.random() << endl;

  cout << endl;
}

int main()
{
  cout << "Some random float: " << endl;
  printRandoms<float>();

  cout << "Some random doubles: " << endl;
  printRandoms<double>();

  cout << "Some random long doubles: " << endl;
  printRandoms<long double>();

  return 0;
}

