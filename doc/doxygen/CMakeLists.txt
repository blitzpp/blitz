# Configure the script and the Doxyfile, then add target

find_package(Doxygen)

if (DOXYGEN_FOUND)
    if (NOT DOXYGEN_DOT_PATH)
        get_filename_component(DOT_PATH ${DOT} PATH)
    endif()

    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    add_dependencies(blitz-doc doxygen_outputs)

    add_custom_target(doxygen_outputs
                      COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
                      COMMAND ${CMAKE_COMMAND} -E chdir latex; ${CMAKE_MAKE_PROGRAM}
                      DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html/ DESTINATION ${CMAKE_INSTALL_DOCDIR}/reference)
    install(FILES latex/refman.pdf DESTINATION ${CMAKE_INSTALL_DOCDIR})

    set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "html;latex;doxygen-warning")
endif()
