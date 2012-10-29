
/*****************************************************************************
 * glpong - opengl/sdl game of the original video game; pong.                *
 * Copyright (C) 2001-2012 Erik Greenwald <erik@elfga.com>                   *
 *                                                                           *
 * This program is free software; you can redistribute it and/or modify      *
 * it under the terms of the GNU General Public License as published by      *
 * the Free Software Foundation; either version 2 of the License, or         *
 * (at your option) any later version.                                       *
 *                                                                           *
 * This program is distributed in the hope that it will be useful,           *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 * GNU General Public License for more details.                              *
 *                                                                           *
 * You should have received a copy of the GNU General Public License         *
 * along with this program; if not, write to the Free Software               *
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA *
 ****************************************************************************/

#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <png.h>

#include "image.h"

static char image_error_string[BUFSIZ];

static void
user_read_data (png_structp png_ptr, png_bytep data, png_size_t length)
{
    static size_t bar = 0;

    if (png_ptr == NULL)
	bar = 0;
    else
	memcpy (data, (void *) ((size_t)(png_ptr->io_ptr) + bar), length);
    bar += length;
    return;
}

static int
ispng (void *buf)
{
    return !png_sig_cmp (buf, 0, 4);
}

static void *
readpng (void *buf, int *width, int *height, int *bpp)
{
    png_structp png_ptr =
	png_create_read_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop info_ptr = png_create_info_struct (png_ptr);
    png_bytepp row_pointers;
    void *out;
    unsigned int i, pitch, channels, depth;

    if (png_ptr == NULL || info_ptr == NULL)
    {
	snprintf (image_error_string, BUFSIZ, "Bad allocation\n");
	return NULL;
    }
    if (setjmp (png_jmpbuf (png_ptr)))
    {
	png_destroy_read_struct (&png_ptr, &info_ptr, NULL);
	snprintf (image_error_string, BUFSIZ, "Woops!\n");
	return NULL;
    }
    png_set_read_fn (png_ptr, buf, user_read_data);

    png_read_png (png_ptr, info_ptr,
	PNG_TRANSFORM_PACKING | PNG_TRANSFORM_STRIP_16 |
	PNG_TRANSFORM_EXPAND, png_voidp_NULL);
    pitch = png_get_rowbytes (png_ptr, info_ptr);
    *width = png_get_image_width (png_ptr, info_ptr);
    *height = png_get_image_height (png_ptr, info_ptr);
    channels = png_get_channels (png_ptr, info_ptr);
    depth = png_get_bit_depth (png_ptr, info_ptr);
    *bpp = channels;

    row_pointers = png_get_rows (png_ptr, info_ptr);

    out = malloc ((*width) * (*height) * (*bpp));
    for (i = 0; i < info_ptr->height; ++i)
	memcpy ((void *)((size_t)out + i * pitch), row_pointers[i], pitch);
    png_destroy_read_struct (&png_ptr, &info_ptr, png_infopp_NULL);
    return out;
}

/************************************************************************/
/* public interface */

char *
image_error ()
{
    return image_error_string;
}

void *
image_load (char *filename, int *width, int *height, int *bpp)
{
    void *image, *buf;
    int fd, size;
    struct stat sb;

    if (stat (filename, &sb) == -1)
	return NULL;
    buf = malloc (sb.st_size);
    fd = open (filename, O_RDONLY);
    size = read (fd, buf, sb.st_size);
    close (fd);
    user_read_data (NULL, NULL, 0);
    if (size != sb.st_size)
    {
	snprintf (image_error_string, BUFSIZ, "Bad read! (%s)\n", filename);
	free (buf);
	return NULL;
    }
    if (!ispng (buf))
    {
	snprintf (image_error_string, BUFSIZ, "%s is not a PNG", filename);
	return NULL;
    }
    image = readpng (buf, width, height, bpp);
    free (buf);
    return image;
}

