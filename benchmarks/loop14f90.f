      SUBROUTINE loop14_F90(N, x, a, b, y)
      INTEGER i, N
      REAL*8 x(N), a(N), b(N), y(N)

      x=a+b
        y=a-b
      RETURN
      END


      SUBROUTINE loop14_F90Overhead(N, x, a, b, y)
      INTEGER i, N
      REAL*8 x(N), a(N), b(N), y(N)

      RETURN
      END
