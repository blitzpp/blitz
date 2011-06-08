#ifndef __BZ_INDEXPAR_H
#define __BZ_INDEXPAR_H

#include <blitz/blitz.h>
#include <blitz/et-forward.h>

BZ_NAMESPACE(blitz);

// Define a template for type used to pass index parameters 
template<int N> 
struct _bz_Indexpar {
#ifdef BZ_ARRAY_EXPR_PASS_INDEX_BY_VALUE
  typedef TinyVector<int,N> index;
#else
  typedef const TinyVector<int,N>& index;
#endif
};

BZ_NAMESPACE_END

#endif
