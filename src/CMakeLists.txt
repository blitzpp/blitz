set(blitz_LIB_SRCS globals.cpp)
add_library(blitz SHARED ${blitz_LIB_SRCS})

if (ENABLE_SERIALISATION)
	set(Boost_USE_STATIC_LIBS        ON) # only find static libs
	set(Boost_USE_MULTITHREADED      ON)
	set(Boost_USE_STATIC_RUNTIME    OFF)
    find_package(Boost COMPONENTS serialization)
    if (Boost_SERIALIZATION_FOUND)
        message(STATUS "Boost serialization library found. ${Boost_LIBRARIES}")
    else()
        message(WARNING "Boost serialization library not found !")
    endif()
	target_link_libraries (blitz
		Boost::boost
		${Boost_LIBRARIES}
	)
endif()

add_dependencies(blitz generated-headers)

set_target_properties(blitz PROPERTIES
                      VERSION ${blitz_VERSION}
                      SOVERSION 0
                      CLEAN_DIRECT_OUTPUT 1)
if (WIN32 AND NOT MINGW)
	set_target_properties(blitz PROPERTIES
						  IMPORT_SUFFIX ".dll.lib")
endif()

set(BLITZ_LIBS blitz)

add_library(blitz-static STATIC ${blitz_LIB_SRCS})
add_dependencies(blitz-static generated-headers)
set(BLITZ_LIBS ${BLITZ_LIBS} blitz-static)
set_target_properties(blitz-static PROPERTIES
					  OUTPUT_NAME blitz
					  ${BLITZ-STATIC-DEFS}
					  CLEAN_DIRECT_OUTPUT 1)


install(TARGETS ${BLITZ_LIBS}
        EXPORT  ${PROJECT_NAME}Targets
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}" COMPONENT runtime
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}" COMPONENT devel
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}" COMPONENT devel
)
