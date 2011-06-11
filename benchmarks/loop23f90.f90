
      SUBROUTINE loop23_F90(N, x, y, a)
      INTEGER i, N
      REAL*8 x(N), a(N), b(N), c(N), d(N), y(N)

      x = a*b + c*d; y = b+d
      RETURN
      END


      SUBROUTINE loop23_F90Overhead(N, x, y, a)
      INTEGER i, N
      REAL*8 x(N), a(N), b(N), c(N), d(N), y(N)

      RETURN
      END
