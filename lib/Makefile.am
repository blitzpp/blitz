#
# Written by Patrick Guio <patrick.guio@fys.uio.no>
#

EXTRA_DIST = readme.txt

AM_CPPFLAGS = -I$(srcdir) -I$(top_srcdir) -I$(top_builddir)

lib_LTLIBRARIES = libblitz.la
libblitz_la_SOURCES = $(top_srcdir)/src/globals.cpp


clean-local:
	-rm -rf cxx_repository ti_files

