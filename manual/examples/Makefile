# Blitz++ examples makefile

# Home directory for Blitz++ library
BZDIR   = ../..

# Uncomment for debug version
DFLAGS  = -DBZ_DEBUG -g +K0 
# DFLAGS  = -DBZ_DEBUG -DBZ_DEBUG_LOG_ALLOCATIONS -DBZ_DEBUG_LOG_REFERENCES -g +K0

# Uncomment for optimized version
# DFLAGS  = +K3 -O

# Uncomment to look at optimized assembly
# DFLAGS = -O2 +K3 -S

# Uncomment for profiling version
# DFLAGS = -pg -O3 +K3

# KAI C++ 3.0
CFLAGS = -I ${BZDIR} ${DFLAGS} -DTV_KCC --restrict \
         --no_implicit_include --abstract_pointer --keep_gen_c \
         --abstract_float --no_implicit_typename --no_old_specializations \
         --strict_warnings --diag_suppress 113 -tused -D_XOPEN_SOURCE

CC     = KCC
LFLAGS =
LIBS   = -lm


############################################################################

EXAMPLES =  simple
TMPDIR   = .
.SUFFIXES: .o .cpp 

.cpp.o:
	${CC} ${CFLAGS} ${DEFS} -c $*.cpp

.c.o:
	${CC} ${CFLAGS} ${DEFS} -c $*.c

###########################################################################

all:	${EXAMPLES}

simple:	simple.o
	${CC} ${CFLAGS} -o simple simple.o ${LIBS}

slicing:	slicing.o
	${CC} ${CFLAGS} -o slicing slicing.o ${LIBS}

debug:	debug.o
	${CC} ${CFLAGS} -o debug debug.o ${LIBS}

xor:	xor.o
	${CC} ${CFLAGS} -o xor xor.o ${LIBS}

cast:	cast.o
	${CC} ${CFLAGS} -o cast cast.o ${LIBS}

dump:	dump.o
	${CC} ${CFLAGS} -o dump dump.o ${LIBS}

output:	output.o
	${CC} ${CFLAGS} -o output output.o ${LIBS}

outer:	outer.o
	${CC} ${CFLAGS} -o outer outer.o ${LIBS}

strideslice:	strideslice.o
	${CC} ${CFLAGS} -o strideslice strideslice.o ${LIBS}

range:	range.o
	${CC} ${CFLAGS} -o range range.o ${LIBS}

###########################################################################

clean:
	rm -f *.o *.ii *.int.c *.s ${EXAMPLES}
