# Configure the script and the Doxyfile, then add target

find_package(Doxygen)

if (DOXYGEN_FOUND)
    if (NOT DOXYGEN_DOT_PATH)
        get_filename_component(DOT_PATH ${DOT} PATH)
    endif()

    option(DISABLE_REFMAN_PDF "Disable generation of refman.pdf" OFF)

    set(top_srcdir ${CMAKE_SOURCE_DIR})
    set(top_builddir ${CMAKE_BINARY_DIR})
    set(enable_latex_docs YES)
    set(enable_html_docs YES)
    set(enable_dot YES)
    set(PACKAGE_NAME ${CMAKE_PROJECT_NAME})
    set(PACKAGE_VERSION ${blitz_VERSION})
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)

    add_custom_target(doxygen ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
                      DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html/ DESTINATION ${CMAKE_INSTALL_DOCDIR}/reference)
    add_dependencies(blitz-doc doxygen)

    if (NOT DISABLE_REFMAN_PDF)
        add_custom_command(OUTPUT latex/refman.pdf
                           COMMAND make
                           WORKING_DIRECTORY latex
                           DEPENDS doxygen)

        add_custom_target(doxygen-latex DEPENDS latex/refman.pdf)
        install(FILES ${CMAKE_CURRENT_BINARY_DIR}/latex/refman.pdf DESTINATION ${CMAKE_INSTALL_DOCDIR})
        add_dependencies(blitz-doc doxygen-latex)
    endif()

    set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "html;latex;doxygen-warning")
endif()
