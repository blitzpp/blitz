      SUBROUTINE loop12_F90(N, y, a, x, b, c, d, u)
      INTEGER i, N
      REAL*8 y(N), a(N), x(N), b(N), c(N), d(N), u

      y=u+a
        x=a+b+c+d
      RETURN
      END


      SUBROUTINE loop12_F90Overhead(N, y, a, x, b, c, d, u)
      INTEGER i, N
      REAL*8 y(N), a(N), x(N), b(N), c(N), d(N), u

      RETURN
      END
