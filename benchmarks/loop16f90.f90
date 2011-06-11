
      SUBROUTINE loop16_F90(N, x, y, a)
      INTEGER i, N
      REAL*8 y(N), x(N), a(N), b(N), c(N), u

      x = a+b+c; y = x+c+u
      RETURN
      END


      SUBROUTINE loop16_F90Overhead(N, x, y, a)
      INTEGER i, N
      REAL*8 y(N), x(N), a(N), b(N), c(N), u

      RETURN
      END
