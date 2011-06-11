
      SUBROUTINE loop22_F90(N, x, y, a)
      INTEGER i, N
      REAL*8 x(N), a(N), b(N), c(N), d(N)

      x = x + a*b + c*d
      RETURN
      END


      SUBROUTINE loop22_F90Overhead(N, x, y, a)
      INTEGER i, N
      REAL*8 x(N), a(N), b(N), c(N), d(N)

      RETURN
      END
