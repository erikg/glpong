# $Id: Makefile.am,v 1.7 2004/01/01 20:20:25 erik Exp $

bin_PROGRAMS = glpong

glpong_SOURCES = ai.c game.c image.c input.c main.c map.c physics.c sound.c text.c timer.c video.c
noinst_HEADERS = ai.h game.h image.h input.h map.h physics.h sound.h text.h timer.h video.h
glpong_CFLAGS = @SDL_CFLAGS@ @PNG_CFLAGS@ @GL_CFLAGS@ @AL_CFLAGS@ -DDATADIR=\"${pkgdatadir}\"
glpong_LDADD = @SDL_LIBS@ @PNG_LIBS@ @GL_LIBS@ @AL_LIBS@

indent:
	for a in *.[ch]; do indent $$a ; done

gindent:
	for a in *.[ch]; do gindent $$a ; done
