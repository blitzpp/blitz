#ifndef BZ_ARRAY_ET_H
#define BZ_ARRAY_ET_H

#ifdef BZ_NEW_EXPRESSION_TEMPLATES
 #include <blitz/array/newet.h>     // Expression templates
#else
 #include <blitz/array/bops.cc>     // Expression templates, two operands
 #include <blitz/array/uops.cc>     // Expression templates, math functions
#endif

#endif
