// BZ_HAVE_SYSTEM_V_MATH

#ifndef _ALL_SOURCE
 #define _ALL_SOURCE
#endif

#ifndef _XOPEN_SOURCE
 #define _XOPEN_SOURCE
#endif

#ifndef _XOPEN_SOURCE_EXTENDED
 #define _XOPEN_SOURCE_EXTENDED 1
#endif

#include <math.h>

int main()
{
    double x = 1.0;
    double y = 1.0;

    _class(x);
    ilogb(x);
    itrunc(x);
    nearest(x);
    rsqrt(x);
    uitrunc(x);

    copysign(x,y);
    drem(x,y);
    fmod(x,y);
    hypot(x,y);
    nextafter(x,y);
    remainder(x,y);
    scalb(x,y);
    unordered(x,y);

    return 0;
}

