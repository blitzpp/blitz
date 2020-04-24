add_custom_target(doc-examples)

macro(TEXI_FROM_SOURCE source)
    get_filename_component(name ${source} NAME_WE)
    set(texi ${name}.texi)
    add_custom_command(TARGET doc-examples
                       COMMAND sed -e 's/{/@{/' -e 's/}/@}/' ${CMAKE_CURRENT_SOURCE_DIR}/${source} | fold -s -w 80 > ${texi}
                       DEPENDS ${source}
                       OUTPUTS ${texi})
endmacro()

macro(OUTPUT_FROM_SOURCE source)
    get_filename_component(name ${source} NAME_WE)
    add_executable(${name} ${source})
    target_link_libraries(${name} blitz ${BLITZ_EXTRA_LIBRARIES})
    set(out ${name}.out)
    add_custom_command(TARGET doc-examples
                       COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${source} 2>&1 | fold -s -w 80 > ${out}
                       DEPENDS ${name}
                       OUTPUTS ${out})
endmacro()

set(GENERATED_FILES)
macro(GENERATE_EXAMPLES var)
    if (NOT "${var}" STREQUAL "texi" AND NOT "${var}" STREQUAL "out")
       message(ERROR,"Unknown output type: ${var}") 
    endif()
    set(ll)
    foreach(source ${ARGN})
        if ("${var}" STREQUAL "texi")
            TEXI_FROM_SOURCE(${source})
        else()
            OUTPUT_FROM_SOURCE(${source})
        endif()
        get_filename_component(name ${source} NAME_WE)
        list(APPEND ll ${name}.${var})
    endforeach()
    add_custom_target(${var} DEPENDS ${ll})
    set(GENERATED_FILES ${GENERATED_FILES} ${ll})
endmacro()

#TODO: Handle fixed-class.cpp fixed-point.h makefile.example io.data

set(EXAMPLES simple.cpp storage.cpp outer.cpp strideslice.cpp slicing.cpp debug.cpp
             output.cpp io.cpp dump.cpp xor.cpp cast.cpp range.cpp fixed.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_BINARY_DIR})

GENERATE_EXAMPLES(texi ${EXAMPLES} fixed-point.h)
GENERATE_EXAMPLES(out  ${EXAMPLES})

target_link_libraries(io blitz)

#   Per the documentation this should not be needed as OUTPUT of
#   ADD_CUSTOM_COMMAND should be automatically cleaned...

set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${GENERATED_FILES}")
