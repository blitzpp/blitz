
      SUBROUTINE floop13_F90(N, x, y, a)
      INTEGER i, N
      REAL*4 y(N), x(N), a(N), b(N), c(N), d(N), u

      x = a+b+c+d; y = u+d
      RETURN
      END


      SUBROUTINE floop13_F90Overhead(N, x, y, a)
      INTEGER i, N
      REAL*4 y(N), x(N), a(N), b(N), c(N), d(N), u

      RETURN
      END
