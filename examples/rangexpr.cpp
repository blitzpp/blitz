/*****************************************************************************
 * rangexpr.cpp        Blitz++ range expression example
 *****************************************************************************/

#include <blitz/vector-et.h>

BZ_USING_NAMESPACE(blitz)

#ifndef M_PI
 #define M_PI   3.14159265358979323846
#endif

int main()
{
    Vector<float> x = cos(Range(0,7) * (2.0 * M_PI / 8));

    cout << x << endl;

    return 0;
}

