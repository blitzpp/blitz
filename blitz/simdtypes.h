#ifndef BZ_SIMDTYPES_H
#define BZ_SIMDTYPES_H

#include <blitz/blitz.h>

BZ_NAMESPACE(blitz)

template<class T,int N> class TinyVector;

// Helper class that defines the width of the simd instructions for a
// given type
template<typename T> class simdTypes {
public:
  // simd width of type in bytes
  static const int byteWidth = 
    BZ_SIMD_WIDTH>sizeof(T) ? BZ_SIMD_WIDTH : sizeof(T);
  // simd width of types in number of elements
  static const int vecWidth=
    BZ_SIMD_WIDTH>sizeof(T) ? BZ_SIMD_WIDTH/sizeof(T) : 1;
  typedef TinyVector<T, vecWidth> vecType;
};

BZ_NAMESPACE_END

#endif
