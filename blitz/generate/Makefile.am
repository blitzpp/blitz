#
# Written by Patrick Guio <patrick.guio@fys.uio.no>
#

noinst_HEADERS = arroperands.h arroptuple.h bzfstream.h operands.h operands2.h optuple.h optuple2.h

noinst_PROGRAMS = genarrbops genmathfunc genvecbops genarruops genmatuops \
                  genvecuops genmatbops genpromote genvecwhere genvecbfn

genarrbops_SOURCES = genarrbops.cpp
genmathfunc_SOURCES = genmathfunc.cpp
genvecbops_SOURCES = genvecbops.cpp
genarruops_SOURCES = genarruops.cpp
genmatuops_SOURCES = genmatuops.cpp
genvecuops_SOURCES = genvecuops.cpp
genmatbops_SOURCES = genmatbops.cpp
genpromote_SOURCES = genpromote.cpp
genvecwhere_SOURCES = genvecwhere.cpp
genvecbfn_SOURCES = genvecbfn.cpp

%.h: 
	./$< 

%.cc: 
	./$< 

$(top_srcdir)/blitz/array/bops.cc: genarrbops
$(top_srcdir)/blitz/array/uops.cc: genarruops
$(top_srcdir)/blitz/matbops.h: genmatbops
$(top_srcdir)/blitz/mathfunc.h: genmathfunc
$(top_srcdir)/blitz/matuops.h: genmatuops
$(top_srcdir)/blitz/promote-old.h: genpromote
$(top_srcdir)/blitz/vecbops.cc: genvecbops
$(top_srcdir)/blitz/vecuops.cc: genvecuops
$(top_srcdir)/blitz/vecwhere.cc: genvecwhere
$(top_srcdir)/blitz/vecbfn.cc: genvecbfn

generate-headers: $(top_srcdir)/blitz/array/bops.cc \
$(top_srcdir)/blitz/array/uops.cc $(top_srcdir)/blitz/matbops.h \
$(top_srcdir)/blitz/mathfunc.h $(top_srcdir)/blitz/matuops.h \
$(top_srcdir)/blitz/promote-old.h $(top_srcdir)/blitz/vecbops.cc \
$(top_srcdir)/blitz/vecuops.cc $(top_srcdir)/blitz/vecwhere.cc \
 $(top_srcdir)/blitz/vecbfn.cc

all-am:
	$(MAKE) $(AM_MAKEFLAGS) generate-headers

clean-local:
	-rm -rf cxx_repository ti_files ii_files $(noinst_PROGRAMS)
