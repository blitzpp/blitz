set(blitz_LIB_SRCS globals.cpp)

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
    set_target_properties(blitz-static PROPERTIES
                          OUTPUT_NAME blitz
                          ${BLITZ-STATIC-DEFS}
                          CLEAN_DIRECT_OUTPUT 1)
endif()

install(TARGETS ${BLITZ_LIBS}
        EXPORT  ${PROJECT_NAME}Targets
        #RUNTIME DESTINATION bin COMPONENT runtime
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT devel
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT devel
)
