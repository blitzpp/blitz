#
# Written by Patrick Guio <patrick.guio@fys.uio.no>
#

ACLOCAL_AMFLAGS  = -I m4

SUBDIRS = bin blitz random lib testsuite \
	examples benchmarks doc manual

EXTRA_DIST = LEGAL LICENSE README.binutils README-VS.NET.txt Blitz-VS.NET.zip \
	ChangeLog.1 

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = blitz.pc blitz-uninstalled.pc

lib: blitz-library

blitz-library:
	@(cd lib && $(MAKE) $(AM_MAKEFLAGS)) || exit 1;

check-testsuite: lib
	@(cd testsuite && $(MAKE) $(AM_MAKEFLAGS) $@) || exit 1;

check-examples: lib
	@(cd examples && $(MAKE) $(AM_MAKEFLAGS) $@) || exit 1;

check-benchmarks: lib
	@(cd benchmarks && $(MAKE) $(AM_MAKEFLAGS) $@) || exit 1;

clean-local:
	-rm -rf .deps so_locations cxx_repository 

