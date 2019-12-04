# ==============================
# = Fix DLL search pb on WIN32 =
# ==============================

IF (WIN32)
    SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/src")

    #   These are obsolete as per cmake 2.6

    SET(LIBRARY_OUTPUT_PATH "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
    SET(EXECUTABLE_OUTPUT_PATH "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
ENDIF()
