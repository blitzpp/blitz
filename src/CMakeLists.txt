add_library(BlitzSrc OBJECT globals.cpp)
add_library(Blitz::BlitzSrc ALIAS BlitzSrc)

target_link_libraries(BlitzSrc PUBLIC BlitzHeaders)

#install(TARGETS ${BLITZ_LIBS}
        #EXPORT  ${PROJECT_NAME}Targets
        #RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}" COMPONENT runtime
        #ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}" COMPONENT devel
        #LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}" COMPONENT devel
#)
