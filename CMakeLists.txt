cmake_minimum_required(VERSION 3.0)
cmake_policy(VERSION 3.1)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

#   Blitz version and release date.

set(blitz_MAJOR 0)
set(blitz_MINOR 10)
set(blitz_PATCH 0)
set(blitz_VERSION ${blitz_MAJOR}.${blitz_MINOR}.${blitz_PATCH})
set(blitz_Release "2013-08-24")
set(BZ_PACKAGE_STRING "${CMAKE_PROJECT_NAME} ${blitz_MAJOR}.${blitz_MINOR}")

#   Set the project

project(blitz VERSION ${blitz_VERSION} LANGUAGES CXX)

option(BUILD_DOC "Build documentation" OFF)
option(BUILD_TESTING "Build tests, examples and benchmarks" OFF)

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
include(BlitzConfigFileName)
include(Win32Compat)
include(CreatePkgConfig)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

include_directories(BEFORE SYSTEM ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR})

add_custom_target(generated-headers ALL)

set(PKGCONFIG_LIBS -lblitz)

add_subdirectory(blitz)
add_subdirectory(random)
add_subdirectory(lib)
if (BUILD_DOC)
    add_subdirectory(doc)
endif()

if (BUILD_TESTING)
    add_subdirectory(testsuite)
    add_subdirectory(examples)
    add_subdirectory(benchmarks)
endif()

#   Configuration files.

CreatePkgConfigInfo(blitz)

write_basic_package_version_file(
    cmake/${PROJECT_NAME}ConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion)
configure_package_config_file(
    cmake/${PROJECT_NAME}Config.cmake.in
    cmake/${PROJECT_NAME}Config.cmake
    INSTALL_DESTINATION lib/cmake/)

#   Installation

install(TARGETS ${PROJECT_NAME} ${STACK_UNWINDING_PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include)
install(EXPORT ${PROJECT_NAME}Targets DESTINATION lib/cmake)
install(FILES
        ${CMAKE_BINARY_DIR}/blitz.pc
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}Config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}ConfigVersion.cmake
        DESTINATION lib/cmake/)