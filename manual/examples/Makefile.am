#
# Written by Patrick Guio <patrick.guio@fys.uio.no>
#

docdir = $(prefix)/doc/blitz/examples
doc_DATA = fixed.cpp outer.log output.log simple.log storage.log

EXTRA_DIST = $(doc_DATA)

AM_CPPFLAGS = -I$(srcdir) -I$(top_srcdir) -I$(top_builddir)
AM_CXXFLAGS = @CXX_DEBUG_FLAGS@
LDADD = -L$(top_builddir)/lib -lblitz

EXAMPLES = 	simple slicing debug xor cast dump output outer \
		strideslice range storage

EXTRA_PROGRAMS =  $(EXAMPLES)

simple_SOURCES = simple.cpp
slicing_SOURCES = slicing.cpp
debug_SOURCES = debug.cpp
xor_SOURCES = xor.cpp
cast_SOURCES = cast.cpp
dump_SOURCES = dump.cpp
output_SOURCES = output.cpp
outer_SOURCES = outer.cpp
strideslice_SOURCES = strideslice.cpp
range_SOURCES = range.cpp
storage_SOURCES = storage.cpp

check-examples: $(EXTRA_PROGRAMS)
	@echo Running test suite...
	@for prog in $(EXTRA_PROGRAMS) ; do \
		echo $$prog && (./$$prog > /dev/null 2>&1) || exit 1; \
		done
	@echo All tests passed.

all-am:

clean-local:
	-rm -rf cxx_repository $(EXTRA_PROGRAMS)


