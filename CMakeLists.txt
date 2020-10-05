cmake_minimum_required(VERSION 3.16) # FindPython

#   Blitz version and release date.

set(blitz_MAJOR 1)
set(blitz_MINOR 0)
set(blitz_PATCH 3)
set(blitz_VERSION ${blitz_MAJOR}.${blitz_MINOR}.${blitz_PATCH})
set(BZ_PACKAGE_STRING "${CMAKE_PROJECT_NAME} ${blitz_MAJOR}.${blitz_MINOR}")

# Set the project

project(blitz VERSION ${blitz_VERSION}  
              LANGUAGES CXX
              DESCRIPTION "A multi-array library -- fork by András Vukics"
              HOMEPAGE_URL "https://github.com/vukics/blitz")

# Ubuntu 20.04LTS versions for compilers

set(GCC_MINIMAL 9.3)
set(CLANG_MINIMAL 10.0)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU AND ${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS ${GCC_MINIMAL})
  message(FATAL_ERROR "GCC g++ version >= ${GCC_MINIMAL} needed.")
endif ()

if (${CMAKE_CXX_COMPILER_ID} STREQUAL Clang AND ${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS ${CLANG_MINIMAL})
  message(FATAL_ERROR "Clang version >= ${CLANG_MINIMAL} needed.")
endif ()

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

#   Packaging

set(CPACK_GENERATOR "TGZ")
set(CPACK_PACKAGE_VERSION_MAJOR ${blitz_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${blitz_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${blitz_PATCH})
set(CPACK_SOURCE_GENERATOR "TBZ2")
set(CPACK_SOURCE_PACKAGE_FILE_NAME blitz-${blitz_VERSION})
set(CPACK_SOURCE_IGNORE_FILES ".*.swp$" ".*.swo$" "~$" ".bz2$" ".gz$")

include(CPack)
include(UnitTests)
include(GNUInstallDirs)
include(CreatePkgConfig)
include(CMakePackageConfigHelpers)

add_subdirectory(blitz)
add_subdirectory(src)

add_library(Blitz INTERFACE)
add_library(Blitz::Blitz ALIAS Blitz)

target_include_directories(Blitz INTERFACE .)
target_link_libraries(Blitz INTERFACE Blitz::BlitzHeaders Blitz::BlitzLib)

add_subdirectory(testsuite)

#   Configuration files.

CreatePkgConfigInfo(blitz "")
CreatePkgConfigInfo(blitz-static static)

write_basic_package_version_file(
    cmake/${PROJECT_NAME}ConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion)
configure_package_config_file(
    cmake/${PROJECT_NAME}Config.cmake.in
    cmake/${PROJECT_NAME}Config.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/)

#   Installation

#install(EXPORT ${PROJECT_NAME}Targets DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake)
#install(FILES
        #${CMAKE_BINARY_DIR}/blitz.pc
		#${CMAKE_BINARY_DIR}/blitz-static.pc 
        #DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
#install(FILES
        #${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}Config.cmake
        #${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}ConfigVersion.cmake
        #DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/)
