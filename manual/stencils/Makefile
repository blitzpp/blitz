# Generated automatically from Makefile.in by configure.
# Blitz++ test suite makefile

srcdir = .
BZDIR = ../..

CXX = g++
CXXFLAGS  = -g -I$(srcdir)/$(BZDIR) -ftemplate-depth-30 -DBZ_DEBUG -Dstenciltodump=Laplacian2D4

DEFS = 

LIBS = -L$(BZDIR)/lib -lblitz -lm

SINGLE_TESTS = dump-stencil

MULTIPLE_TESTS = modules

TESTS = $(SINGLE_TESTS) $(MULTIPLE_TESTS)

.SUFFIXES: .o .cpp 

.cpp.o:
	$(CXX) $(CXXFLAGS) $(DEFS) -c $(srcdir)/$*.cpp

###########################################################################

all:	$(TESTS)
	echo Running test suite...
	@for prog in $(TESTS) ; do \
	  echo $$prog && (./$$prog) || exit 1; \
	done

$(SINGLE_TESTS): 
	$(CXX) $(LDFLAGS) $@.o -o $@ $(LIBS)

dump-stencil:	dump-stencil.o

##########################################################################

check:	all

clean:
	rm -f *.o *.ii *.int.c *.s $(TESTS)
