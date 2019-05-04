
AC_DEFUN([AC_SET_COMPILER_SPECIFIC_HEADER],[

AC_ARG_VAR([COMPILER_SPECIFIC_HEADER],[
automatically set if supported compiler, otherwise
should be set to <some-compiler-specific-path>/bzconfig.h.
See also file blitz/bzconfig.h
])

AC_MSG_CHECKING(compiler specific header)

case "$CXX" in
  *xlc++*)      COMPILER_SPECIFIC_HEADER="apple/bzconfig.h" ;;
  *icpc*|*icc*) COMPILER_SPECIFIC_HEADER="intel/bzconfig.h" ;;
  *xlC*)        COMPILER_SPECIFIC_HEADER="ibm/bzconfig.h" ;;
  *clang++)     COMPILER_SPECIFIC_HEADER="llvm/bzconfig.h" ;;
  *cxx*)        COMPILER_SPECIFIC_HEADER="compaq/bzconfig.h" ;;
  *aCC*)        COMPILER_SPECIFIC_HEADER="hp/bzconfig.h" ;;
  *g++*|*c++*)  case "$target" in
                  *apple*) COMPILER_SPECIFIC_HEADER="llvm/bzconfig.h" ;;
                  *)       COMPILER_SPECIFIC_HEADER="gnu/bzconfig.h" ;;
                esac
                ;;
  *KCC*)        COMPILER_SPECIFIC_HEADER="kai/bzconfig.h" ;;
  *pgCC*)       COMPILER_SPECIFIC_HEADER="pgi/bzconfig.h" ;;
dnl  *FCC*)        COMPILER_SPECIFIC_HEADER="fujitsu/bzconfig.h" ;;
  *pathCC*)     COMPILER_SPECIFIC_HEADER="pathscale/bzconfig.h" ;;
  *CC*)
    case "$target" in
    *sgi*)      COMPILER_SPECIFIC_HEADER="sgi/bzconfig.h" ;;
    *solaris*)  COMPILER_SPECIFIC_HEADER="sun/bzconfig.h" ;;
    *cray*)     COMPILER_SPECIFIC_HEADER="cray/bzconfig.h" ;;
    *fujitsu*)  COMPILER_SPECIFIC_HEADER="fujitsu/bzconfig.h" ;;
    esac
  ;;
esac

AX_PREFIX_CONFIG_H([blitz/${COMPILER_SPECIFIC_HEADER}],[BZ])

AC_MSG_RESULT($COMPILER_SPECIFIC_HEADER)

AC_SUBST(COMPILER_SPECIFIC_HEADER,$COMPILER_SPECIFIC_HEADER)
])
