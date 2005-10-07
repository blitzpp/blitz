#include <blitz/tinyvec-et.h>

using namespace blitz;

int main()
{
    TinyVector<int,3> A, B;
    A = 1, 2, 3;
    B = 0, 1, 2;

    A += B*B;
  
    cout << A << endl;

    A *= 10;

    cout << A << endl;

    TinyVector<int,3>::iterator it, end=B.end();
    for (it = B.begin(); it != end; ++it) 
        cout << *it << " ";
    cout << endl;
}

