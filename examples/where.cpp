/*****************************************************************************
 * where.cpp     Blitz++ Vector<T> example, illustrating where(X,Y,Z)
 *               expressions.
 *****************************************************************************/

#include <blitz/vector-et.h>
#include <blitz/vecwhere.h>

BZ_USING_NAMESPACE(blitz)

int main()
{
    Vector<int> x = Range(-3,+3);   // [ -3 -2 -1  0  1  2  3 ]

    // The where(X,Y,Z) function is similar to the X ? Y : Z operator.
    // If X is logical true, then Y is returned; otherwise, Z is
    // returned.

    Vector<int> y = where(abs(x) > 2, x+10, x-10);

    // The above statement is transformed into something resembling:
    //
    // for (unsigned i=0; i < 7; ++i)
    //     y[i] = (abs(x[i]) > 2) ? (x[i]+10) : (x[i]-10);
    //
    // The first expression (abs(x) > 2) can involve the usual
    // comparison and logical operators: < > <= >= == != && || 

    cout << x << endl
         << y << endl;

    return 0;
}

