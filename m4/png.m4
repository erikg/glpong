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
# $Id: png.m4,v 1.5 2010/01/06 01:05:59 erik Exp $

#
# AM_PATH_PNG([ACTION-IF-FOUND [,ACTION-IF-NOT-FOUND]])
#

AC_DEFUN([AM_PATH_PNG],
[
  AC_REQUIRE([AC_PROG_CC])

  PNG_CFLAGS=""
  PNG_LIBS=""

  AC_LANG_SAVE
  AC_LANG_C

  AC_ARG_WITH(png-prefix,
    [  --with-png-prefix=PFX     Prefix where PNG is installed],
    [
      PNG_CFLAGS="-I$withval/include"
      PNG_LIBS="-L$withval/lib"
    ])

  AC_ARG_WITH(png-includes,
    [  --with-png-includes=DIR   where the PNG includes are installed],
    [
      PNG_CFLAGS="-I$withval"
    ])

  AC_ARG_WITH(png-libraries,
    [  --with-png-libraries=DIR  where the PNG libraries are installed],
    [
      PNG_LIBS="-L$withval"
    ])

  saved_CFLAGS="$CFLAGS"
  saved_LIBS="$LIBS"
  AC_LANG_SAVE
  AC_LANG_C
  have_PNG=no

  exec 8>&AC_FD_MSG
dnl  exec AC_FD_MSG>/dev/null


  AC_CHECK_LIB(z, uncompress, AC_CHECK_LIB(png, png_create_info_struct, [
	PNG_LIBS="$PNG_LIBS -lpng -lz"
	have_PNG=yes
    ],,$PNG_LIBS))

  LIBS="$saved_LIBS"
  CFLAGS="$saved_CFLAGS"

  exec AC_FD_MSG>&8
  AC_LANG_RESTORE

  if test "$have_PNG" = "yes"; then
     ifelse([$1], , :, [$1])
  else
     PNG_CFLAGS=""
     PNG_LIBS=""
     ifelse([$2], , :, [$2])
  fi
  AC_SUBST(PNG_CFLAGS)
  AC_SUBST(PNG_LIBS)
])

