#include <blitz/array-only.h>
#include <blitz/array/ops.h>
#include <blitz/array/funcs.h>

int main() {
  using namespace blitz;
  Array<int,2> A(7, 7);
  firstIndex i;
  secondIndex j;
  A=i+10*j;
  cout << A << endl << A.base() << endl << A.ubound() << endl << endl;
  A.reindexSelf(TinyVector<int,2>(2,3));
  cout << A << endl << A.base() << endl << A.ubound() << endl << endl;
}

