

# Support doxygen documentation ?

docdir = $(datadir)/doc/$(PACKAGE)-doc-$(VERSION)

if DOC

html/index.html: Doxyfile
	@DOXYGEN@

# Document Targets
html: html/index.html
ps: $(PACKAGE).ps
pdf: $(PACKAGE).pdf

$(PACKAGE).ps: html/index.html
	@if test -d latex; then \
	echo "Making PostScript manual"; \
		$(MAKE) -C latex refman.ps; \
	mv ./latex/refman.ps $(PACKAGE).ps; \
	fi

$(PACKAGE).pdf: html/index.html
	@if test -d latex; then \
	echo "Making PDF manual"; \
		$(MAKE) -C latex refman.pdf; \
		mv ./latex/refman.pdf $(PACKAGE).pdf; \
	fi

doc: html/index.html
	@if test ! -f html/blitz.tag; then \
		(cd html; doxytag -t blitz.tag); \
	fi
	@if test -d latex; then \
		make pdf; \
	fi

else
doc:
endif


all-local: doc


# documentation distribution
doc-dist: doc
	@if test -d html; then \
		echo "please wait while archiving the docs."; \
		tar cf - -C html . | bzip2 --best -c > $(PACKAGE)-docs.tar.bz2; \
	fi
	@if test -f $(PACKAGE).ps; then \
		bzip2 --force --best $(PACKAGE).ps; \
	fi
	@if test -f $(PACKAGE).pdf; then \
		bzip2 --force --best $(PACKAGE).pdf; \
	fi

# Clean hooks
clean-local:
	@if test -f $(PACKAGE).pdf; then \
		$(RM) -f $(PACKAGE).pdf; \
	fi
	@if test -f $(PACKAGE).pdf.bz2; then \
		$(RM) -f $(PACKAGE).pdf.bz2; \
	fi
	@if test -d html; then \
		$(RM) -rf html; \
	fi
	@if test -d latex; then \
		$(RM) -rf latex; \
	fi

# Install hooks
make-install-dirs:
	@if test '!' -d $(docdir) ; \
		then mkdir -p $(docdir) ; \
	fi

install-data-hook: make-install-dirs
	@if test -d html; then \
		echo Installing documentations into $(docdir) ; \
		$(INSTALL_DATA) html/* $(docdir) ; \
	fi
	@if test -f $(PACKAGE).ps; then \
		echo Installing PostScript manual into $(docdir) ; \
		$(INSTALL_DATA) $(PACKAGE).ps $(docdir) ; \
	fi
	@if test -f $(PACKAGE).pdf; then \
		echo Installing PDF manual into $(docdir) ; \
		$(INSTALL_DATA) $(PACKAGE).pdf $(docdir) ; \
	fi

