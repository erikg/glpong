
/*****************************************************************************
 * glpong - opengl/sdl game of the original video game; pong.                *
 * Copyright (C) 2001-2004 Erik Greenwald <erik@smluc.org>                   *
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

/*
 * $Id: text.c,v 1.18 2004/04/18 01:39:29 erik Exp $ 
 */

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <SDL_opengl.h>
#include <SDL.h>

#include "image.h"
#include "text.h"
#include "video.h"

unsigned int textid;

	/*
	 * evil magic bound to our texture 
	 */
float texcoords[][4] = {
    {32.0, 32.0, 64.0, 64.0},	/* 0 */
    {0.0, 0, 32.0, 32.0},	/* 1 */
    {32.0, 0, 64.0, 32.0},	/* 2 */
    {64.0, 0, 96.0, 32.0},	/* 3 */
    {96.0, 0, 128.0, 32.0},	/* 4 */
    {128.0, 0, 160.0, 32.0},	/* 5 */
    {160.0, 0, 192.0, 32.0},	/* 6 */
    {192.0, 0, 224.0, 32.0},	/* 7 */
    {224.0, 0.0, 256.0, 32.0},	/* 8 */
    {0.0, 32.0, 32.0, 64.0},	/* 9 */
    {0.0, 96.0, 112.0, 128.0},	/* human */
    {0.0, 64.0, 100.0, 96.0},	/* machine */
    {0.0, 128.0, 60.0, 160.0},	/* fps */
};

void
text_init ()
{
    video_load_texture ("texture", &textid);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexGeni (GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGeni (GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    return;
}

void
text_mode (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glOrtho (0,w,0,h,-1,1);
    glMatrixMode (GL_MODELVIEW);
    return;
}

void
text_draw_static (int id, float x, float y, float w, float h)
{
    glEnable (GL_TEXTURE_2D);
    glBindTexture (GL_TEXTURE_2D, textid);
    glBegin (GL_TRIANGLE_STRIP);
    glTexCoord2d (texcoords[id][0] / 256.0, texcoords[id][1] / 256.0);
    glVertex3f (x, y + h, 0);
    glTexCoord2d (texcoords[id][2] / 256.0, texcoords[id][1] / 256.0);
    glVertex3f (x + w, y + h, 0);
    glTexCoord2d (texcoords[id][0] / 256.0, texcoords[id][3] / 256.0);
    glVertex3f (x, y, 0);
    glTexCoord2d (texcoords[id][2] / 256.0, texcoords[id][3] / 256.0);
    glVertex3f (x + w, y, 0);
    glEnd ();
    glDisable (GL_TEXTURE_2D);
    return;
}

void
text_draw_string (char *s, float x, float y, float w, float h)
{
    float mlen = w / (float)strlen (s);

    while (*s++)
    {
	if (*s >= '0' && *s <= '9')
	    text_draw_static (*s - '0', x, y, mlen, h);
	x += mlen;
    }
    return;
}

void
text_destroy ()
{
    return;
}
