      SUBROUTINE loop13_F77(N, x, a, b, c, d, y, u)
      INTEGER i, N
      REAL*8 x(N), a(N), b(N), c(N), d(N), y(N), u

      DO i=1,N
          x(i)=a(i)+b(i)+c(i)+d(i)
          y(i)=u+d(i)
      END DO
      RETURN
      END


      SUBROUTINE loop13_F77Overhead(N, x, a, b, c, d, y, u)
      INTEGER i, N
      REAL*8 x(N), a(N), b(N), c(N), d(N), y(N), u
      RETURN
      END
