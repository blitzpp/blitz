#
# Written by Patrick Guio <patrick.guio@fys.uio.no>
#

SUBDIRS = .

INCLUDES = -I$(top_srcdir)
lib_LIBRARIES = libblitz.a
libblitz_a_SOURCES = globals.cpp
libblitz_a_AR = $(AR) $(AR_FLAGS)

all-am: lib

lib: $(top_srcdir)/lib/$(lib_LIBRARIES)

$(top_srcdir)/lib/$(lib_LIBRARIES): $(lib_LIBRARIES)
	cp $< $@

clean-local:
	-rm -rf cxx_repository ti_files
