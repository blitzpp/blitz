#
# Written by Patrick Guio <patrick.guio@fys.uio.no>
#

SUBDIRS = .

EXTRA_DIST = readme.txt

INCLUDES = -I$(top_srcdir)

lib_LIBRARIES = libblitz.a
libblitz_a_SOURCES = $(top_srcdir)/src/globals.cpp
libblitz_a_AR = $(AR) $(AR_FLAGS)

#lib_LTLIBRARIES = libblitz.la
#libblitz_la_SOURCES = $(top_srcdir)/src/globals.cpp


clean-local:
	-rm -f libblitz.a cxx_repository ti_files

