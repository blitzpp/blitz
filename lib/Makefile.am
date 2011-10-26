#
# Written by Patrick Guio <patrick.guio@fys.uio.no>
#

EXTRA_DIST = readme.txt

AM_CPPFLAGS = -I$(top_srcdir) -I$(top_builddir) $(BOOST_CPPFLAGS)

lib_LTLIBRARIES = libblitz.la
libblitz_la_SOURCES = $(top_srcdir)/src/globals.cpp
libblitz_la_LIBADD = $(LIBS) $(CXX_LIBS)


clean-local:
	-rm -rf *.ii *.ti cxx_repository Template.dir ii_files ti_files

