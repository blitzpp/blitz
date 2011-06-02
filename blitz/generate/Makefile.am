#
# Written by Patrick Guio <patrick.guio@fys.uio.no>
#

noinst_HEADERS = arroperands.h arroptuple.h bzfstream.h operands.h operands2.h optuple.h optuple2.h

EXTRA_PROGRAMS = genarrbops genarruops genmathfunc genvecbops genmatuops \
                 genvecuops genmatbops genvecwhere genvecbfn genpromote

genarrbops_SOURCES = genarrbops.cpp
genarruops_SOURCES = genarruops.cpp
genmatbops_SOURCES = genmatbops.cpp
genmatuops_SOURCES = genmatuops.cpp
genmathfunc_SOURCES = genmathfunc.cpp
genvecbops_SOURCES = genvecbops.cpp
genvecuops_SOURCES = genvecuops.cpp
genvecwhere_SOURCES = genvecwhere.cpp
genvecbfn_SOURCES = genvecbfn.cpp
genpromote_SOURCES = genpromote.cpp

$(top_srcdir)/blitz/array/bops.cc: genarrbops.cpp
$(top_srcdir)/blitz/array/uops.cc: genarruops.cpp
$(top_srcdir)/blitz/matbops.h: genmatbops.cpp
$(top_srcdir)/blitz/matuops.h: genmatuops.cpp
$(top_srcdir)/blitz/mathfunc.h: genmathfunc.cpp
$(top_srcdir)/blitz/vecbops.cc: genvecbops.cpp
$(top_srcdir)/blitz/vecuops.cc: genvecuops.cpp
$(top_srcdir)/blitz/vecwhere.cc: genvecwhere.cpp
$(top_srcdir)/blitz/vecbfn.cc: genvecbfn.cpp
$(top_srcdir)/blitz/promote-old.h: genpromote.cpp

$(top_srcdir)/blitz/array/stencil-classes.cc: genstencils.py
	python $< $@

generate-headers: $(top_srcdir)/blitz/array/bops.cc \
$(top_srcdir)/blitz/array/uops.cc \
$(top_srcdir)/blitz/array/stencil-classes.cc \
$(top_srcdir)/blitz/matbops.h \
$(top_srcdir)/blitz/matuops.h $(top_srcdir)/blitz/mathfunc.h \
$(top_srcdir)/blitz/vecuops.cc $(top_srcdir)/blitz/vecbops.cc \
$(top_srcdir)/blitz/vecwhere.cc $(top_srcdir)/blitz/vecbfn.cc \
$(top_srcdir)/blitz/promote-old.h

all-local: $(EXTRA_PROGRAMS)
	$(MAKE) $(AM_MAKEFLAGS) generate-headers

clean-local:
	-rm -rf cxx_repository ti_files ii_files $(EXTRA_PROGRAMS)


%.h: 
	./$(patsubst %.cpp,%$(EXEEXT),$<)

%.cc: 
	./$(patsubst %.cpp,%$(EXEEXT),$<)


