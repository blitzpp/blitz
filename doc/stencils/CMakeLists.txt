include(ParseArguments.cmake)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_BINARY_DIR})

add_custom_target(stencils ALL)

set(GENERATED_FILES)
macro(STENCIL_DOC name define)
    add_executable(${name} dump-stencil.cpp)
    target_compile_definitions(${name} PRIVATE -Dstenciltoapply=${name}_stencilop -Dstencilargs=${define})
    target_link_libraries(${name} blitz)
    set(texi ${name}.texi)
    add_custom_target(${texi}
                      DEPENDS ${name}
                      COMMAND $<TARGET_FILE:${name}> > ${texi} 2>&1 
                      OUTPUTS ${texi})
    add_dependencies(stencils ${texi})
    #   For some reason the generated files are not cleaned up (contrarily to what is said for cmake).
    set(GENERATED_FILES ${GENERATED_FILES} ${texi})
endmacro()
    
macro(GENERATE_STENCILS_DOCS)
    set(args ${ARGN})
    PARSE_ARGUMENTS(STENCIL "NORMAL;LAPLACIAN" "" ${args})
    foreach(texi ${STENCIL_NORMAL})
        STENCIL_DOC(${texi} "A,1")
    endforeach()
    foreach(texi ${STENCIL_LAPLACIAN})
        STENCIL_DOC(${texi} "A")
    endforeach()
endmacro()

set(NORMAL_STENCILS
    central12 central22 central32 central42 central14 central24 central34 central44
    forward11 forward21 forward31 forward41 forward12 forward22 forward32 forward42
    backward11 backward21 backward31 backward41 backward12 backward22 backward32 backward42)

set(LAPLACIAN_STENCILS Laplacian2D Laplacian2D4)

GENERATE_STENCILS_DOCS(NORMAL ${NORMAL_STENCILS} LAPLACIAN ${LAPLACIAN_STENCILS})

set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${GENERATED_FILES}")

#source_group(Stencils FILES ${NORMAL_STENCILS} ${LAPLACIAN_STENCILS})
