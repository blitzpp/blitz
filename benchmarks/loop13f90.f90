      SUBROUTINE loop13_F90(N, x, a, b, c, d, y, u)
      INTEGER i, N
      REAL*8 x(N), a(N), b(N), c(N), d(N), y(N), u

      x=a+b+c+d
        y=u+d
      RETURN
      END


      SUBROUTINE loop13_F90Overhead(N, x, a, b, c, d, y, u)
      INTEGER i, N
      REAL*8 x(N), a(N), b(N), c(N), d(N), y(N), u

      RETURN
      END
