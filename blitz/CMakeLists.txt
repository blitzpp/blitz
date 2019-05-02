include(CheckCXXFeatures)

option(BZ_FULLY64BIT "Enable 64 dimensions with > 2^31 elements (NOT IMPLEMENTED)" OFF)
option(BZ_THREADSAFE "Enable Blitz thread-safety features" OFF)

option(TBB "Use Intel Threading Building Blocks atomic types" OFF)
if (TBB)
    set(BZ_THREADSAFE_USE_TBB TRUE)
    CHECK_HEADER(BZ_HAVE_TBB_ATOMIC_H "tbb/atomic.h")
endif()

option(SIMD_EXTENSION "Facilitate compiler vectorization optimizations for SIMD instruction width of n bytes." OFF)
if (SIMD_EXTENSION)
    set(USE_ALIGNMENT_PRAGMAS TRUE)
    CHECK_ALIGNMENT_DIRECTIVE(BZ_)
    set(BZ_SIMD_WIDTH 1 CACHE STRING "Size of simd types in bytes.")
    if (BZ_SIMD_WIDTH GREATER 1)
        option(ARRAY_LENGTH_PADDING "Sets the default array padding policy to pad all lowest-rank lengths to nearest larger SIMD width. Caution: This means that arrays will in general be non-contiguous." OFF)
        if (ARRAY_LENGTH_PADDING)
            set(BZ_PAD_ARRAYS TRUE)
        endif()
    endif()
else()
    set(BZ_SIMD_WIDTH 1)
endif()

set(EXTRA_LIBS)
option(ENABLE_SERIALISATION "Enable serialization support using Boost::Serialization" OFF)
if (ENABLE_SERIALISATION)
    find_package(Boost COMPONENTS serialization)
    if (Boost_FOUND)
        set(BZ_HAVE_BOOST TRUE)
        include_directories(${Boost_INCLUDE_DIRS})
        if (Boost_SERIALIZATION_FOUND)
            set(DEP_PKGS ${DEP_PKGS} Boost)
            set(BOOST_command "Boost COMPONENTS serialization" PARENT_SCOPE)
            set(BZ_HAVE_BOOST_SERIALIZATION TRUE)
            set(EXTRA_LIBS ${EXTRA_LIBS} ${BOOST_LIBRARIES})
        else()
            message(WARNING "Boost serialization library not found !")
        endif()
    endif()
endif()

find_library(BZ_HAVE_LIBPAPI papi)
if (BZ_HAVE_LIBPAPI)
    set(DEP_LIBS ${DEP_LIBS} papi)
    set(EXTRA_LIBS ${EXTRA_LIBS} ${BZ_HAVE_LIBPAPI})
    set(PKGCONFIG_LIBS ${PKGCONFIG_LIBS} -lpapi)
endif()

find_library(BZ_HAVE_LIBM m)
if (BZ_HAVE_LIBM)
    set(DEP_LIBS ${DEP_LIBS} m)
    set(EXTRA_LIBS ${EXTRA_LIBS} ${BZ_HAVE_LIBM})
    set(PKGCONFIG_LIBS ${PKGCONFIG_LIBS} -lm)
endif()
set(BLITZ_EXTRA_LIBRARIES ${EXTRA_LIBS} PARENT_SCOPE)
set(DEPS ${DEP_PKGS} LIBRARIES ${DEP_LIBS} PARENT_SCOPE)

if (NOT CHECKED_COMPILER_CXX_FEATURES)
    CHECK_ALL_CXX_FEATURES(BZ_)
    CHECK_HEADER(HAVE_INTTYPES_H inttypes.h)
    set(BZ_MATH_ABSINT_IN_NAMESPACE_STD ${BZ_HAVE_MATH_ABSINT_IN_NAMESPACE_STD})
    set(BZ_MATH_FN_IN_NAMESPACE_STD     ${BZ_HAVE_MATH_FN_IN_NAMESPACE_STD})
    set(BZ_ISNAN_IN_NAMESPACE_STD       ${BZ_HAVE_ISNAN_IN_NAMESPACE_STD})
    set(BZ_HAVE_NCEG_RESTRICT_EGCS      ${BZ_HAVE_RESTRICT_EGCS})
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.cmake.h.in ${BLITZ_CONFIG_FILE})
    set(CHECKED_COMPILER_CXX_FEATURES TRUE CACHE INTERNAL "Gating variable to avoid checking compiler features multiple times")
endif()

macro(GENERATE_BLITZ_HEADER header prog var)
    add_custom_target(${header} ALL)
    add_dependencies(${header} ${prog})
    add_dependencies(generated-headers ${header})
    add_custom_command(
        COMMAND $<TARGET_FILE:${prog}>
        TARGET  ${header}
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/blitz/generate
        OUTPUTS ${header}
    )
    set(${var} ${${var}} ${CMAKE_CURRENT_BINARY_DIR}/${header})
endmacro()

add_subdirectory(generate) 
add_subdirectory(meta) 
add_subdirectory(array)

set(GENERATED_HEADERS)
GENERATE_BLITZ_HEADER(vecbops.cc    genvecbops  GENERATED_HEADERS)
GENERATE_BLITZ_HEADER(vecuops.cc    genvecuops  GENERATED_HEADERS)
GENERATE_BLITZ_HEADER(vecwhere.cc   genvecwhere GENERATED_HEADERS)
GENERATE_BLITZ_HEADER(vecbfn.cc     genvecbfn   GENERATED_HEADERS)
GENERATE_BLITZ_HEADER(matbops.h     genmatbops  GENERATED_HEADERS)
GENERATE_BLITZ_HEADER(matuops.h     genmatuops  GENERATED_HEADERS)
GENERATE_BLITZ_HEADER(mathfunc.h    genmathfunc GENERATED_HEADERS)
GENERATE_BLITZ_HEADER(promote-old.h genpromote  GENERATED_HEADERS)

set(BLITZ_HEADERS
    array-impl.h array.cc array.h bench.cc bench.h benchext.cc benchext.h blitz.h bounds.h bzdebug.h bzconfig.h
    compiler.h constpointerstack.h etbase.h et-forward.h funcs.h globeval.cc indexexpr.h indexmap-forward.h
    levicivita.h limits-hack.h listinit.h memblock.cc memblock.h minmax.h numinquire.h numtrait.h ops.h
    prettyprint.h promote.h range.h range.cc ranks.h reduce.h shapecheck.h simdtypes.h tau.h timer.h tinymat2.h
    tinymat2.cc tinymat2io.cc tinyvec2.cc tinyvec2.h tinyvec2io.cc tm2fastiter.h tmevaluate.h tv2fastiter.h
    tvevaluate.h traversal.cc traversal.h tuning.h tvcross.h tvecglobs.h update.h wrap-climits.h)

foreach (i ${BLITZ_HEADERS})
    set(HEADERS ${HEADERS} ${CMAKE_CURRENT_SOURCE_DIR}/${i})
endforeach()

install(FILES ${HEADERS} ${GENERATED_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/blitz)
install(FILES ${BLITZ_CONFIG_FILE} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${BLITZ_CONFIG_INSTALL_DIR})
