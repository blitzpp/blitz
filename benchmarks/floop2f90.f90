
      SUBROUTINE floop2_F90(N, x, y, a)
      INTEGER i, N
      REAL*4 x(N), y(N), u

      x = y/u
      RETURN
      END


      SUBROUTINE floop2_F90Overhead(N, x, y, a)
      INTEGER i, N
      REAL*4 x(N), y(N), u

      RETURN
      END
