#ifndef BZ_ARRAY_OPS_H
#define BZ_ARRAY_OPS_H

#ifndef BZ_OPS_H
 #include <blitz/ops.h>
#endif

#ifndef BZ_NEWET_MACROS_H
 #include <blitz/array/newet-macros.h>
#endif

BZ_NAMESPACE(blitz)

// operator<< has been commented out because it causes ambiguity
// with statements like "cout << A".  NEEDS_WORK
// ditto operator<<

BZ_DECLARE_ARRAY_ET(operator+,  Add)
BZ_DECLARE_ARRAY_ET(operator-,  Subtract)
BZ_DECLARE_ARRAY_ET(operator*,  Multiply)
BZ_DECLARE_ARRAY_ET(operator/,  Divide)
BZ_DECLARE_ARRAY_ET(operator%,  Modulo)
BZ_DECLARE_ARRAY_ET(operator^,  BitwiseXor)
BZ_DECLARE_ARRAY_ET(operator&,  BitwiseAnd)
BZ_DECLARE_ARRAY_ET(operator|,  BitwiseOr)
// BZ_DECLARE_ARRAY_ET(operator>>, ShiftRight)
// BZ_DECLARE_ARRAY_ET(operator<<, ShiftLeft)
BZ_DECLARE_ARRAY_ET(operator>,  Greater)
BZ_DECLARE_ARRAY_ET(operator<,  Less)
BZ_DECLARE_ARRAY_ET(operator>=, GreaterOrEqual)
BZ_DECLARE_ARRAY_ET(operator<=, LessOrEqual)
BZ_DECLARE_ARRAY_ET(operator==, Equal)
BZ_DECLARE_ARRAY_ET(operator!=, NotEqual)
BZ_DECLARE_ARRAY_ET(operator&&, LogicalAnd)
BZ_DECLARE_ARRAY_ET(operator||, LogicalOr)

BZ_DECLARE_ARRAY_ET_UOP(operator-, _bz_negate)

// NEEDS_WORK: operator!, operator~

BZ_NAMESPACE_END

#endif
