# $Id: Makefile.am,v 1.8 2004/04/17 14:43:14 erik Exp $

bin_PROGRAMS = glpong

glpong_SOURCES = ai.c game.c image.c input.c main.c map.c physics.c sound.c text.c timer.c video.c
noinst_HEADERS = ai.h game.h image.h input.h map.h physics.h sound.h text.h timer.h video.h
AM_CFLAGS = @SDL_CFLAGS@ @PNG_CFLAGS@ @GL_CFLAGS@ @AL_CFLAGS@ -DDATADIR=\"${pkgdatadir}\"
LDADD = @SDL_LIBS@ @PNG_LIBS@ @GL_LIBS@ @AL_LIBS@

indent:
	then for a in ${glpong_SOURCES} ${noinst_HEADERS}; do indent $$a ; done

