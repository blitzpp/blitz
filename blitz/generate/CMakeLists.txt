foreach(X b u)
  add_executable("genarr${X}ops" "genarr${X}ops.cpp")
  add_custom_command(TARGET "genarr${X}ops"
                     POST_BUILD
                     COMMAND $<TARGET_FILE:genarr${X}ops>
                     BYPRODUCTS "../array/${X}ops.cc"
                     WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/
                     COMMENT "built genarr${X}ops, now generating ../array/${X}ops.cc")
endforeach()

#add_executable(genarrbops  genarrbops.cpp)

#add_custom_command(TARGET genarrbops
                   #POST_BUILD
                   #COMMAND $<TARGET_FILE:genarrbops>
                   #BYPRODUCTS ../array/bops.cc
                   #WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/
                   #COMMENT "built genarrbops, now generating ../array/bops.cc")

#add_executable(genarruops  genarruops.cpp)

macro(GENERATE_GENERATED_HEADER prog header)
    add_executable(${prog} "${prog}.cpp")
    add_custom_command(TARGET ${prog}
                       POST_BUILD
                       COMMAND $<TARGET_FILE:${prog}>
                       BYPRODUCTS ../${header}
                       WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/
                       COMMENT "built ${prog}, now generating ${header}")
endmacro()

GENERATE_GENERATED_HEADER(genmatbops  matbops.h)
GENERATE_GENERATED_HEADER(genmatuops  matuops.h)
GENERATE_GENERATED_HEADER(genvecbops  vecbops.cc)
GENERATE_GENERATED_HEADER(genvecuops  vecuops.cc)
GENERATE_GENERATED_HEADER(genvecwhere vecwhere.cc)
GENERATE_GENERATED_HEADER(genvecbfn   vecbfn.cc)
GENERATE_GENERATED_HEADER(genpromote  promote-old.h)

find_package(Python 3.8 REQUIRED COMPONENTS Interpreter)

#add_custom_target(genStencilClasses ALL
                  #DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/genstencils.py
                  #COMMAND ${Python_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/genstencils.py stencil-classes.cc
                  #BYPRODUCTS stencil-classes.cc
                  #COMMENT "Generating stencil-classes.cc by genstencils.py")
                  
