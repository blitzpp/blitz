      SUBROUTINE FDTD(CAEX,CBEX,CAEY,CBEY,CAEZ,CBEZ,EX,EY,EZ,HX,HY,HZ)
      REAL CAEX, CBEX, CAEY, CBEY, CAEZ, CBEZ
      REAL EX(129,129,128), EY(129,129,128), EZ(129,129,128)
      REAL HX(129,129,128), HY(129,129,128), HZ(129,129,128)
      DO J = 2, 127
         DO I = 2, 127
            DO K = 2, 127
               EX(K,I,J) = CAEX*(EX(K,I,J) +
     &                     CBEX*(HZ(K,I,J) - HZ(K,I,J-1) +
     &                           HY(K,I,J) - HY(K-1,I,J)))
               EY(K,I,J) = CAEY*(EY(K,I,J) +
     &                     CBEY*(HX(K-1,I,J) - HX(K,I,J) +
     &                           HZ(K,I-1,J) - HZ(K,I,J)))
               EZ(K,I,J) = CAEZ*(EZ(K,I,J) +
     &                     CBEZ*(HX(K,I,J-1) - HX(K,I,J) +
     &                           HY(K,I,J) - HY(K,I-1,J)))
            END DO
         END DO
      END DO
      RETURN
      END
