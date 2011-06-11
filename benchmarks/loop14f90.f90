
      SUBROUTINE loop14_F90(N, x, y, a)
      INTEGER i, N
      REAL*8 y(N), x(N), a(N), b(N)

      x = a+b; y = a-b
      RETURN
      END


      SUBROUTINE loop14_F90Overhead(N, x, y, a)
      INTEGER i, N
      REAL*8 y(N), x(N), a(N), b(N)

      RETURN
      END
