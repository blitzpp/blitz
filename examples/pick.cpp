/*****************************************************************************
 * pick.cpp          Blitz++ VectorPick example
 *****************************************************************************/

#include <blitz/vector-et.h>
#include <blitz/vecpick.h>

BZ_USING_NAMESPACE(blitz)

int main()
{                                         //   0  1  2  3        8  9
    Vector<float> x = sqr(Range(0,9));    // [ 0  1  4  9  ...  64 81 ]
    cout << x << endl;

    Vector<int> index(3);   
    index[0] = 2;
    index[1] = 5;  
    index[2] = 7;

    VectorPick<float> y(x, index);        //    2  5  7 
    cout << y << endl;                    // [  4 25 49 ]

    y = 0;                                //    0  1  2  3  4  5  6  7  8  9
    cout << x << endl;                    // [  0  1  0  9 16  0 36  0 64 81 ]

    y += sin(Range(0,2));

    return 0;
}

