#include <blitz/array.h>

using namespace blitz;

int main()
{
    Array<int,1> A(4), B(4);
    Array<float,1> C(4);

    A = 1, 2, 3, 5;
    B = 2, 2, 2, 7;

    C = A / B;
    cout << C << endl;

    C = A / cast(B, float());
    cout << C << endl;

    return 0;
}

