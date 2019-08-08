set(BLITZ_ARRAY_HEADERS
    asexpr.h asexpr.cc cartesian.h cgsolve.h complex.cc convolve.cc convolve.h cycle.cc domain.h et.h expr.h expr.cc
    fastiter.h funcs.h functorExpr.h geometry.h indirect.h interlace.cc io.cc iter.h map.h methods.cc misc.cc multi.h
    newet-macros.h newet.h ops.cc ops.h reduce.cc reduce.h resize.cc shape.h slice.h slicing.cc stencil-et.h
    stencil-et-macros.h stencilops.h stencils.cc stencils.h storage.h where.h zip.h)

foreach(i ${BLITZ_ARRAY_HEADERS})
    set(HEADERS ${HEADERS} ${CMAKE_CURRENT_SOURCE_DIR}/${i})
endforeach()

GENERATE_BLITZ_HEADER(bops.cc genarrbops BLITZ_ARRAY_GENERATED_HEADERS)
GENERATE_BLITZ_HEADER(uops.cc genarruops BLITZ_ARRAY_GENERATED_HEADERS)

find_package (Python COMPONENTS Interpreter)

add_custom_target(stencil-classes.cc ALL
                  COMMAND ${Python_EXECUTABLE}  ${CMAKE_CURRENT_SOURCE_DIR}/../generate/genstencils.py stencil-classes.cc
                  MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/../generate/genstencils.py)
add_dependencies(generated-headers stencil-classes.cc)

set(BLITZ_ARRAY_GENERATED_HEADERS ${BLITZ_ARRAY_GENERATED_HEADERS} ${CMAKE_CURRENT_BINARY_DIR}/stencil-classes.cc)

install(FILES ${HEADERS} ${BLITZ_ARRAY_GENERATED_HEADERS} DESTINATION include/blitz/array)
