# glpong - opengl/sdl game of the original video game; pong.
# Copyright (C) 2001-2012 Erik Greenwald <erik@elfga.com>
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

AC_INIT
AC_CONFIG_SRCDIR([src/main.c])
AC_CANONICAL_SYSTEM
AM_INIT_AUTOMAKE(glpong, 1.3)

AM_CONFIG_HEADER(config.h)

AC_PROG_CC
AC_PROG_INSTALL

dnl autosearch /usr/X11R6
AC_MSG_CHECKING([for /usr/X11R6])
if test -d /usr/X11R6/include ; then
	AC_MSG_RESULT([found, adding /usr/X11R6 to search paths])
	CPPFLAGS="$CPPFLAGS -I/usr/X11R6/include"
	if test -d /usr/X11R6/lib ; then
		LDFLAGS="$LDFLAGS -L/usr/X11R6/lib"
	fi
else
	AC_MSG_RESULT([not found])
fi

dnl autosearch /usr/local
AC_MSG_CHECKING([for /usr/local])
if test -d /usr/local/include ; then
	AC_MSG_RESULT([found, adding /usr/local to search paths])
	CPPFLAGS="$CPPFLAGS -I/usr/local/include"
	if test -d /usr/local/lib ; then
		LDFLAGS="$LDFLAGS -L/usr/local/lib"
	fi
else
	AC_MSG_RESULT([not found])
fi

dnl autosearch /opt/local
AC_MSG_CHECKING([for /opt/local])
if test -d /opt/local/include ; then
	AC_MSG_RESULT([found, adding /opt/local to search paths])
	CPPFLAGS="$CPPFLAGS -I/opt/local/include"
	if test -d /opt/local/lib ; then
		LDFLAGS="$LDFLAGS -L/opt/local/lib"
	fi
else
	AC_MSG_RESULT([not found])
fi

dnl autosearch fink paths
AC_MSG_CHECKING([for fink in /sw])
if test -d /sw/include ; then
	AC_MSG_RESULT([found, adding /sw to search paths])
	CPPFLAGS="$CPPFLAGS -I/sw/include"
	if test -d /sw/lib ; then
		LDFLAGS="$LDFLAGS -L/sw/lib"
	fi
else
	AC_MSG_RESULT([not found])
fi

AM_PATH_SDL(1.2.0,,AC_MSG_ERROR([Cannot find SDL.]))
AC_SUBST(SDL_CFLAGS)
AC_SUBST(SDL_LIBS)

AM_PATH_OPENGL(,AC_MSG_ERROR([Cannot find OpenGL.]))
AC_SUBST(GL_CFLAGS)
AC_SUBST(GL_LIBS)

AM_PATH_PNG(,AC_MSG_ERROR([Cannot find libpng.]))
AC_SUBST(PNG_CFLAGS)
AC_SUBST(PNG_LIBS)

AM_PATH_OPENAL(AC_DEFINE(HAVE_SOUND,,OpenAL exists),AC_MSG_WARN(Cannot find OpenAL. Get it from http://www.openal.org))
AC_SUBST(AL_CFLAGS)
AC_SUBST(AL_LIBS)

case $target in
	*-apple-darwin*)
		MYDATADIR="$PACKAGE.app/Contents/Resources"
		;;
	*)
		MYDATADIR="$pkgdatadir"
		;;
esac

AC_SUBST(MYDATADIR)

AC_CONFIG_FILES([Makefile data/Makefile src/Makefile debian/Makefile glpong.spec Info.plist version.plist])
AC_OUTPUT

