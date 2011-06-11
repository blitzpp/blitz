
      SUBROUTINE floop9_F90(N, x, y, a)
      INTEGER i, N
      REAL*4 a(N), x(N)

      x = x+a
      RETURN
      END


      SUBROUTINE floop9_F90Overhead(N, x, y, a)
      INTEGER i, N
      REAL*4 a(N), x(N)

      RETURN
      END
