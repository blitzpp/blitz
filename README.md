[![Github Actions Build Status](https://github.com/blitzpp/blitz/workflows/main/badge.svg?branch=main)](https://github.com/blitzpp/blitz/actions)
[![Windows Build status](http://ci.appveyor.com/api/projects/status/github/blitzpp/blitz?branch=main&svg=true)](https://ci.appveyor.com/project/blitzpp/blitz/branch/main)

# IMPORTANT NOTICE

Blitz++ written for the C++98 standard, and is not able to make use of the substantial benefits that came with C++11.  Although it works as well as ever, as of 2024, Blitz++ is thoroughly obsolete, which results in a number of annoyances when using it in modern C++ code.

In the meantime, Fortran-90 / NumPy style arrays have received high-level thought in the C++ Standards community, resulting in `std::mdspan`.  I highly recommend anyone starting a new project to consider this alternative before using Blitz++.  MDSpan is part of C++23 and in theory should be supported by popular compilers "out of the box."  If your C++ compiler does not (yet) support MDSpan, I would try using the publicly available [Reference Implemenation](https://github.com/kokkos/mdspan).  Here is more information on MDSpan:

* https://en.cppreference.com/w/cpp/container/mdspan
* https://www.studyplan.dev/pro-cpp/mdspan
* https://www.osti.gov/servlets/purl/1646434

Blitz++ has not received new features for many years, and will not going forward either.  However, it is likely to be required for many years by a number of existing projects, and is provided here for users and developers of those projects.

# Overview

Blitz++ is a C++ template class library that provides high-performance multidimensional array containers
for scientific computing. 

Blitz++ has gone through some changes in location:

 1. The original Blitz++ website was located at ``http://oonumerics.org/blitz`` 
    (archived at http://www.math.unipd.it/~michela/OP.htm).  

 2. Blitz++ then moved to SourceForge, at http://www.sourceforge.net/projects/blitz.

 3. The latest maintained version of Blitz++ is now on GitHub, at https://github.com/blitzpp/blitz

Diverse information on Blitz++ is now being catalogued at the GitHub wiki:
http://github.com/blitzpp/blitz/wiki/

Licensing information is detailed in the LEGAL file.
Summary: you can do anything except sell this library in source
form.  Blitz is licensed under either the Lesser GPL version 3 license
(see COPYING and COPYING.LESSER), the BSD license (see COPYRIGHT), and
the less restrictive Perl "artistic license" version 2.0 (see LICENSE).

Blitz++ uses CMake for build, test and installation automation.
For details on using CMake consult https://cmake.org/documentation/
In short, the following steps should work on UNIX-like systems:

```
  mkdir build
  cd build
  cmake ..
  make lib
  sudo make install
```

On Windows try:
```
  md build
  cd build
  cmake ..
  cmake --build . --config Release
  cmake --build . --target install

```
