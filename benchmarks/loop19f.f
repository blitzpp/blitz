      SUBROUTINE loop19_F77(N, x, a, b, y, u, v)
      INTEGER i, N
      REAL*8 x(N), a(N), b(N), y(N), u, v

      DO i=1,N
          x(i)=u*a(i)
          y(i)=v*b(i)
      END DO
      RETURN
      END


      SUBROUTINE loop19_F77Overhead(N, x, a, b, y, u, v)
      INTEGER i, N
      REAL*8 x(N), a(N), b(N), y(N), u, v
      RETURN
      END
