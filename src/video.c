
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
 * $Id: video.c,v 1.34 2004/04/25 22:57:15 erik Exp $ 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include <image.h>
#include <SDL_opengl.h>

#include "game.h"
#include "image.h"
#include "map.h"
#include "text.h"
#include "timer.h"
#include "video.h"

Uint32 rmask, gmask, bmask, amask;

GLfloat light_position[] = { -2, 5.0, 6, 0.0 };
char buf[1024];
GLuint refl;

struct display_s {
    int width, height, depth;
} display =
{
0, 0, 0};

void
draw_paddle (int reflective, float x)
{
    /*
     * range of x is [-3,3] 
     */
    float left, right;

    left = 0.0833333333333333 * x + .25;
    right = 0.0833333333333333 * x + .75;
    if (reflective)
    {
	glEnable (GL_TEXTURE_2D);
    }
    glBindTexture (GL_TEXTURE_2D, refl);
    glBegin (GL_TRIANGLE_STRIP);
    glTexCoord2d (left, 1);
    glNormal3f (-.1, -.1, 1);
    glVertex3f (-1, -.3, .1);
    glTexCoord2d (left, 0);
    glNormal3f (-.1, .1, 1);
    glVertex3f (-1, .3, .1);
    glTexCoord2d (right, 1);
    glNormal3f (.1, -.1, 1);
    glVertex3f (1, -.3, .1);
    glTexCoord2d (right, 0);
    glNormal3f (.1, .1, 1);
    glVertex3f (1, .3, .1);
    glEnd ();
    glDisable (GL_TEXTURE_2D);

    glBegin (GL_TRIANGLE_STRIP);
    glNormal3f (-.1, 1, -.1);
    glVertex3f (-1, .3, -.1);
    glNormal3f (-.1, 1, .1);
    glVertex3f (-1, .3, .1);
    glNormal3f (.1, 1, -.1);
    glVertex3f (1, .3, -.1);
    glNormal3f (.1, 1, .1);
    glVertex3f (1, .3, .1);

    glNormal3f (1, 0, 0);
    glVertex3f (1, -.3, -.1);
    glVertex3f (1, -.3, .1);
    glVertex3f (1, .3, -.1);
    glVertex3f (1, .3, .1);

    glNormal3f (-1, 0, 0);
    glVertex3f (-1, -.3, -.1);
    glVertex3f (-1, -.3, .1);
    glVertex3f (-1, .3, -.1);
    glVertex3f (-1, .3, .1);
    glEnd ();
    return;
}

static void
reshape (int w, int h)
{
    display.width = w;
    display.height = h;
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glFrustum (-w / h, w / h, -1, 1, 1.5, 33);
    glMatrixMode (GL_MODELVIEW);
    return;
}

unsigned int
video_load_texture (char *file, unsigned int *texid)
{
    void *t = NULL;
    char buf[BUFSIZ];
    int width, height, bpp, type;

    glEnable (GL_TEXTURE_2D);
    glGenTextures (1, (GLuint *) texid);

    snprintf (buf, BUFSIZ, "%s/%s.png", DATADIR, file);
    t = image_load (buf, &width, &height, &bpp);
    if (t == NULL)
    {
	printf ("couldn't read %s: %s\n", buf, image_error ());
	snprintf (buf, BUFSIZ, "../data/%s.png", file);
	t = image_load (buf, &width, &height, &bpp);
    }
    if (t == NULL)
    {
	printf ("couldn't read %s: %s\n", buf, image_error ());
	snprintf (buf, BUFSIZ, "data/%s.png", file);
	t = image_load (buf, &width, &height, &bpp);
    }
    if (t == NULL)
    {
	printf ("couldn't read %s: %s\n", buf, image_error ());
	fprintf (stderr, "Cannot load texture: %s\nAborting...\n", file);
	SDL_Quit ();
	exit (-1);
    }
    switch (bpp)
    {
    case 4:
	type = GL_RGBA;
	break;
    case 3:
	type = GL_RGB;
	break;
    default:
	printf ("Unknown depth: %d (reading %s)\n", bpp, file);
	exit (-1);
    }
    glBindTexture (GL_TEXTURE_2D, *texid);
    glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, type,
	GL_UNSIGNED_BYTE, t);
    return *texid;
}

