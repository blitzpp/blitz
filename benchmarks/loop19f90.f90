      SUBROUTINE loop19_F90(N, x, a, b, y, u, v)
      INTEGER i, N
      REAL*8 x(N), a(N), b(N), y(N), u, v

      x=u*a
        y=v*b
      RETURN
      END


      SUBROUTINE loop19_F90Overhead(N, x, a, b, y, u, v)
      INTEGER i, N
      REAL*8 x(N), a(N), b(N), y(N), u, v

      RETURN
      END
