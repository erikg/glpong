# $Id: Makefile.am,v 1.8 2004/04/25 21:12:52 erik Exp $

SOUNDS=lose.wav boink.wav 
IMAGES=refl.png font.png

dist_pkgdata_DATA = $(SOUNDS) $(IMAGES)

EXTRA_DIST = glpong.icns
bundle:
	for file in $(SOUNDS) $(IMAGES) glpong.icns ; do ${INSTALL} $(top_srcdir)/data/$$file $(top_builddir)/@PACKAGE@.app/Contents/Resources/ ; done

