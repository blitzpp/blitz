#
# Written by Patrick Guio <patrick.guio@fys.uio.no>
#

generatedir = $(builddir)/blitz/generate

noinst_HEADERS = arroperands.h arroptuple.h bzfstream.h operands.h operands2.h optuple.h optuple2.h

noinst_PROGRAMS = genarrbops genmathfunc genvecbops genarruops genmatuops \
                  genvecuops genmatbops genpromote genvecwhere

genarrbops_SOURCES = genarrbops.cpp
genmathfunc_SOURCES = genmathfunc.cpp
genvecbops_SOURCES = genvecbops.cpp
genarruops_SOURCES = genarruops.cpp
genmatuops_SOURCES = genmatuops.cpp
genvecuops_SOURCES = genvecuops.cpp
genmatbops_SOURCES = genmatbops.cpp
genpromote_SOURCES = genpromote.cpp
genvecwhere_SOURCES = genvecwhere.cpp

clean-local:
	-rm -rf cxx_repository ti_files