static void
form_reflmap ()
{
    video_load_texture ("refl", (unsigned int *)&refl);
    glTexGeni (GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGeni (GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    return;
}

void
video_init (int width, int height)
{
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat light_ambient[] = { 0, 0, 0, 0 };

    /*
     * snatched from sdldoc.sf.net 
     */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    form_reflmap ();

    glShadeModel (GL_SMOOTH);
    glMaterialfv (GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv (GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv (GL_LIGHT1, GL_AMBIENT, light_ambient);

    glEnable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
    glEnable (GL_DEPTH_TEST);

    glClearColor (0.0, 0, 0.0, 1);

    reshape (width, height);
    return;
}

int angle = 0;
static int curcolor = 0x000000;

static void
drawtri (struct map_tri *t)
{
    switch (t->type)
    {
    case MAP_WALL:
	if (curcolor != 0xff0000)
	{
	    curcolor = 0xff0000;
	    glColor3f (1, 0, 0);
	}
	glVertex3fv (t->v[0]);
	glVertex3fv (t->v[1]);
	glVertex3fv (t->v[2]);
	break;
    case MAP_GATE:
#ifdef DRAW_GATE
	if (curcolor != 0x00ff00)
	{
	    curcolor = 0x00ff00;
	    glColor3f (0, .5, 0);
	}
	glVertex3fv (t->v[0]);
	glVertex3fv (t->v[1]);
	glVertex3fv (t->v[2]);
#endif
	break;
    }
    return;
}

void
video_do (game_t * g)
{
    int x;

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity ();

    glTranslatef (0, 0, -15);
    glPushMatrix ();
    glRotatef (20, 1, 0, 0);

    glLightfv (GL_LIGHT0, GL_POSITION, light_position);

    /*
     * machine paddle 
     */
    glPushMatrix ();
    glTranslatef (g->player[MACHINE].X, 0, -8);
    draw_paddle (1, g->player[MACHINE].X);
    glPopMatrix ();

    /*
     * human paddle 
     */
    glPushMatrix ();
    glTranslatef (g->player[PLAYER].X, 0, 8);
    draw_paddle (0, g->player[PLAYER].X);
    glPopMatrix ();

    /*
     * ball 
     */
    glDisable (GL_LIGHTING);

    glPushMatrix ();
    glTranslatef (g->ball->pos[0], 0, g->ball->pos[1]);
    glColor3f (1, 1, 1);
    glBegin (GL_TRIANGLE_STRIP);
    glVertex3f (-g->ball->radius, -.3, -g->ball->radius);
    glVertex3f (-g->ball->radius, -.2, -g->ball->radius);
    glVertex3f (g->ball->radius, -.3, -g->ball->radius);
    glVertex3f (g->ball->radius, -.2, -g->ball->radius);
    glEnd ();
    glPopMatrix ();

    /*
     * strips 
     */
    curcolor = 0xffffff;
    glBegin (GL_TRIANGLES);
    map_map_tri (drawtri);
    glEnd ();

    /*
     * text 
     */
    glPopMatrix ();
    glColor3f (1, 1, 1);
    text_mode (display.width, display.height);

    text_draw_static_ca (TEXT_MACHINE, display.width - 100, display.height - 32, 100, 32);
    sprintf (buf, "%d", g->player[MACHINE].score);
    x = strlen (buf) * 32;
    text_draw_string_ca (buf, display.width - 100, display.height - 32 * 2, x, 32);

    text_draw_static_ca (TEXT_HUMAN, 100, display.height - 32, 112, 32);
    sprintf (buf, "%d", g->player[PLAYER].score);
    x = strlen (buf) * 32;
    text_draw_string_ca (buf, 100, display.height - 32 * 2, x, 32);

    text_draw_static_ca (TEXT_FPS, display.width / 2, 66, 60, 32);
    sprintf (buf, "%d", (int)timer_fps ());
    x = strlen (buf) * 32;
    text_draw_string_ca (buf, display.width / 2, 32, x, 32);

    glEnable (GL_LIGHTING);
    reshape (display.width, display.height);
    SDL_GL_SwapBuffers ();
    return;
}

static void
flip_surface (SDL_Surface * s)
{
    int x;
    Uint8 *buf;

    buf = (Uint8 *) malloc (s->pitch);

    for (x = 0; x < (480 / 2); x++)
    {
	memcpy (buf, (Uint8 *) (s->pixels + x * s->pitch), s->pitch);
	memcpy ((Uint8 *) (s->pixels + x * s->pitch),
	    (Uint8 *) (s->pixels + (479 - x) * s->pitch), s->pitch);
	memcpy ((Uint8 *) (s->pixels + (479 - x) * s->pitch), buf, s->pitch);
    }
    return;
}

void
video_screenshot ()
{
    SDL_Surface *ss;

    ss = SDL_CreateRGBSurface (0, 640, 480, 24, 0, 0, 0, 0);
    glReadPixels (0, 0, 640, 480, GL_BGR, GL_UNSIGNED_BYTE, ss->pixels);
    flip_surface (ss);
    SDL_SaveBMP (ss, "screenshot.bmp");
    return;
}
