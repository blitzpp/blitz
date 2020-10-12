add_library(BlitzLib SHARED globals.cpp "$<TARGET_OBJECTS:blitzGitSHA1>")
add_library(Blitz::BlitzLib ALIAS BlitzLib)

target_link_libraries(BlitzLib PUBLIC BlitzHeaders)

set_target_properties(BlitzLib PROPERTIES
                      VERSION ${blitz_VERSION}
                      SOVERSION 0
                      CLEAN_DIRECT_OUTPUT 1)

#install(TARGETS ${BLITZ_LIBS}
        #EXPORT  ${PROJECT_NAME}Targets
        #RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}" COMPONENT runtime
        #ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}" COMPONENT devel
        #LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}" COMPONENT devel
#)
