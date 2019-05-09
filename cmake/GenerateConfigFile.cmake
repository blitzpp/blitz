#   Offer the user the choice of overriding the installation directories

include(GNUInstallDirs)

macro(PARSE_ARGUMENTS_GENERATE LIST_VARS DEFAULT_VAR)
    foreach(var ${LIST_VARS})
        unset(${var})
    endforeach ()

    set(CURRENT_VAR ${DEFAULT_VAR})
    foreach (arg ${ARGN})
        set(skip_this_arg FALSE)
        foreach(var ${LIST_VARS})
            if (${arg} STREQUAL ${var})
                set(CURRENT_VAR ${var})
                set(skip_this_arg TRUE)
                BREAK()
            endif()
        endforeach ()
        if (NOT skip_this_arg)
            set(${CURRENT_VAR} ${${CURRENT_VAR}} ${arg})
        endif()
    endforeach()
endmacro()

function(DumpFindPackage filename package options)
    file(APPEND ${filename} "if (NOT ${arg}_FOUND)\n")
    file(APPEND ${filename} "\tfind_package(${arg} ${options})\n")
    file(APPEND ${filename} "endif()\n")
endfunction()

macro(Dependencies ConfigName)
    PARSE_ARGUMENTS_GENERATE("LIBRARIES" "DEFAULT" ${ARGN})
    set(DepFileName ${CMAKE_CURRENT_BINARY_DIR}/${ConfigName}Dependencies.cmake)
    file(WRITE ${DepFileName} "")
    set(DEPLIBS)
    set(DEPINCS)
    foreach(arg ${LIBRARIES})
        set(HINTS ${PROJECT_BINARY_DIR}/../${arg} ${PROJECT_BINARY_DIR}/../Libs/${arg})
        set(var ${arg}_LIB)
        file(APPEND ${DepFileName} "find_library(${arg}_var ${arg} HINTS ${HINTS} NO_CMAKE_PACKAGE_REGISTRY QUIET)\n")
        file(APPEND ${DepFileName} "find_library(${arg}_var ${arg} PATHS ${CMAKE_INSTALL_FULL_DATADIR}/ NO_CMAKE_PACKAGE_REGISTRY QUIET)\n")
        file(APPEND ${DepFileName} "find_library(${arg}_var ${arg})\n\n")
        set(DEPLIBS ${DEPLIBS};\${${var}})
    endforeach()
    foreach(arg ${DEFAULT})
        if (DEFINED ${arg}_command)
            set(pkg_command ${${arg}_command})
        else()
            set(pkg_command ${arg})
        endif()
        set(HINTS ${PROJECT_BINARY_DIR}/../${arg} ${PROJECT_BINARY_DIR}/../Libs/${arg})
        DumpFindPackage(${DepFileName} ${arg} "HINTS ${HINTS} NO_CMAKE_PACKAGE_REGISTRY QUIET")
        DumpFindPackage(${DepFileName} ${arg} "PATHS ${CMAKE_INSTALL_FULL_DATADIR}/ NO_CMAKE_PACKAGE_REGISTRY QUIET")
        DumpFindPackage(${DepFileName} ${arg} "REQUIRED")
        file(APPEND ${DepFileName} "\n")
        set(DEPLIBS ${DEPLIBS};\${${arg}_LIBRARIES})
        set(DEPINCS ${DEPINCS};\${${arg}_INCLUDE_DIRS})
    endforeach()
    include(${DepFileName})
endmacro()

function(GenerateConfigFile ConfigName)

    PARSE_ARGUMENTS_GENERATE("LIBRARIES;INCLUDES;INCLUDE_DIRS;PLUGINS_INCLUDE_DIRS" "DEFAULT" ${ARGN})

    #   Creating files for companion projects

    #   Export the package for use from the build-tree
    #   (this registers the build-tree with a global CMake-registry)

    export(PACKAGE ${ConfigName})

    set(INCLUDE_DIRS_ORIG "${INCLUDE_DIRS}")

    #   Create a XXXConfig.cmake file for the use from the build tree

    set(LIB_DIRS             "${CMAKE_BINARY_DIR}/lib")
    set(INCLUDE_DIRS         "${CMAKE_SOURCE_DIR}" "${CMAKE_BINARY_DIR}")
    set(CONFIG_DIR           "${CMAKE_BINARY_DIR}")

    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/XXXConfig.cmake.in
                   "${PROJECT_BINARY_DIR}/${ConfigName}Config.cmake" @ONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/XXXConfigVersion.cmake.in
                   "${PROJECT_BINARY_DIR}/${ConfigName}ConfigVersion.cmake" @ONLY)
 
    #   Install the export set for use with the install-tree

    install(EXPORT ${ConfigName} DESTINATION "${CMAKE_INSTALL_LIBDIR}/${ConfigName}/CMake" COMPONENT dev)
 
    #   Create a XXXConfig.cmake file for the use from the install tree and install it.

    set(LIB_DIRS             "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
    set(INCLUDE_DIRS         "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR};${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}/blitz/include/")
    set(CONFIG_DIR           "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}/${ConfigName}/CMake")

    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/XXXConfig.cmake.in
                   "${CMAKE_CURRENT_BINARY_DIR}/InstallFiles/${ConfigName}Config.cmake" @ONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/XXXConfigVersion.cmake.in
                   "${CMAKE_CURRENT_BINARY_DIR}/InstallFiles/${ConfigName}ConfigVersion.cmake" @ONLY)
    install(FILES
            "${CMAKE_CURRENT_BINARY_DIR}/InstallFiles/${ConfigName}Config.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/InstallFiles/${ConfigName}ConfigVersion.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/${ConfigName}Dependencies.cmake"
            DESTINATION "${CONFIG_DIR}" COMPONENT dev)
endfunction()
