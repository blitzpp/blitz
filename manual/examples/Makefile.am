#
# Written by Patrick Guio <patrick.guio@fys.uio.no>
#

docdir = $(prefix)/doc/blitz/examples
doc_DATA = cast.cpp debug.cpp dump.cpp fixed.cpp outer.cpp outer.log output.cpp \
output.log range.cpp simple.cpp simple.log slicing.cpp storage.cpp storage.log \
strideslice.cpp xor.cpp

EXTRA_DIST = $(doc_DATA)

INCLUDES = -I$(top_srcdir)
AM_CXXFLAGS = @CXXFLAGS@ @CXX_DEBUG_FLAGS@
LDADD = -L$(top_srcdir)/lib -lblitz

# Uncomment for debug version
#DFLAGS  = -DBZ_DEBUG -g +K0
#DFLAGS  = -DBZ_DEBUG -DBZ_DEBUG_LOG_ALLOCATIONS -DBZ_DEBUG_LOG_REFERENCES -g +K0
# Uncomment for optimized version
#DFLAGS  = +K3 -O
# Uncomment to look at optimized assembly
#DFLAGS = -pg -O3 +K3

# KAI C++ 3.0
#CXXFLAGS = $(DFLAGS) -DTV_KCC --restrict \
#				 --no_implicit_include --abstract_pointer --keep_gen_c \
#				 --abstract_float --no_implicit_typename --no_old_specializations \
#				 --strict_warnings --diag_suppress 113 -tused -D_XOPEN_SOURCE
#CXX     = KCC


EXAMPLES = simple #slicing debug xor cast dump output outer strideslice range

EXTRA_PROGRAMS =  $(EXAMPLES)

simple_SOURCES = simple.cpp
#slicing_SOURCES = slicing.cpp
#debug_SOURCES = debug.cpp
#xor_SOURCES = xor.cpp
#cast_SOURCES = cast.cpp
#dump_SOURCES = dump.cpp
#output_SOURCES = output.cpp
#outer_SOURCES = outer.cpp
#strideslice_SOURCES = strideslice.cpp
#range_SOURCES = range.cpp

check-examples: $(EXTRA_PROGRAMS)
	@echo Running test suite...
	@for prog in $(EXTRA_PROGRAMS) ; do \
		echo $$prog && (./$$prog > /dev/null 2>&1) || exit 1; \
		done
	@echo All tests passed.

all-am:

clean-local:
	-rm -rf cxx_repository $(EXTRA_PROGRAMS)


