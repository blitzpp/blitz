#
# Written by Patrick Guio <patrick.guio@fys.uio.no>
#

SUBDIRS = examples stencils doxygen

# install these files
docdir = $(prefix)/doc

HERE=$(CURDIR)
DVIPS=export TEXPICTS=$(srcdir); dvips
AM_MAKEINFOFLAGS = --no-split -I$(HERE)
TEXI2HTML = texi2html
TEXI2HTML_FLAGS = -split_chapter

STENCILS = stencils/backward11.texi stencils/backward12.texi \
stencils/backward21.texi stencils/backward22.texi stencils/backward31.texi \
stencils/backward32.texi stencils/backward41.texi stencils/backward42.texi \
stencils/central12.texi stencils/central14.texi stencils/central22.texi \
stencils/central24.texi stencils/central32.texi stencils/central34.texi \
stencils/central42.texi stencils/central44.texi stencils/forward11.texi \
stencils/forward12.texi stencils/forward21.texi stencils/forward22.texi \
stencils/forward31.texi stencils/forward32.texi stencils/forward41.texi \
stencils/forward42.texi stencils/Laplacian2D4.texi stencils/Laplacian2D.texi

EXAMPLES = examples/cast.texi examples/debug.texi examples/dump.texi \
examples/fixed-point.texi examples/fixed.texi examples/io.texi \
examples/outer.texi examples/output.texi examples/range.texi \
examples/simple.texi examples/slicing.texi examples/storage.texi \
examples/strideslice.texi examples/xor.texi

OUTPUT = examples/cast.out examples/debug.out examples/dump.out \
examples/fixed.out examples/io.out examples/outer.out examples/output.out \
examples/range.out examples/simple.out examples/slicing.out \
examples/storage.out examples/strideslice.out examples/xor.out

info_TEXINFOS = blitz.texi
blitz_TEXINFOS = about.texi arrays-ctors.texi arrays-debug.texi \
arrays-expr.texi arrays-globals.texi arrays-indirect.texi arrays-intro.texi \
arrays-io.texi arrays-members.texi arrays-multi.texi arrays-slicing.texi \
arrays-stencils.texi arrays-storage.texi arrays-types.texi \
arrays-usertype.texi compiling.texi constants.texi download.texi \
faq.texi help.texi install.texi legal.texi numinquire.texi parallel.texi \
platforms.texi random.texi tau.texi tinymatrix.texi tinyvector.texi \
tuning.texi copyright.texi $(STENCILS) $(EXAMPLES) $(OUTPUT)

EXTRA_DIST = blitz.ps blitz.gif blitztiny.jpg \
	indirect.eps indirect.fig indirect.pdf indirect.gif indirect.txt \
	sinsoid.eps sinsoid.pdf sinsoid.gif sinsoid.txt \
	slice.eps slice.fig slice.pdf slice.gif slice.txt \
	strideslice.eps strideslice.fig strideslice.pdf strideslice.gif strideslice.txt \
	tensor1.eps tensor1.fig tensor1.pdf tensor1.gif tensor1.txt

# Files from texi2dvi that should be removed, but which Automake does
# not know.
CLEANFILES = blitz.tmp

## ----------------------------- ##
## Other documentation formats.  ##
## ----------------------------- ##

html: blitz_1.html

blitz_1.html: $(info_TEXINFOS) $(blitz_TEXINFOS)
	$(TEXI2HTML) $(TEXI2HTML_FLAGS) $(srcdir)/blitz.texi

stencils/%.texi:
	(cd stencils; $(MAKE) $(AM_MAKEFLAGS) stencils)

examples/%.texi:
	(cd examples; $(MAKE) $(AM_MAKEFLAGS) -i texi)

examples/%.out:
	(cd examples; $(MAKE) $(AM_MAKEFLAGS) -i out)


.PHONY: html

clean-local:
	-rm -rf blitz*.html 

