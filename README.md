[![Build Status](https://travis-ci.org/blitzpp/blitz.svg?branch=master)](https://travis-ci.org/blitzpp/blitz)
[![Windows Build status](http://ci.appveyor.com/api/projects/status/github/blitzpp/blitz?branch=master&svg=true)](https://ci.appveyor.com/project/blitzpp/blitz/branch/master)

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

Installing Blitz
================

We recommend that users consider using Spack to install Blitz++ (see
below; use `spack install blitz`).  For those who enjoy spending hours
upon hours installing software by hand...

Blitz++ is distributed with a GNU Autotools build.  Autotools was
originally developed to address the non-portability of hand-built
Makefiles.  It was a big step forward, and for the first time allowed
users to install programs on their own Unix/Linux system, without too
many hassles due to minor differences between Unices.  While
frequently easy to use for end users, Autotools is also arcane and
difficult to use.  It has since been supplanted by `CMake`, which
offers a somewhat more straightforward way of doing things.  It is our
recommendation that any new projects are produced with CMake builds
--- not Autotools or hand-built Makefiles.  See
[here](https://devmanual.gentoo.org/general-concepts/autotools/index.html)
--- or search around --- for more information on Autotools:

NOTES:

1. Autools-based tarballs are normally distributed with a
`./configure` script.  This is most convenient for the user, since
nothing special must be installed on the system for it to work.
Autotools-based Git repositories normally do *not* contain the
`./configure` script: because that script is a generated file, not an
original source file.  Anyone checking out an Autotools-based project
from a Git repository needs to run `autoreconf` to first generate the
`./configure` file; this is a fundamental fact of life when using
Autotools and Git.  Search around for instructions on how to do so.

Auto-Builders: Spack
=====================

Although Autotools is not in itself particularly difficult to use,
modern open source software stacks frequently require dozens or even
hundreds of packages for a particular project.  Blitz++ does not have
any dependencies, and is therefore pretty "easy" to install; but
typical projects that involve Blitz++ could require the installation
of many more packages.  Installing a dozen or more packages by hand is
slow, error-prone, and must be re-done every time something
foundational changes (compiler or OS version) --- in other words, hand
installation of packages is a waste of time.  Nobody hand-builds
assembly code today either.  Some things are better automated.

[Spack](https://spack.io) is an auto-installer that automates the
installation (and re-installation) of packages.  People have
successfully used it to manage software stacks for particular projects
involving over 100 packages --- which would previously have taken
weeks for one person to complete by hand.  We recommend that people
interested in Blitz++ use Spack for installation, for the following
reaosns:

1. Spack already knows the intricacies of building and installing
software --- including Autotools, Autoreconf, CMake, dependency
management, compiler versions, shared libraries, etc.  This is arcane,
tricky stuff that should not be foisted on everybody just because they
want to use open source software.

1. Spack already knows the package-specific "gotchas" involved in
installing any particular piece of software.  Many packages are quite
standard, and don't require much special knowledge beyond a general
understanding of Autotools or CMake --- but many others have a variety
of "gotchas": they require patches or workardounds for particular
situations, they use standard tools in non-standard ways, they have
bugs that require patching, they involve a one-off hand-built
Makefile; the list goes on.  Every package-specific "gotcha" requires
minutes or hours of effort to understand when installing that package
--- effort that does not help in installing any other package, nor
does it help the next person installing the same package.  This is a
big waste of time.  Spack knows the "gotchas" for each package so you
don't have to.

1. The use of Spack avoides the need for project authors (such as
those at Blitz++) to answer an unending stream of build questions,
almost all of which are entirely generic and have nothing to do with
the actual project.  If Spack fails on a particular package, and then
questions are asked on the Spack forum --- then people who spend every
day on build system minutea will be there to help.

1. Spack recipes provide a clear and concise explanation (in Python
code) of how to install a particular package.  For those who prefer to
continue stone age traditions, inspection of the Spack package will
tell exactly what is required to install a package by hand, including
the package-specific "gotchas."
