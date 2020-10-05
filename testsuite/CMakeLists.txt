add_definitions(-DBZ_DEBUG)

add_executable(Adnene-Ben-Abdallah-1 Adnene-Ben-Abdallah-1.cpp)
target_link_libraries(Adnene-Ben-Abdallah-1 Blitz::Blitz)


#add_custom_target(testsuite)

#UNITTEST(testsuite module module1.cpp module2.cpp)

#TESTS(testsuite
      #Adnene-Ben-Abdallah-1 Adnene-Ben-Abdallah-2 arrayresize chris-jeffery-1 chris-jeffery-2
      #chris-jeffery-3 complex-test constarray contiguous copy ctors derrick-bass-1 derrick-bass-3
      #exprctor extract free gary-huber-1 initialize interlace iter Josef-Wagenhuber loop1
      #matthias-troyer-1 matthias-troyer-2 mattias-lindstroem-1 minmax minsumpow newet
      #Olaf-Ronneberger-1 patrik-jonsson-1 peter-bienstman-1 peter-bienstman-2 peter-bienstman-3
      #peter-bienstman-4 peter-bienstman-5 peter-nordlund-1  peter-nordlund-2 peter-nordlund-3
      #promote qcd reduce reindex reverse shapecheck shape storage strided-domain stub
      #theodore-papadopoulo-1 tinymat tinyvec transpose troyer-genilloud Ulisses-Mello-1
      #wei-ku-1 where zeek-1)

#add_custom_target(check-testsuite
                  #DEPENDS blitz testsuite
                  #COMMAND ${CMAKE_BUILD_TOOL} test)
