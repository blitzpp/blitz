#
# Written by Patrick Guio <patrick.guio@fys.uio.no>
#

docdir = $(prefix)/doc/blitz/examples

doc_DATA = cast.cpp debug.cpp dump.cpp fixed.cpp fixed-point.h outer.cpp \
output.cpp range.cpp simple.cpp slicing.cpp storage.cpp strideslice.cpp \
xor.cpp

EXTRA_DIST = $(doc_DATA)

INCLUDES = -I$(top_srcdir)
AM_CXXFLAGS = @CXXFLAGS@ @CXX_DEBUG_FLAGS@
LDADD = -L$(top_srcdir)/lib -lblitz

EXAMPLES = simple storage outer strideslice slicing debug output io dump xor \
cast range fixed

EXTRA_PROGRAMS =  $(EXAMPLES)

simple_SOURCES = simple.cpp
storage_SOURCES = storage.cpp
outer_SOURCES = outer.cpp
strideslice_SOURCES = strideslice.cpp
slicing_SOURCES = slicing.cpp
debug_SOURCES = debug.cpp
output_SOURCES = output.cpp
io_SOURCES = io.cpp
dump_SOURCES = dump.cpp
xor_SOURCES = xor.cpp
cast_SOURCES = cast.cpp
range_SOURCES = range.cpp
fixed_SOURCES = fixed.cpp

%.texi : 
	sed -e 's/{/@{/' -e 's/}/@}/' $< | fold -s -w 80 > $@

%.out : %
	./$< 2>&1 | fold -s -w 80 > $@

simple.texi: simple.cpp
storage.texi: storage.cpp
outer.texi: outer.cpp
strideslice.texi: strideslice.cpp
slicing.texi: slicing.cpp
debug.texi: debug.cpp
output.texi: output.cpp
io.texi: io.cpp
dump.texi: dump.cpp
xor.texi: xor.cpp
cast.texi: cast.cpp
range.texi: range.cpp
fixed.texi: fixed.cpp
fixed-point.texi: fixed-point.h

simple.out: simple
storage.out: storage
outer.out: outer
strideslice.out: strideslice
slicing.out: slicing
debug.out: debug
output.out: output
io.out: io
dump.out: dump
xor.out: xor
cast.out: cast
range.out: range
fixed.out: fixed

texi: simple.texi storage.texi outer.texi strideslice.texi slicing.texi \
debug.texi output.texi io.texi dump.texi xor.texi cast.texi range.texi \
fixed.texi fixed-point.texi

out: simple.out storage.out outer.out strideslice.out slicing.out \
debug.out output.out io.out dump.out xor.out cast.out range.out fixed.out

all-am:
	$(MAKE) $(AM_MAKEFLAGS) -i texi
	$(MAKE) $(AM_MAKEFLAGS) -i out

clean-local:
	-rm -rf cxx_repository $(EXTRA_PROGRAMS) *.texi *.out core.[0-9]*


