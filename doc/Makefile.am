#
# Written by Patrick Guio <patrick.guio@fys.uio.no>
#

SUBDIRS = examples stencils

# install these files
docdir = $(prefix)/doc
doc_DATA = blitz.ps 

AM_MAKEINFOFLAGS = --no-split
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

CODES = examples/cast.texi examples/debug.texi examples/dump.texi \
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
arrays-usertype.texi blitz.texi compiling.texi constants.texi download.texi \
faq.texi help.texi install.texi legal.texi numinquire.texi parallel.texi \
platforms.texi random.texi tau.texi tinymatrix.texi tinyvector.texi \
tuning.texi copyright.texi $(STENCILS) $(CODES) $(OUTPUT)

# Files from texi2dvi that should be removed, but which Automake does
# not know.
CLEANFILES = blitz.tmp

## ----------------------------- ##
## Other documentation formats.  ##
## ----------------------------- ##

html: blitz_1.html

blitz_1.html: blitz.texi $(blitz_TEXINFOS)
	$(TEXI2HTML) $(TEXI2HTML_FLAGS) $(srcdir)/blitz.texi


.PHONY: html

clean-local:
	-rm -rf blitz*.html 

