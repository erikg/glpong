SOUNDS=lose.wav boink.wav 
IMAGES=refl.@IMGEXT@ texture.@IMGEXT@
SIMAGES=refl texture

dist_pkgdata_DATA = $(SOUNDS) $(IMAGES)

bundle:
	for file in $(SOUNDS) $(IMAGES) glpong.icns ; do ${INSTALL} $(top_srcdir)/data/$$file $(top_builddir)/@PACKAGE@.app/Contents/Resources/ ; done

