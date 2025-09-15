# glpong - opengl/sdl game of the original video game; pong.
# Copyright (C) 2001-2025 Erik Greenwald <erik@elfga.com>
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

AC_INIT([glpong], [1.4], [erik@elfga.com], [glpong], [https://github.com/erikg/glpong])
AC_CONFIG_SRCDIR([src/main.c])
AC_CANONICAL_TARGET
AM_INIT_AUTOMAKE([1.11 foreign subdir-objects])

AC_CONFIG_HEADERS([config.h])

# Check for programs
AC_PROG_CC
AC_PROG_INSTALL
PKG_PROG_PKG_CONFIG

# Enable modern C standards
AC_PROG_CC_C99
if test "x$ac_cv_prog_cc_c99" = "xno"; then
    AC_MSG_ERROR([C99 compiler required])
fi

# Check for math library
AC_SEARCH_LIBS([cos], [m], [], [AC_MSG_ERROR([Math library not found])])

# Check for required headers
AC_CHECK_HEADERS([stdlib.h string.h unistd.h])

# Check for required functions
AC_CHECK_FUNCS([memset])

# Add common library paths for different platforms
for search_path in /usr/X11R6 /usr/local /opt/local /sw; do
    AC_MSG_CHECKING([for $search_path])
    if test -d "$search_path/include"; then
        AC_MSG_RESULT([found, adding $search_path to search paths])
        CPPFLAGS="$CPPFLAGS -I$search_path/include"
        if test -d "$search_path/lib"; then
            LDFLAGS="$LDFLAGS -L$search_path/lib"
        fi
    else
        AC_MSG_RESULT([not found])
    fi
done

PKG_CHECK_MODULES([SDL2], [sdl2 >= 2.0.0], , AC_MSG_ERROR([Cannot find SDL2.]))
AC_SUBST(SDL2_CFLAGS)
AC_SUBST(SDL2_LIBS)

PKG_CHECK_MODULES([GL], [opengl], , [PKG_CHECK_MODULES([GL], [gl], , AC_MSG_ERROR([Cannot find OpenGL.]))])
AC_SUBST(GL_CFLAGS)
AC_SUBST(GL_LIBS)

PKG_CHECK_MODULES([PNG], [libpng], , AC_MSG_ERROR([Cannot find libpng.]))
AC_SUBST(PNG_CFLAGS)
AC_SUBST(PNG_LIBS)

PKG_CHECK_MODULES([AL], [openal], [AC_DEFINE(HAVE_SOUND,,OpenAL exists)], AC_MSG_WARN([Cannot find OpenAL. Get it from http://www.openal.org]))
AC_SUBST(AL_CFLAGS)
AC_SUBST(AL_LIBS)

case $target in
	*-apple-darwin*)
		MYDATADIR="$PACKAGE_NAME.app/Contents/Resources"
		;;
	*)
		MYDATADIR="$pkgdatadir"
		;;
esac

AC_SUBST(MYDATADIR)

AC_CONFIG_FILES([Makefile data/Makefile src/Makefile debian/Makefile glpong.spec Info.plist version.plist])
AC_OUTPUT

