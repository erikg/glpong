# $Id: Makefile.am,v 1.7 2004/01/01 20:20:24 erik Exp $

SOUNDS=lose.wav boink.wav 
IMAGES=refl.png texture.png

dist_pkgdata_DATA = $(SOUNDS) $(IMAGES)

EXTRA_DIST = glpong.icns
bundle:
	for file in $(SOUNDS) $(IMAGES) glpong.icns ; do ${INSTALL} $(top_srcdir)/data/$$file $(top_builddir)/@PACKAGE@.app/Contents/Resources/ ; done

