[![Build Status](https://travis-ci.org/blitzpp/blitz.svg?branch=master)](https://travis-ci.org/blitzpp/blitz)
[![Windows Build status](http://ci.appveyor.com/api/projects/status/github/blitzpp/blitz?branch=master&svg=true)](https://ci.appveyor.com/project/blitzpp/blitz/branch/master)

Blitz++ is a C++ template class library that provides array objects
for scientific computing.  It is not a linear algebra or fft library;
see http://oonumerics.org/oon or http://www.math.unipd.it/~michela/OP.htm
for libraries that will do those things.

Blitz has gone through some changes in location:

 1. The original Blitz website was located at http://oonumerics.org/blitz.  

 2. Blitz then moved to SourceForge, at http://www.sourceforge.net/projects/blitz.

 3. The latest maintained version of Blitz is now on GitHub, at  https://github.com/blitzpp/blitz

Licensing information is detailed in the LEGAL file.
Summary: you can do anything except sell this library in source
form.  Blitz is licensed under either the Lesser GPL version 3 license
(see COPYING and COPYING.LESSER), the BSD license (see COPYRIGHT), and
the less restrictive Perl "artistic license" version 2.0 (see LICENSE).


Downloading Blitz
-----------------

The latest version of Blitz++ is 1.0.1.  The tarball may be downloaded
at:

   https://codeload.github.com/blitzpp/blitz/legacy.tar.gz/1.0.1


Directories
-----------

blitz         Blitz++ headers and source files
blitz/meta    Blitz++ template metaprogramming headers
blitz/array   Blitz++ headers for Array class
random        Blitz++ headers for random number generation
src           Blitz++ source files compiled into library
doc           Current Blitz documentation using .texi and doxygen.
manual        Original Blitz manual in HTML and PS format (not updated)
m4            Local m4 macros used by autoconf/automake
compiler      Compiler tests (used with obsolete bzconfig script)  
testsuite     Test suite 
examples      Example programs 
benchmarks    Benchmark programs 
lib           Build area for Blitz++ library


Compiling programs
------------------

All Blitz++ header files are referred to with a prefix of "blitz/".
For example, to use the Array<T,N> class, one needs to include
<blitz/array.h> instead of just <array.h>.
To make this work, the main Blitz++ directory must be in
your include path.  For example, if Blitz++ was installed
in /software/Blitz++, you will need to compile with
-I/software/Blitz++ and -L/software/Blitz++/lib -lblitz

To summarize, a typical command line is:

g++ foo.cpp -o foo -I/software/Blitz++ -L/software/Blitz++/lib -lblitz

To avoid the -I and -L options, you can set up symbolic links -- see
INSTALL for details.

Email addresses
---------------

Please report bugs to <blitz-support@lists.sourceforge.net> 
or submit a bug report on the SourceForge website at 
http://www.sourceforge.net/projects/blitz.

Please send ideas or feature requests to <blitz-devel@lists.sourceforge.net>
or submit them on the Blitz++ SourceForge website.


Legal mumbo-jumbo
-----------------

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

