# $Id: Makefile.am,v 1.6 2003/12/28 17:04:48 erik Exp $

bin_PROGRAMS = glpong

glpong_SOURCES = ai.c game.c input.c main.c map.c physics.c sound.c text.c timer.c video.c
noinst_HEADERS = ai.h game.h input.h map.h physics.h sound.h text.h timer.h video.h

glpong_CFLAGS = -DDATADIR=\"${pkgdatadir}\" -DIMGEXT=\"@IMGEXT@\"

indent:
	for a in *.[ch]; do indent $$a ; done

gindent:
	for a in *.[ch]; do gindent $$a ; done
