#
# Written by Patrick Guio <patrick.guio@fys.uio.no>
#

# install these files
#docdir = $(prefix)/doc/blitz/stencils
#doc_DATA = backward11.texi backward12.texi backward21.texi backward22.texi \
#backward31.texi backward32.texi backward41.texi backward42.texi \
#central12.texi central14.texi central22.texi central24.texi central32.texi \
#central34.texi central42.texi central44.texi forward11.texi forward12.texi \
#forward21.texi forward22.texi forward31.texi forward32.texi forward41.texi \
#forward42.texi Laplacian2D.texi Laplacian2D4.texi \
#dump-stencil.cpp

EXTRA_DIST = dump-stencil.cpp

INCLUDES = -I$(top_srcdir) -I$(top_builddir)
LDADD = -L$(top_builddir)/lib -lblitz -lm
COMPILE = $(CXX) $(CXXFLAGS) $(INCLUDES) 

LTCXXCOMPILE = $(LIBTOOL) --mode=link $(CXX) $(DEFS) \
	$(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) \
	$(AM_CXXFLAGS) $(CXXFLAGS)

%2D.texi :
	$(LTCXXCOMPILE) "-Dstenciltoapply=$(patsubst %.texi,%,$@)(A)" \
		-o $(patsubst %.cpp,%,$<) $< $(LDADD)
	./$(patsubst %.cpp,%,$<) > $@  2>&1
	-rm -f $(patsubst %.cpp,%,$<)

%2D4.texi :
	$(LTCXXCOMPILE) "-Dstenciltoapply=$(patsubst %.texi,%,$@)(A)" \
		-o $(patsubst %.cpp,%,$<) $< $(LDADD)
	./$(patsubst %.cpp,%,$<) > $@  2>&1
	-rm -f $(patsubst %.cpp,%,$<)

%.texi :
	$(LTCXXCOMPILE) "-Dstenciltoapply=$(patsubst %.texi,%,$@)(A,1)" \
		-o $(patsubst %.cpp,%,$<) $< $(LDADD)
	./$(patsubst %.cpp,%,$<) > $@  2>&1
	-rm -f $(patsubst %.cpp,%,$<)

central12.texi: dump-stencil.cpp
central22.texi: dump-stencil.cpp
central32.texi: dump-stencil.cpp
central42.texi: dump-stencil.cpp
central14.texi: dump-stencil.cpp
central24.texi: dump-stencil.cpp
central34.texi: dump-stencil.cpp
central44.texi: dump-stencil.cpp

forward11.texi: dump-stencil.cpp
forward21.texi: dump-stencil.cpp
forward31.texi: dump-stencil.cpp
forward41.texi: dump-stencil.cpp
forward12.texi: dump-stencil.cpp
forward22.texi: dump-stencil.cpp
forward32.texi: dump-stencil.cpp
forward42.texi: dump-stencil.cpp

backward11.texi: dump-stencil.cpp
backward21.texi: dump-stencil.cpp
backward31.texi: dump-stencil.cpp
backward41.texi: dump-stencil.cpp
backward12.texi: dump-stencil.cpp
backward22.texi: dump-stencil.cpp
backward32.texi: dump-stencil.cpp
backward42.texi: dump-stencil.cpp

Laplacian2D.texi: dump-stencil.cpp
Laplacian2D4.texi: dump-stencil.cpp

stencils: central12.texi central22.texi central32.texi central42.texi \
central14.texi central24.texi central34.texi central44.texi forward11.texi \
forward21.texi forward31.texi forward41.texi forward12.texi forward22.texi \
forward32.texi forward42.texi backward11.texi backward21.texi \
backward31.texi backward41.texi backward12.texi backward22.texi \
backward32.texi backward42.texi Laplacian2D.texi Laplacian2D4.texi

all-am:
	$(MAKE) $(AM_MAKEFLAGS) stencils

clean-local:
	-rm -rf cxx_repository dump-stencil *.texi

