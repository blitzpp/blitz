#
# Written by Patrick Guio <patrick.guio@fys.uio.no>
#

AUTOMAKE_OPTIONS = foreign

SUBDIRS = bin compiler blitz random src lib testsuite \
	examples benchmarks doc manual

EXTRA_DIST = LEGAL LICENSE README.binutils README-VS.NET Blitz-VS.NET.zip \
	ChangeLog.1 

# demodir = $(prefix)/demos
# demo_DATA = demos/Makefile

check-compiler:
	@(cd compiler && $(MAKE) $(AM_MAKEFLAGS) $@) || exit 1;

check-testsuite: lib
	@(cd testsuite && $(MAKE) $(AM_MAKEFLAGS) $@) || exit 1;

check-examples: lib
	@(cd examples && $(MAKE) $(AM_MAKEFLAGS) $@) || exit 1;

check-benchmarks: lib
	@(cd benchmarks && $(MAKE) $(AM_MAKEFLAGS) $@) || exit 1;

lib: check-compiler
	@(cd lib && $(MAKE) $(AM_MAKEFLAGS)) || exit 1;

clean-local:
	-rm -rf .deps

