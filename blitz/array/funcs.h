#ifndef BZ_BASICOPS_H
#define BZ_BASICOPS_H

#ifndef BZ_MATHFUNC_H
 #include <blitz/mathfunc.h>
#endif

#ifndef BZ_NEWET_MACROS_H
 #include <blitz/array/newet-macros.h>
#endif

BZ_NAMESPACE(blitz)

BZ_DECLARE_ARRAY_ET(atan2,      _bz_atan2)
BZ_DECLARE_ARRAY_ET(pow,        _bz_pow)

#ifdef BZ_HAVE_COMPLEX_MATH
BZ_DECLARE_ARRAY_ET(polar,     _bz_polar)
#endif

#ifdef BZ_HAVE_SYSTEM_V_MATH
BZ_DECLARE_ARRAY_ET(copysign,  _bz_copysign)
BZ_DECLARE_ARRAY_ET(drem,      _bz_drem)
BZ_DECLARE_ARRAY_ET(fmod,      _bz_fmod)
BZ_DECLARE_ARRAY_ET(hypot,     _bz_hypot)
BZ_DECLARE_ARRAY_ET(nextafter, _bz_nextafter)
BZ_DECLARE_ARRAY_ET(remainder, _bz_remainder)
BZ_DECLARE_ARRAY_ET(scalb,     _bz_scalb)
BZ_DECLARE_ARRAY_ET(unordered, _bz_unordered)
#endif

BZ_DECLARE_ARRAY_ET_UOP(abs,   _bz_abs)
BZ_DECLARE_ARRAY_ET_UOP(acos,  _bz_acos)
BZ_DECLARE_ARRAY_ET_UOP(asin,  _bz_asin)
BZ_DECLARE_ARRAY_ET_UOP(atan,  _bz_atan)
BZ_DECLARE_ARRAY_ET_UOP(ceil,  _bz_ceil)
BZ_DECLARE_ARRAY_ET_UOP(cexp,  _bz_cexp)
BZ_DECLARE_ARRAY_ET_UOP(cos,   _bz_cos)
BZ_DECLARE_ARRAY_ET_UOP(cosh,  _bz_cosh)
BZ_DECLARE_ARRAY_ET_UOP(csqrt, _bz_csqrt)
BZ_DECLARE_ARRAY_ET_UOP(exp,   _bz_exp)
BZ_DECLARE_ARRAY_ET_UOP(fabs,  _bz_abs)
BZ_DECLARE_ARRAY_ET_UOP(floor, _bz_floor)
BZ_DECLARE_ARRAY_ET_UOP(log,   _bz_log)
BZ_DECLARE_ARRAY_ET_UOP(log10, _bz_log10)
BZ_DECLARE_ARRAY_ET_UOP(pow2,  _bz_pow2)
BZ_DECLARE_ARRAY_ET_UOP(pow3,  _bz_pow3)
BZ_DECLARE_ARRAY_ET_UOP(pow4,  _bz_pow4)
BZ_DECLARE_ARRAY_ET_UOP(pow5,  _bz_pow5)
BZ_DECLARE_ARRAY_ET_UOP(pow6,  _bz_pow6)
BZ_DECLARE_ARRAY_ET_UOP(pow7,  _bz_pow7)
BZ_DECLARE_ARRAY_ET_UOP(pow8,  _bz_pow8)
BZ_DECLARE_ARRAY_ET_UOP(sin,   _bz_sin)
BZ_DECLARE_ARRAY_ET_UOP(sinh,  _bz_sinh)
BZ_DECLARE_ARRAY_ET_UOP(sqr,   _bz_sqr)
BZ_DECLARE_ARRAY_ET_UOP(sqrt,  _bz_sqrt)
BZ_DECLARE_ARRAY_ET_UOP(tan,   _bz_tan)
BZ_DECLARE_ARRAY_ET_UOP(tanh,  _bz_tanh)

#ifdef BZ_HAVE_COMPLEX_MATH
BZ_DECLARE_ARRAY_ET_UOP(arg,   _bz_arg)
BZ_DECLARE_ARRAY_ET_UOP(conj,  _bz_conj)
#endif

#ifdef BZ_HAVE_SYSTEM_V_MATH
BZ_DECLARE_ARRAY_ET_UOP(_class,  _bz__class)
BZ_DECLARE_ARRAY_ET_UOP(ilogb,   _bz_ilogb)
BZ_DECLARE_ARRAY_ET_UOP(itrunc,  _bz_itrunc)
BZ_DECLARE_ARRAY_ET_UOP(nearest, _bz_nearest)
BZ_DECLARE_ARRAY_ET_UOP(rsqrt,   _bz_rsqrt)
BZ_DECLARE_ARRAY_ET_UOP(uitrunc, _bz_uitrunc)
#endif


#ifdef BZ_HAVE_IEEE_MATH

// finite and trunc omitted: blitz-bugs/archive/0189.html
BZ_DECLARE_ARRAY_ET_UOP(acosh,  _bz_acosh)
BZ_DECLARE_ARRAY_ET_UOP(asinh,  _bz_asinh)
BZ_DECLARE_ARRAY_ET_UOP(atanh,  _bz_atanh)
BZ_DECLARE_ARRAY_ET_UOP(cbrt,   _bz_cbrt)
BZ_DECLARE_ARRAY_ET_UOP(expm1,  _bz_expm1)
BZ_DECLARE_ARRAY_ET_UOP(erf,    _bz_erf)
BZ_DECLARE_ARRAY_ET_UOP(erfc,   _bz_erfc)
// BZ_DECLARE_ARRAY_ET_UOP(finite, _bz_finite)
BZ_DECLARE_ARRAY_ET_UOP(isnan,  _bz_isnan)
BZ_DECLARE_ARRAY_ET_UOP(j0,     _bz_j0)
BZ_DECLARE_ARRAY_ET_UOP(j1,     _bz_j1)
BZ_DECLARE_ARRAY_ET_UOP(lgamma, _bz_lgamma)
BZ_DECLARE_ARRAY_ET_UOP(logb,   _bz_logb)
BZ_DECLARE_ARRAY_ET_UOP(log1p,  _bz_log1p)
BZ_DECLARE_ARRAY_ET_UOP(rint,   _bz_rint)
// BZ_DECLARE_ARRAY_ET_UOP(trunc,  _bz_trunc)
BZ_DECLARE_ARRAY_ET_UOP(y0,     _bz_y0)
BZ_DECLARE_ARRAY_ET_UOP(y1,     _bz_y1)
#endif

BZ_NAMESPACE_END

#endif
