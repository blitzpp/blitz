      SUBROUTINE loop15_F77(N, x, c, a, b)
      INTEGER i, N
      REAL*8 x(N), c(N), a(N), b(N)

      DO i=1,N
          x(i)=c(i)+a(i)*b(i)
      END DO
      RETURN
      END


      SUBROUTINE loop15_F77Overhead(N, x, c, a, b)
      INTEGER i, N
      REAL*8 x(N), c(N), a(N), b(N)
      RETURN
      END
