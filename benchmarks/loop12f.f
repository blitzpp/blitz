      SUBROUTINE loop12_F77(N, y, a, x, b, c, d, u)
      INTEGER i, N
      REAL*8 y(N), a(N), x(N), b(N), c(N), d(N), u

      DO i=1,N
          y(i)=u+a(i)
          x(i)=a(i)+b(i)+c(i)+d(i)
      END DO
      RETURN
      END


      SUBROUTINE loop12_F77Overhead(N, y, a, x, b, c, d, u)
      INTEGER i, N
      REAL*8 y(N), a(N), x(N), b(N), c(N), d(N), u
      RETURN
      END
