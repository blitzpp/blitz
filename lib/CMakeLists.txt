set(blitz_LIB_SRCS ../src/globals.cpp)

add_library(blitz SHARED ${blitz_LIB_SRCS})
add_dependencies(blitz generated-headers)

set_target_properties(blitz PROPERTIES
                      VERSION ${blitz_VERSION}
                      SOVERSION 0
                      CLEAN_DIRECT_OUTPUT 1)

set(BLITZ_LIBS blitz)
if (NOT WIN32)
    add_library(blitz-static STATIC ${blitz_LIB_SRCS})
    add_dependencies(blitz-static generated-headers)
    set(BLITZ_LIBS ${BLITZ_LIBS} blitz-static)

    #SET(BLITZ-STATIC-DEFS)
    #IF (NOT WIN32)
    #    GET_TARGET_PROPERTY(BLITZ-STATIC-DEFS blitz-static COMPILE_DEFINITIONS)
    #    IF (NOT BLITZ-STATIC-DEFS)
    #        SET(BLITZ-STATIC-DEFS)
    #    ENDIF()
    #    SET(BLITZ-STATIC-DEFS COMPILE_DEFINITIONS "${BLITZ-STATIC-DEFS};BLITZ_STATIC_LIBRARY")
    #ENDIF()

    set_target_properties(blitz-static PROPERTIES
                          OUTPUT_NAME blitz
                          ${BLITZ-STATIC-DEFS}
                          CLEAN_DIRECT_OUTPUT 1)
endif()

install(TARGETS ${BLITZ_LIBS}
        EXPORT  blitz
        #RUNTIME DESTINATION bin COMPONENT runtime
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT devel
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT devel
)
