!      INTEGER N, iters
!      REAL check

!      N = 128
!      iters = N*3
!      CALL echo_f77(N,iters,check)
!      PRINT *, check
!      END


 
      SUBROUTINE echo_f77Tuned(N, niters, check)
      INTEGER N, niters, iter
      REAL check
      REAL P1(N,N), P2(N,N), P3(N,N), C(N,N)
      INTEGER i, j
      INTEGER nitersd3, remainder

      CALL echo_f77_set(c, P1, P2, P3, N)
      CALL checkArray2(P2, N)
      CALL checkArray2(c, N)

      nitersd3 = niters / 3
      remainder = niters - 3 * nitersd3
      IF (remainder .NE. 0) THEN
        PRINT *, 'niters should be divisible by 3, results will be off'
      ENDIF

      DO iter=1, niters, 3
        CALL stencil5(c, P1, P2, P3, N)
        CALL stencil5(c, P2, P3, P1, N)
        CALL stencil5(c, P3, P1, P2, N)
      END DO

      check = P1(N/2,7*N/8)

      RETURN
      END



      SUBROUTINE stencil5(c, P1, P2, P3, N)
      INTEGER N
      REAL c(N,N), P1(N,N), P2(N,N), P3(N,N)
      REAL tmp1, tmp2, tmp3
      INTEGER TileWidth, TileHeight, bj, nj, bi, ni, i

      TileWidth = 16
      TileHeight = 3

      DO bj=2, N-1, TileWidth
        nj = MIN(bj+TileWidth-1, N-1)

        DO bi=2, N-1, TileHeight
          IF (bi+TileHeight .LT. N) THEN
            i = bi
            DO j=bj,nj
              tmp1 = (2-4*c(i,j))*P2(i,j) + c(i,j)*(P2(i,j-1)
     .          + P2(i,j+1) + P2(i-1,j) + P2(i+1,j)) - P1(i,j)
              tmp2 = (2-4*c(i+1,j))*P2(i+1,j) + c(i+1,j)
     .          *(P2(i+1,j-1) + P2(i+1,j+1) + P2(i,j) + P2(i+2,j)) 
     .          - P1(i+1,j)
              tmp3 = (2-4*c(i+2,j))*P2(i+2,j) + c(i+2,j)
     .          *(P2(i+2,j-1) + P2(i+2,j+1) + P2(i+1,j) + P2(i+3,j)) 
     .          - P1(i+2,j)
              P3(i,j) = tmp1
              P3(i+1,j) = tmp2
              P3(i+2,j) = tmp3
            END DO
          ELSE
            DO i=bi, N-1
              DO j=bj,nj
                P3(i,j) = (2-4*c(i,j))*P2(i,j) + c(i,j)*(P2(i,j-1)
     .            + P2(i,j+1) + P2(i-1,j) + P2(i+1,j)) - P1(i,j)
              END DO
            END DO
          END IF
        END DO
      END DO

      RETURN
      END


      SUBROUTINE checkArray2(A, N)
      INTEGER N
      REAL A(N,N)

      INTEGER i,j
      REAL check
      check = 0.0
      DO j=1,N
        DO i=1,N
          check = check + (i*n+j)*A(i,j)
        END DO
      END DO

      PRINT *, 'Array check: ', check
      RETURN
      END

