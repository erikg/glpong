# glpong - opengl/sdl game of the original video game; pong.
# Copyright (C) 2001-2008 Erik Greenwald <erik@smluc.org>
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

# $Id: Makefile.am,v 1.9 2008/02/01 00:03:54 erik Exp $

SOUNDS=lose.wav boink.wav 
IMAGES=refl.png font.png

dist_pkgdata_DATA = $(SOUNDS) $(IMAGES)

EXTRA_DIST = glpong.icns
bundle:
	for file in $(SOUNDS) $(IMAGES) glpong.icns ; do ${INSTALL} $(top_srcdir)/data/$$file $(top_builddir)/@PACKAGE@.app/Contents/Resources/ ; done

