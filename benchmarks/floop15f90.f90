
      SUBROUTINE floop15_F90(N, x, y, a)
      INTEGER i, N
      REAL*4 x(N), a(N), b(N), c(N)

      x = c + a*b
      RETURN
      END


      SUBROUTINE floop15_F90Overhead(N, x, y, a)
      INTEGER i, N
      REAL*4 x(N), a(N), b(N), c(N)

      RETURN
      END
