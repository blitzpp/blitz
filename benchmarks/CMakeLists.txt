#set(OTHER_BENCH tinydaxpy hao-he iter)
set(OTHER_BENCH tinydaxpy iter)

option(FORTRAN_BENCHMARKS "Enable Fortran benchmarks" OFF)
if (FORTRAN_BENCHMARKS)
    enable_language(Fortran OPTIONAL)
    set(daxpy_SOURCES daxpy.cpp fdaxpy.f fidaxpy.f)
    set(stencil_SOURCES stencil.cpp stencilf.f stencilf2.f)
    set(acoustic_SOURCES acoustic.cpp acousticf.f acousticf2.f)
    set(acou3d_SOURCES acou3db1.cpp acou3db2.cpp acou3db3.cpp acou3db4.cpp \ acou3d.cpp acou3df.f acou3df2.f )
    set(LOOP_KERNELS loop1 loop2 loop3 loop5 loop6 loop8 loop9 loop10 loop11
        loop12 loop13 loop14 loop15 loop16 loop17 loop18 loop19 loop21 loop22
        loop23 loop24 loop25 loop36 loop100 floop1 floop2 floop3 floop5 floop6 floop8 floop9 floop10 floop11
        floop12 floop13 floop14 floop15 floop16 floop17 floop18 floop19 floop21 floop22
        floop23 floop24 floop25 floop36)
    set(OTHER_BENCH ${OTHER_BENCH} arrdaxpy haney qcd stencil cfd)
    if (CMAKE_Fortran_COMPILER_SUPPORTS_F90)
        set(daxpy_SOURCES ${daxpy_SOURCES} daxpyf90.f90)
        set(stencil_SOURCES ${stencil_SOURCES} stencilf90.f90)
        set(acoustic_SOURCES ${acoustic_SOURCES} acousticf90.f90 acousticf902.f90)
        set(acou3d_SOURCES ${acou3d_SOURCES} acou3df90.f90 acou3df902.f90)
    endif()
endif()

add_custom_target(benchmark)

TESTS(benchmark ${LOOP_KERNELS} ${OTHER_BENCH})

add_custom_target(check-benchmarks
                  DEPENDS blitz benchmark
                  COMMAND ${CMAKE_BUILD_TOOL} test)

set(COMPILE_TIME_BENCHMARKS ctime1 ctime2 ctime3 ctime4 ctime5 ctime1v ctime2v ctime3v ctime4v ctime5v)
