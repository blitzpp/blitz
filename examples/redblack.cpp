        HSQ = H*H
        FACTOR = 1.0D0/6.0D0
        DO NREL=1,ITER

          WHERE(RED(2:NX-1,2:NY-1,2:NZ-1))
  !
  !     RELAXATION OF THE RED POINTS
  !
          U(2:NX-1,2:NY-1,2:NZ-1) =                                       &
       &              FACTOR*(HSQ*F(2:NX-1,2:NY-1,2:NZ-1)+                &
       &    U(1:NX-2,2:NY-1,2:NZ-1)+U(3:NX,2:NY-1,2:NZ-1)+                &
       &    U(2:NX-1,1:NY-2,2:NZ-1)+U(2:NX-1,3:NY,2:NZ-1)+                &
       &    U(2:NX-1,2:NY-1,1:NZ-2)+U(2:NX-1,2:NY-1,3:NZ))

          ELSEWHERE
  !
  !     RELAXATION OF THE BLACK POINTS
  !
          U(2:NX-1,2:NY-1,2:NZ-1) =                                       &
       &              FACTOR*(HSQ*F(2:NX-1,2:NY-1,2:NZ-1)+                &
       &    U(1:NX-2,2:NY-1,2:NZ-1)+U(3:NX,2:NY-1,2:NZ-1)+                &
       &    U(2:NX-1,1:NY-2,2:NZ-1)+U(2:NX-1,3:NY,2:NZ-1)+                &
       &    U(2:NX-1,2:NY-1,1:NZ-2)+U(2:NX-1,2:NY-1,3:NZ))

          END WHERE

        ENDDO
