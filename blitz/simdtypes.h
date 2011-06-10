#ifndef BZ_SIMDTYPES_H
#define BZ_SIMDTYPES_H

#include <blitz/blitz.h>

BZ_NAMESPACE(blitz)

template<class T,int N> class TinyVector;

/** Helper class that defines the width of the simd instructions for a
    given type. It also defines a type that is a TinyVector of the
    appropriate length to fill the simd width. This is used as the
    "evaluation type" to facilitate automatic vectorization. Because
    TinyVectors are aligned on BZ_SIMD_WIDTH, an array of vecType will
    be dense in memory, which is required to reinterpret an array of T
    to an array of vecType. \todo How do we check that the type fits
    evenly into the simd width? */
template<typename T> class simdTypes {
public:
  /// SIMD width of type in bytes (sizeof(T) if simd width does not
  /// fit a T)
  static const int byteWidth = 
    BZ_SIMD_WIDTH>sizeof(T) ? BZ_SIMD_WIDTH : sizeof(T);

  /// SIMD width of types in number of elements.
  static const int vecWidth=
    BZ_SIMD_WIDTH>sizeof(T) ? BZ_SIMD_WIDTH/sizeof(T) : 1;

  /// Vector type of T that fills the simd width.
  typedef TinyVector<T, vecWidth> vecType;
};

BZ_NAMESPACE_END

#endif
