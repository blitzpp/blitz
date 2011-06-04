#ifndef BZ_RANGE_CC
#define BZ_RANGE_CC


#include <blitz/range.h>
#include <blitz/array/ops.h>

BZ_NAMESPACE(blitz)


inline Range::T_numtype Range::operator[](int i) const
{
  return first_ + i * stride_;
}

inline RectDomain<Range::rank_> Range::domain() const
{ 
  return RectDomain<rank_>(TinyVector<int,1>(0),
			   TinyVector<int,1>(ubound(0)));
}

BZ_NAMESPACE_END

#endif
