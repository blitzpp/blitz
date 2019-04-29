SET(RAMDOM_FILES
    F.h beta.h chisquare.h default.h discrete-uniform.h exponential.h
    gamma.h mt.h mtparam.cc normal.h uniform.h)

INSTALL(FILES ${RAMDOM_FILES} DESTINATION include/random )
