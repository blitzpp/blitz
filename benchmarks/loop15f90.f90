      SUBROUTINE loop15_F90(N, x, c, a, b)
      INTEGER i, N
      REAL*8 x(N), c(N), a(N), b(N)

      x=c+a*b
      RETURN
      END


      SUBROUTINE loop15_F90Overhead(N, x, c, a, b)
      INTEGER i, N
      REAL*8 x(N), c(N), a(N), b(N)

      RETURN
      END
