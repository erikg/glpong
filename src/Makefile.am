# glpong - opengl/sdl game of the original video game; pong.
# Copyright (C) 2001-2010 Erik Greenwald <erik@brlcad.org>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

# $Id: Makefile.am,v 1.13 2010/01/06 01:06:00 erik Exp $

bin_PROGRAMS = glpong

glpong_SOURCES = ai.c game.c image.c input.c main.c map.c physics.c sound.c text.c timer.c video.c
noinst_HEADERS = ai.h game.h image.h input.h map.h physics.h sound.h text.h timer.h video.h
AM_CFLAGS = @SDL_CFLAGS@ @PNG_CFLAGS@ @GL_CFLAGS@ @AL_CFLAGS@ -DDATADIR=\"${pkgdatadir}\"
LDADD = @SDL_LIBS@ @PNG_LIBS@ @GL_LIBS@ @AL_LIBS@

indent:
	for a in ${glpong_SOURCES} ${noinst_HEADERS}; do [ x`which gindent` = x ] && indent $$a || gindent $$a ; done

ctags: $(glpong_SOURCES) $(noinst_HEADERS)
	ctags $(glpong_SOURCES) $(noinst_HEADERS)
