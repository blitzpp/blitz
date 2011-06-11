
      SUBROUTINE loop19_F90(N, x, y, a)
      INTEGER i, N
      REAL*8 y(N), x(N), a(N), b(N), u, v

      x = u*a; y = v*b
      RETURN
      END


      SUBROUTINE loop19_F90Overhead(N, x, y, a)
      INTEGER i, N
      REAL*8 y(N), x(N), a(N), b(N), u, v

      RETURN
      END
