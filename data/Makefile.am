SOUNDS=lose.wav boink.wav 
IMAGES=refl.png texture.png
SIMAGES=refl texture

MACOS_RES=../$(PACKAGE).app/Contents/Resources

EXTRA_DIST = $(SOUNDS) $(IMAGES) 

install:
	mkdir -p $(DESTDIR)${datadir}/glpong/
	install -c -m 644 lose.wav $(DESTDIR)${datadir}/glpong/lose.wav
	install -c -m 644 boink.wav $(DESTDIR)${datadir}/glpong/boink.wav
	install -c -m 644 refl.png $(DESTDIR)${datadir}/glpong/refl.png
	install -c -m 644 texture.png $(DESTDIR)${datadir}/glpong/texture.png

uninstall:
	rm -rf $(DESTDIR)${datadir}/glpong

bundle:
	cp $(SOUNDS) $(MACOS_RES)/
	cp macos.icns $(MACOS_RES)/$(PACKAGE).icns
	for a in $(SIMAGES); do convert $$a.png TGA:$(MACOS_RES)/$$a.tga ; done
