#
# $Id$
#
# Patrick Guio <patrick.guio@fys.uio.no>
#

# Blitz++ test suite makefile

SUBDIRS =

EXTRA_DIST = testsuite.h

INCLUDES = -I$(top_srcdir)
CXXFLAGS = @CXXFLAGS@ @CXX_DEBUG_FLAGS@
LDADD = -L$(top_srcdir)/lib -lblitz

# install this file
testsuitedir = $(prefix)/testsuite
testsuite_DATA = Adnene-Ben-Abdallah-1.cpp Adnene-Ben-Abdallah-2.cpp \
Josef-Wagenhuber.cpp Olaf-Ronneberger-1.cpp Ulisses-Mello-1.cpp \
arrayresize.cpp chris-jeffery-1.cpp chris-jeffery-2.cpp chris-jeffery-3.cpp \
complex_test.cpp constarray.cpp contiguous.cpp copy.cpp ctors.cpp \
derrick-bass-1.cpp derrick-bass-3.cpp exprctor.cpp extract.cpp free.cpp \
gary-huber-1.cpp initialize.cpp interlace.cpp iter.cpp loop1.cpp \
matthias-troyer-1.cpp matthias-troyer-2.cpp mattias-lindstroem-1.cpp \
minmax.cpp minsumpow.cpp module1.cpp module2.cpp newet.cpp \
peter-bienstman-1.cpp peter-bienstman-2.cpp peter-bienstman-3.cpp \
peter-bienstman-4.cpp peter-bienstman-5.cpp peter-nordlund-1.cpp \
peter-nordlund-2.cpp peter-nordlund-3.cpp promote.cpp qcd.cpp reduce.cpp \
reindex.cpp reverse.cpp shape.cpp shapecheck.cpp storage.cpp stub.cpp \
theodore-papadopoulo-1.cpp tinymat.cpp tinyvec.cpp transpose.cpp \
troyer-genilloud.cpp wei-ku-1.cpp where.cpp Makefile

EXTRA_PROGRAMS = Adnene-Ben-Abdallah-1 Adnene-Ben-Abdallah-2 arrayresize \
chris-jeffery-1 chris-jeffery-2 chris-jeffery-3 complex_test constarray \
contiguous copy ctors derrick-bass-1 derrick-bass-3 exprctor extract free \
gary-huber-1 initialize interlace iter Josef-Wagenhuber loop1 \
matthias-troyer-1 matthias-troyer-2 mattias-lindstroem-1 minmax minsumpow \
module newet Olaf-Ronneberger-1 peter-bienstman-1 peter-bienstman-2 \
peter-bienstman-3 peter-bienstman-4 peter-bienstman-5 peter-nordlund-1 \
peter-nordlund-2 peter-nordlund-3 promote qcd reduce reindex reverse \
shapecheck shape storage stub theodore-papadopoulo-1 tinymat tinyvec \
transpose troyer-genilloud Ulisses-Mello-1 wei-ku-1 where

Adnene_Ben_Abdallah_1_SOURCES = Adnene-Ben-Abdallah-1.cpp
Adnene_Ben_Abdallah_2_SOURCES = Adnene-Ben-Abdallah-2.cpp
arrayresize_SOURCES = arrayresize.cpp
chris_jeffery_1_SOURCES = chris-jeffery-1.cpp
chris_jeffery_2_SOURCES = chris-jeffery-2.cpp
chris_jeffery_3_SOURCES = chris-jeffery-3.cpp
complex_test_SOURCES = complex_test.cpp
constarray_SOURCES = constarray.cpp
contiguous_SOURCES = contiguous.cpp
copy_SOURCES = copy.cpp
ctors_SOURCES = ctors.cpp
derrick_bass_1_SOURCES = derrick-bass-1.cpp
derrick_bass_3_SOURCES = derrick-bass-3.cpp
exprctor_SOURCES = exprctor.cpp
extract_SOURCES = extract.cpp
free_SOURCES = free.cpp
gary_huber_1_SOURCES = gary-huber-1.cpp
initialize_SOURCES = initialize.cpp
interlace_SOURCES = interlace.cpp
iter_SOURCES = iter.cpp
Josef_Wagenhuber_SOURCES = Josef-Wagenhuber.cpp
loop1_SOURCES = loop1.cpp
matthias_troyer_1_SOURCES = matthias-troyer-1.cpp
matthias_troyer_2_SOURCES = matthias-troyer-2.cpp
mattias_lindstroem_1_SOURCES = mattias-lindstroem-1.cpp
minmax_SOURCES = minmax.cpp
minsumpow_SOURCES = minsumpow.cpp
module_SOURCES = module1.cpp module2.cpp
newet_SOURCES = newet.cpp
Olaf_Ronneberger_1_SOURCES = Olaf-Ronneberger-1.cpp
peter_bienstman_1_SOURCES = peter-bienstman-1.cpp
peter_bienstman_2_SOURCES = peter-bienstman-2.cpp
peter_bienstman_3_SOURCES = peter-bienstman-3.cpp
peter_bienstman_4_SOURCES = peter-bienstman-4.cpp
peter_bienstman_5_SOURCES = peter-bienstman-5.cpp
peter_nordlund_1_SOURCES = peter-nordlund-1.cpp
peter_nordlund_2_SOURCES = peter-nordlund-2.cpp
peter_nordlund_3_SOURCES = peter-nordlund-3.cpp
promote_SOURCES = promote.cpp
qcd_SOURCES = qcd.cpp
reduce_SOURCES = reduce.cpp
reindex_SOURCES = reindex.cpp
reverse_SOURCES = reverse.cpp
shapecheck_SOURCES = shapecheck.cpp
shape_SOURCES = shape.cpp
storage_SOURCES = storage.cpp
stub_SOURCES = stub.cpp
theodore_papadopoulo_1_SOURCES = theodore-papadopoulo-1.cpp
tinymat_SOURCES = tinymat.cpp
tinyvec_SOURCES = tinyvec.cpp
transpose_SOURCES = transpose.cpp
troyer_genilloud_SOURCES = troyer-genilloud.cpp
Ulisses_Mello_1_SOURCES = Ulisses-Mello-1.cpp
wei_ku_1_SOURCES = wei-ku-1.cpp
where_SOURCES = where.cpp

check-testsuite:  $(EXTRA_PROGRAMS)
	@echo Running test suite...
	@for prog in $(EXTRA_PROGRAMS) ; do \
		echo $$prog && (./$$prog > /dev/null 2>&1) || exit 1; \
		done
	@echo All tests passed.

clean-local:
	-rm -rf cxx_repository $(EXTRA_PROGRAMS)

