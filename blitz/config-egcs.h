/******************************************************************************
 * config.h           Compiler language support flags
 *
 * This file was generated automatically by the script bzconfig.
 * You should rerun bzconfig each time you switch compilers, install new
 * standard libraries, or change compiler versions.
 *
 */

 
#ifndef BZ_CONFIG_H
#define BZ_CONFIG_H
 
#define BZ_COMPILER_NAME   "xgcc"
#define BZ_COMPILER_OPTIONS "-I /home/tveldhui/software/egcs/include -B /home/tveldhui/software/egcs/include"
#define BZ_OS_NAME         "AIX 2"
#define BZ_BZCONFIG_DATE   "Mon Sep  8 13:14:14 EDT 1997"
 
#undef  BZ_NAMESPACES
#undef  BZ_EXCEPTIONS
#define BZ_RTTI
#define BZ_MEMBER_CONSTANTS
#define BZ_OLD_FOR_SCOPING
#define BZ_EXPLICIT
#define BZ_MUTABLE
#define BZ_TYPENAME
#undef  BZ_NCEG_RESTRICT
#define BZ_BOOL
#define BZ_CONST_CAST
#define BZ_STATIC_CAST
#define BZ_REINTERPRET_CAST
#define BZ_DYNAMIC_CAST
#define BZ_TEMPLATES
#define BZ_PARTIAL_SPECIALIZATION
#undef  BZ_PARTIAL_ORDERING
#define BZ_DEFAULT_TEMPLATE_PARAMETERS
#undef  BZ_MEMBER_TEMPLATES
#undef  BZ_MEMBER_TEMPLATES_OUTSIDE_CLASS
#define BZ_FULL_SPECIALIZATION_SYNTAX
#undef  BZ_FUNCTION_NONTYPE_PARAMETERS
#define BZ_TEMPLATE_QUALIFIED_BASE_CLASS
#define BZ_TEMPLATE_QUALIFIED_RETURN_TYPE
#undef  BZ_EXPLICIT_TEMPLATE_FUNCTION_QUALIFICATION
#undef  BZ_TEMPLATES_AS_TEMPLATE_ARGUMENTS
#undef  BZ_TEMPLATE_KEYWORD_QUALIFIER
#undef  BZ_TEMPLATE_SCOPED_ARGUMENT_MATCHING
#define BZ_TYPE_PROMOTION
#define BZ_USE_NUMTRAIT
#undef  BZ_HAVE_COMPLEX
#undef  BZ_HAVE_NUMERIC_LIMITS
#undef  BZ_HAVE_VALARRAY
#undef  BZ_HAVE_COMPLEX_MATH
#define BZ_HAVE_IEEE_MATH
#define BZ_HAVE_SYSTEM_V_MATH
#undef  BZ_HAVE_STD
#define BZ_HAVE_RUSAGE
#define BZ_ENUM_COMPUTATIONS
 
#endif // BZ_CONFIG_H
