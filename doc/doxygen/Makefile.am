

# Support doxygen documentation ?

if DOC

html/index.html: Doxyfile
	@DOXYGEN@

# Document Targets
html: html/index.html
ps: $(PACKAGE)-$(VERSION).ps
pdf: $(PACKAGE)-$(VERSION).pdf

$(PACKAGE)-$(VERSION).ps: html/index.html
	@if test -d latex; then \
	@echo "Making postscript manual"; \
		$(MAKE) -C latex refman.ps; \
	mv ./latex/refman.ps $(PACKAGE)-$(VERSION).ps; \
	fi

$(PACKAGE)-$(VERSION).pdf: html/index.html
	@if test -d latex; then \
	@echo "Making PDF manual"; \
		$(MAKE) -C latex refman.pdf; \
		mv ./latex/refman.pdf $(PACKAGE)-$(VERSION).pdf; \
	fi

doc: html/index.html
	@if test ! -f html/search.idx; then \
		(cd html; doxytag -s search.idx); \
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
		tar cf - -C html . | bzip2 --best -c > $(PACKAGE)-docs-$(VERSION).tar.bz2; \
	fi
	@if test -f $(PACKAGE)-$(VERSION).ps; then \
		bzip2 --force --best $(PACKAGE)-$(VERSION).ps; \
	fi
	@if test -f $(PACKAGE)-$(VERSION).pdf; then \
		bzip2 --force --best $(PACKAGE)-$(VERSION).pdf; \
	fi

# Clean hooks
clean-local:
	@if test -f $(PACKAGE)-$(VERSION).pdf; then \
		$(RM) -f $(PACKAGE)-$(VERSION).pdf; \
	fi
	@if test -f $(PACKAGE)-$(VERSION).pdf.bz2; then \
		$(RM) -f $(PACKAGE)-$(VERSION).pdf.bz2; \
	fi
	@if test -d html; then \
		$(RM) -rf html; \
	fi
	@if test -d latex; then \
		$(RM) -rf latex; \
	fi

# Install hooks
make-install-dirs:
	@if test '!' -d $(datadir)/doc/$(PACKAGE)-$(VERSION); \
		then mkdir -p $(datadir)/doc/$(PACKAGE)-$(VERSION); \
	fi

install-data-hook: make-install-dirs
	@if test -d html; then \
		echo Installing documentations into $(datadir)/doc/$(PACKAGE)-$(VERSION) ; \
		$(INSTALL_DATA) html/* $(datadir)/doc/$(PACKAGE)-$(VERSION) ; \
	fi

