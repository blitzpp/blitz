#
# $Id$
#
# Patrick Guio <patrick.guio@fys.uio.no>
#

EXTRA_DIST = CHANGELOG LEGAL LICENSE config.h.in GPL README.binutils

demodir = $(prefix)/demos
demo_DATA = demos/Makefile

check-compiler:
	@(cd compiler && $(MAKE) $(AM_MAKEFLAGS) $@) || exit 1;

check-testsuite: lib
	@(cd testsuite && $(MAKE) $(AM_MAKEFLAGS) $@) || exit 1;

check-examples: lib
	@(cd examples && $(MAKE) $(AM_MAKEFLAGS) $@) || exit 1;

check-benchmarks: lib
	@(cd benchmarks && $(MAKE) $(AM_MAKEFLAGS) $@) || exit 1;

lib: check-compiler
	@(cd src && $(MAKE) $(AM_MAKEFLAGS) $@) || exit 1;

clean-local:
	-rm -rf .deps

