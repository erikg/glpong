EXTRA_DIST = lose.wav boink.wav refl.png texture.png

install:
	mkdir -p $(DESTDIR)${datadir}/glpong/
	install -c -m 644 lose.wav $(DESTDIR)${datadir}/glpong/lose.wav
	install -c -m 644 boink.wav $(DESTDIR)${datadir}/glpong/boink.wav
	install -c -m 644 refl.png $(DESTDIR)${datadir}/glpong/refl.png
	install -c -m 644 texture.png $(DESTDIR)${datadir}/glpong/texture.png

uninstall:
	rm -rf $(DESTDIR)${datadir}/glpong

