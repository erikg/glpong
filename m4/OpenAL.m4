# Game/graphics/multimedia oriented m4 package for autoconf/aclocal.
#
# Copyright 2000-2010 Erik Greenwald <erik@smluc.org>
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
# 3. All advertising materials mentioning features or use of this software
#    must display the following acknowledgement:
# This product includes software developed by Erik Greenwald.
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
# OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
# SUCH DAMAGE.
#
# $Id: OpenAL.m4,v 1.11 2010/01/06 01:05:59 erik Exp $
#

#
# AM_PATH_OPENAL([ACTION-IF-FOUND [,ACTION-IF-NOT-FOUND]])
#

AC_DEFUN([AM_PATH_OPENAL],
[
  AC_REQUIRE([AC_PROG_CC])
  AC_REQUIRE([AC_CANONICAL_TARGET])

  AL_CFLAGS=""
  AL_LIBS=""

  AC_LANG_SAVE
  AC_LANG_C

  AC_ARG_WITH(al-prefix,
    [  --with-al-prefix=PFX     Prefix where OpenAL is installed],
    [
      AL_CFLAGS="-I$withval/include"
      AL_LIBS="-L$withval/lib"
    ])

  AC_ARG_WITH(al-includes,
    [  --with-al-includes=DIR   where the OpenAL includes are installed],
    [
      AL_CFLAGS="-I$withval"
    ])

  AC_ARG_WITH(al-libraries,
    [  --with-al-libraries=DIR  where the OpenAL libraries are installed],
    [
      AL_LIBS="-L$withval"
    ])

case "$target" in
	*-*-freebsd* | *-*-FreeBSD*)
		AL_LIBS="$AL_LIBS -pthread"
		;;
	*)
		AL_LIBS="$AL_LIBS -lpthread"
		;;
esac

  saved_CFLAGS="$CFLAGS"
  saved_LIBS="$LIBS"
  AC_LANG_SAVE
  AC_LANG_C
  have_AL=no

  exec 8>&AC_FD_MSG
dnl  exec AC_FD_MSG>/dev/null

case "$target" in
	*-apple-darwin*)
		AL_LIBS="-framework OpenAL"
		AL_CFLAGS="-framework OpenAL"
		have_AL=yes
		;;
	*)
		AC_SEARCH_LIBS(alGenBuffers,
			[openal OpenAL32],
			[
				AL_LIBS="$LIBS"
				have_AL=yes
			], , $AL_LIBS)
		;;
esac

  LIBS="$saved_LIBS"
  CFLAGS="$saved_CFLAGS"

  exec AC_FD_MSG>&8
  AC_LANG_RESTORE

  if test "$have_AL" = "yes"; then
     ifelse([$1], , :, [$1])
  else
     AL_CFLAGS=""
     AL_LIBS=""
     ifelse([$2], , :, [$2])
  fi
  AC_SUBST(AL_CFLAGS)
  AC_SUBST(AL_LIBS)
])

