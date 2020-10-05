add_executable(genarrbops  genarrbops.cpp)
add_executable(genarruops  genarruops.cpp)
add_executable(genmatbops  genmatbops.cpp)
add_executable(genmatuops  genmatuops.cpp)
add_executable(genvecbops  genvecbops.cpp)
add_executable(genvecuops  genvecuops.cpp)
add_executable(genvecwhere genvecwhere.cpp)
add_executable(genvecbfn   genvecbfn.cpp)
add_executable(genmathfunc genmathfunc.cpp)
add_executable(genpromote  genpromote.cpp)

find_package(Python 3.8 REQUIRED COMPONENTS Interpreter)

add_custom_target(stencil-classes.cc ALL
                  COMMAND ${Python_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/genstencils.py stencil-classes.cc
                  MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/genstencils.py)
