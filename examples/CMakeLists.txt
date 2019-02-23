# Old examples that have been removed... Add then again ?
#      cfd curldiv diff erf indirect pauli pick profile qcd rangexpr stencil3 stencil stencilet tiny2 tiny3 transform)

add_custom_target(examples)

set(ALL_EXAMPLES
      array cartesian cast complex-test convolve deriv fixed
      io iter matmult nested numinquire outer polymorph prettyprint
      rand2 random reduce simple slicing stencil2 
      storage tiny useret where whitt)

TESTS(examples ${ALL_EXAMPLES})

add_custom_target(check-examples
                  DEPENDS blitz examples
                  COMMAND ${CMAKE_BUILD_TOOL} test)

set(EXAMPLES)
foreach (example ${ALL_EXAMPLES})
    list(APPEND EXAMPLES ${example}.cpp)
endforeach()

install(FILES ${EXAMPLES} DESTINATION ${CMAKE_INSTALL_DOCDIR}/examples)
