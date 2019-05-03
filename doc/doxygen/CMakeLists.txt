# Configure the script and the Doxyfile, then add target

find_package(Doxygen)

if (DOXYGEN_FOUND)
    if (NOT DOXYGEN_DOT_PATH)
        get_filename_component(DOT_PATH ${DOT} PATH)
    endif()

    set(top_srcdir ${CMAKE_SOURCE_DIR})
    set(top_builddir ${CMAKE_BINARY_DIR})
    set(enable_latex_docs YES)
    set(enable_html_docs YES)
    set(enable_dot YES)
    set(PACKAGE_NAME ${CMAKE_PROJECT_NAME})
    set(PACKAGE_VERSION ${blitz_VERSION})
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    add_custom_target(doxygen ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
                      DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    add_custom_target(doxygen-latex make
                      WORKING_DIRECTORY latex
                      DEPENDS doxygen)

    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html/ DESTINATION ${CMAKE_INSTALL_DOCDIR}/reference)
    install(FILES latex/refman.pdf DESTINATION ${CMAKE_INSTALL_DOCDIR})

    set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "html;latex;doxygen-warning")
endif()
