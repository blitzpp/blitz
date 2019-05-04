
AC_DEFUN([AC_SET_COMPILER_SPECIFIC_HEADER],[

AC_ARG_VAR([COMPILER_SPECIFIC_HEADER],[
automatically set if supported compiler, otherwise
should be set to <some-compiler-specific-path>/bzconfig.h.
See also file blitz/bzconfig.h
])

AC_MSG_CHECKING(compiler specific header)

AS_CASE([$CXX],
  [*xlc++*],      [COMPILER_VENDOR="apple"],
  [*icpc*|*icc*], [COMPILER_VENDOR="intel"],
  [*xlC*],        [COMPILER_VENDOR="ibm"],
  [*clang++],     [COMPILER_VENDOR="llvm"],
  [*cxx*],        [COMPILER_VENDOR="compaq"],
  [*aCC*],        [COMPILER_VENDOR="hp"],
  [*g++*|*c++*],  [AS_CASE([$target],
                           [*apple*], [COMPILER_VENDOR="llvm"],
                                      [COMPILER_VENDOR="gnu"])],
  [*KCC*],        [COMPILER_VENDOR="kai"],
  [*pgCC*],       [COMPILER_VENDOR="pgi"],
dnl  [*FCC*],        [COMPILER_VENDOR="fujitsu"],
  [*pathCC*],     [COMPILER_VENDOR="pathscale"],
  [*CC*],         [AS_CASE([$target],
                      [*sgi*],      [COMPILER_VENDOR="sgi"],
                      [*solaris*],  [COMPILER_VENDOR="sun"],
                      [*cray*],     [COMPILER_VENDOR="cray"],
                      [*fujitsu*],  [COMPILER_VENDOR="fujitsu"])]
)
export COMPILER_VENDOR
AX_PREFIX_CONFIG_H([blitz/$COMPILER_VENDOR/bzconfig.h],[BZ])
AC_SUBST(COMPILER_SPECIFIC_HEADER,$COMPILER_VENDOR/bzconfig.h)

AC_MSG_RESULT($COMPILER_SPECIFIC_HEADER)

])
