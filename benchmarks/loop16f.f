      SUBROUTINE loop16_F77(N, x, a, b, c, y, u)
      INTEGER i, N
      REAL*8 x(N), a(N), b(N), c(N), y(N), u

      DO i=1,N
          x(i)=a(i)+b(i)+c(i)
          y(i)=x(i)+c(i)+u
      END DO
      RETURN
      END


      SUBROUTINE loop16_F77Overhead(N, x, a, b, c, y, u)
      INTEGER i, N
      REAL*8 x(N), a(N), b(N), c(N), y(N), u
      RETURN
      END
