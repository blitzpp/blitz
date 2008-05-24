#include "blitz/array.h"
using namespace blitz;

int main(int, char**)
{
  Array<double,2> a(10,10);
  Array<double,1> d(sum(a,tensor::j));

}
