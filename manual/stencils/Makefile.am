#
# Written by Patrick Guio <patrick.guio@fys.uio.no>
#

SUBDIRS = .

docdir = $(prefix)/doc/blitz/stencils
doc_DATA = Laplacian2D.yo Laplacian2D4.yo backward11.yo backward12.yo \
backward21.yo backward22.yo backward31.yo backward32.yo backward41.yo \
backward42.yo central12.yo central14.yo central22.yo central24.yo central32.yo \
central34.yo central42.yo central44.yo dump-stencil.cpp dump1D dumpdiffs dumpst \
forward11.yo forward12.yo forward21.yo forward22.yo forward31.yo forward32.yo \
forward41.yo forward42.yo

EXTRA_DIST = $(doc_DATA)

INCLUDES = -I$(top_srcdir)
CXXFLAGS = @CXXFLAGS@ @CXX_DEBUG_FLAGS@ -Dstenciltodump=Laplacian2D4
LDADD = -L$(top_srcdir)/lib -lblitz

SINGLE_TESTS = dump-stencil

MULTIPLE_TESTS = modules

EXTRA_PROGRAMS = $(SINGLE_TESTS)

dump_stencil_SOURCES = dump-stencil.cpp

check-examples: $(EXTRA_PROGRAMS)
	@echo Running test suite...
	@for prog in $(EXTRA_PROGRAMS) ; do \
		echo $$prog && (./$$prog > /dev/null 2>&1) || exit 1; \
		done
	@echo All tests passed.

clean-local:
	-rm -rf cxx_repository $(EXTRA_PROGRAMS)

