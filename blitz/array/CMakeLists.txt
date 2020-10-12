add_library(Array INTERFACE)
add_library(Blitz::Array ALIAS Array)

target_include_directories(Array INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/../..")

#install(FILES
        #asexpr.h asexpr.cc cartesian.h cgsolve.h complex.cc convolve.cc convolve.h cycle.cc domain.h et.h expr.h expr.cc
        #fastiter.h funcs.h functorExpr.h geometry.h indirect.h interlace.cc io.cc iter.h map.h methods.cc misc.cc multi.h
        #newet-macros.h newet.h ops.cc ops.h reduce.cc reduce.h resize.cc shape.h slice.h slicing.cc stencil-et.h
        #stencil-et-macros.h stencilops.h stencils.cc stencils.h storage.h where.h zip.h
        #${BLITZ_ARRAY_GENERATED_HEADERS}
        #DESTINATION include/blitz/array)
