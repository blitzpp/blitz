      SUBROUTINE loop14_F77(N, x, a, b, y)
      INTEGER i, N
      REAL*8 x(N), a(N), b(N), y(N)

      DO i=1,N
          x(i)=a(i)+b(i)
          y(i)=a(i)-b(i)
      END DO
      RETURN
      END


      SUBROUTINE loop14_F77Overhead(N, x, a, b, y)
      INTEGER i, N
      REAL*8 x(N), a(N), b(N), y(N)
      RETURN
      END
