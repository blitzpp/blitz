      SUBROUTINE loop16_F90(N, x, a, b, c, y, u)
      INTEGER i, N
      REAL*8 x(N), a(N), b(N), c(N), y(N), u

      x=a+b+c
        y=x+c+u
      RETURN
      END


      SUBROUTINE loop16_F90Overhead(N, x, a, b, c, y, u)
      INTEGER i, N
      REAL*8 x(N), a(N), b(N), c(N), y(N), u

      RETURN
      END
