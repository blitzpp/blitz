add_library(BlitzHeaders INTERFACE)
add_library(Blitz::BlitzHeaders ALIAS BlitzHeaders)

target_include_directories(BlitzHeaders INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/..)


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

find_package(Boost 1.71 COMPONENTS serialization)

if (TARGET Boost::serialization)
    target_compile_definitions(BlitzHeaders INTERFACE BZ_HAVE_BOOST_SERIALIZATION)
    target_link_libraries(BlitzHeaders INTERFACE Boost::serialization)
endif()

string(TOLOWER ${CMAKE_BUILD_TYPE} cmake_build_type_tolower)
if (cmake_build_type_tolower STREQUAL "debug")
    message(STATUS "Blitz debugging flag on")
    target_compile_definitions(BlitzHeaders INTERFACE BZ_DEBUG)
endif()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in config.h)

add_subdirectory(generate) 
add_subdirectory(meta) 
add_subdirectory(array)

target_link_libraries(BlitzHeaders INTERFACE Blitz::Array Blitz::Meta Boost::serialization)

#install(FILES
       #${CMAKE_CURRENT_BINARY_DIR}/config.h
       #array-impl.h array.cc array.h bench.cc bench.h benchext.cc benchext.h blitz.h bounds.h bzdebug.h
       #compiler.h constpointerstack.h etbase.h et-forward.h funcs.h globeval.cc indexexpr.h indexmap-forward.h
       #levicivita.h limits-hack.h listinit.h memblock.cc memblock.h minmax.h numinquire.h numtrait.h ops.h
       #prettyprint.h promote.h range.h range.cc ranks.h reduce.h shapecheck.h simdtypes.h tau.h timer.h tinymat2.h
       #tinymat2.cc tinymat2io.cc tinyvec2.cc tinyvec2.h tinyvec2io.cc tm2fastiter.h tmevaluate.h tv2fastiter.h
       #tvevaluate.h traversal.cc traversal.h tuning.h tvcross.h tvecglobs.h update.h wrap-climits.h
       #${GENERATED_HEADERS}
       #DESTINATION include/blitz)
