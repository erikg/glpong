AC_INIT
AC_CONFIG_SRCDIR([src/main.c])
AC_CANONICAL_TARGET
AM_INIT_AUTOMAKE(glpong, 1.2)

AM_CONFIG_HEADER(config.h)

AC_PROG_CC
AC_PROG_INSTALL

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

AC_CONFIG_FILES([Makefile data/Makefile src/Makefile glpong.spec Info.plist version.plist])
AC_OUTPUT
