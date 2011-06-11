
      SUBROUTINE loop5_F90(N, x, y, a)
      INTEGER i, N
      REAL*8 x(N), a(N), b(N)

      x = a+b
      RETURN
      END


      SUBROUTINE loop5_F90Overhead(N, x, y, a)
      INTEGER i, N
      REAL*8 x(N), a(N), b(N)

      RETURN
      END
