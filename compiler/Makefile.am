#
# Written by Patrick Guio <patrick.guio@fys.uio.no>
# $Revision$
#

SUBDIRS=

EXTRA_DIST = LEGAL README bool.cpp bzconfig climits.cpp cmthscop.cpp \
complex.cpp compmath.cpp constcst.cpp cstd.cpp default.cpp \
dynamic.cpp elabbase.cpp elabret.cpp enumcmp2.cpp enumcomp.cpp except.cpp \
explicit.cpp fullspec.cpp getruse.cpp ieeemath.cpp instant.cpp \
mathscop.cpp membcnst.cpp membtmp2.cpp membtmpl.cpp mutable.cpp \
namespac.cpp nontype.cpp numlimit.cpp numtrait.cpp oldfor.cpp partial.cpp \
porder.cpp promote.cpp reinterp.cpp restric2.cpp restrict.cpp rtti.cpp \
statcast.cpp std.cpp stl.cpp sysvmath.cpp tempkey.cpp template.cpp \
tempqmt.cpp tempqual.cpp temptemp.cpp typename.cpp vac.icc valarray.cpp

BZ_CONFIG_H = $(top_srcdir)/blitz/config.h

all-am: check-compiler

check-compiler: $(BZ_CONFIG_H)

$(BZ_CONFIG_H):	$(srcdir)/bzconfig
	$(srcdir)/bzconfig --compiler=$(CXX) --flags="$(CXXFLAGS)" --srcdir=$(srcdir)
	cp config.h $(BZ_CONFIG_H)

clean-local:
	-rm -rf bzjunk bzjunk.cpp bztemp bztest config.h logfile cxx_repository

