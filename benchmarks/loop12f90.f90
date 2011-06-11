
      SUBROUTINE loop12_F90(N, x, y, a)
      INTEGER i, N
      REAL*8 y(N), x(N), a(N), b(N), c(N), d(N), u

      y = u+a; x = a+b+c+d
      RETURN
      END


      SUBROUTINE loop12_F90Overhead(N, x, y, a)
      INTEGER i, N
      REAL*8 y(N), x(N), a(N), b(N), c(N), d(N), u

      RETURN
      END
