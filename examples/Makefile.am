#
# Written by Patrick Guio <patrick.guio@fys.uio.no>
#

EXTRA_DIST = stencil4.f profile.cpp tiny2.cpp tiny3.cpp

AM_CPPFLAGS = -I$(srcdir) -I$(top_srcdir)
LDADD = -L$(top_builddir)/lib -lblitz

EXTRA_PROGRAMS = array cartesian cast cfd complex-test convolve curldiv \
deriv diff erf fixed indirect io iter matmult nested numinquire outer pauli \
pick polymorph prettyprint qcd rand2 random rangexpr reduce simple \
slicing stencil2 stencil3 stencil stencilet storage tiny \
transform useret where whitt 

array_SOURCES = array.cpp
cartesian_SOURCES = cartesian.cpp
cast_SOURCES = cast.cpp
cfd_SOURCES = cfd.cpp
complex_test_SOURCES = complex-test.cpp
convolve_SOURCES = convolve.cpp
curldiv_SOURCES = curldiv.cpp
deriv_SOURCES = deriv.cpp
diff_SOURCES = diff.cpp
erf_SOURCES = erf.cpp
fixed_SOURCES = fixed.cpp
indirect_SOURCES = indirect.cpp
io_SOURCES = io.cpp
iter_SOURCES = iter.cpp
matmult_SOURCES = matmult.cpp
nested_SOURCES = nested.cpp
numinquire_SOURCES = numinquire.cpp
outer_SOURCES = outer.cpp
pauli_SOURCES = pauli.cpp
pick_SOURCES = pick.cpp
polymorph_SOURCES = polymorph.cpp
prettyprint_SOURCES = prettyprint.cpp
#profile_SOURCES = profile.cpp
qcd_SOURCES = qcd.cpp
rand2_SOURCES = rand2.cpp
random_SOURCES = random.cpp
rangexpr_SOURCES = rangexpr.cpp
reduce_SOURCES = reduce.cpp
simple_SOURCES = simple.cpp
slicing_SOURCES = slicing.cpp
stencil2_SOURCES = stencil2.cpp
stencil3_SOURCES = stencil3.cpp
stencil_SOURCES = stencil.cpp
stencilet_SOURCES = stencilet.cpp
storage_SOURCES = storage.cpp
#tiny2_SOURCES = tiny2.cpp
#tiny3_SOURCES = tiny3.cpp
tiny_SOURCES = tiny.cpp
transform_SOURCES = transform.cpp
useret_SOURCES = useret.cpp
where_SOURCES = where.cpp
whitt_SOURCES = whitt.cpp

#compile: $(EXTRA_PROGRAMS)

check-examples: $(EXTRA_PROGRAMS)
	@echo Running examples...
	@for prog in $(EXTRA_PROGRAMS) ; do \
		echo $$prog && (./$$prog > /dev/null 2>&1) || exit 1; \
	done
	@echo All tests passed.

#all:

clean-local:
	-rm -rf cxx_repository $(EXTRA_PROGRAMS)


