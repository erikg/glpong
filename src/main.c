
/*****************************************************************************
 * glpong - opengl/sdl game of the original video game; pong.                *
 * Copyright (C) 2001-2025 Erik Greenwald <erik@elfga.com>                   *
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

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#ifndef WIN32
# include <unistd.h>
#endif
#include <ctype.h>

#ifdef __linux__
#ifndef __USE_BSD
#define __USE_BSD
#endif
#include <getopt.h>
#endif

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include "ai.h"
#include "game.h"
#include "input.h"
#include "map.h"
#include "physics.h"
#include "sound.h"
#include "text.h"
#include "timer.h"
#include "video.h"

SDL_Window *window;

void
main_add_map ()
{
    int i;
    float wall[4][3][3] = {
	{{4.2, -.3, -9}, {4.2, -.3, 9}, {4.0, -.3, 9}},
	{{4.2, -.3, 9}, {4.0, -.3, -9}, {4.2, -.3, -9}},
	{{-4.2, -.3, -9}, {-4.2, -.3, 9}, {-4.0, -.3, 9}},
	{{-4.2, -.3, 9}, {-4.0, -.3, -9}, {-4.2, -.3, -9}}
    };
    float goal[4][3][3] = {
	{{-4, -.3, 8.4}, {4, -.3, 8.4}, {4, -.3, 8.2}},
	{{-4, -.3, 8.4}, {-4, -.3, 8.2}, {4, -.3, 8.2}},
	{{-4, -.3, -8.4}, {4, -.3, -8.4}, {4, -.3, -8.2}},
	{{-4, -.3, -8.4}, {-4, -.3, -8.2}, {4, -.3, -8.2}},
    };

    for (i = 0; i < 4; ++i)
	map_add_tri (MAP_WALL, wall[i]);
    for (i = 0; i < 4; ++i)
	map_add_tri (MAP_GATE, goal[i]);
    return;
}

int
doversion (char *name)
{
    printf ("\
%s (%s) Copyright (C) 2001-2025 Erik Greenwald <erik@elfga.com>\n\
%s comes with ABSOLUTELY NO WARRANTY. Please read the GPL for details.\n\n", name, PACKAGE, VERSION);
    return 0;
}

int
dohelp (char *name)
{
    doversion (name);
    printf ("Usage\n\
\t%s [-fwhv] [-w <width>x<height>]\n\
\n\
 -f                      Force fullscreen\n\
 -g <width>x<height>     Set resolution\n\
 -w                      Force windowed (default)\n\
 -h                      Display this help screen\n\
 -v                      Display the version\n\
\n", name);
    return 0;
}

int
main (int argc, char **argv)
{
    game_t *g;
    int width, height;
    char buf[BUFSIZ], *name = *argv;
    int c, fullscreen = 0;

    width = 640;
    height = 480;

#ifndef WIN32
    while ((c = getopt (argc, argv, "g:fwhv")) != -1)
	switch (tolower (c))
	{
	case ':':
	    printf ("Option \"%s\" missing parameter\n", optarg);
	    dohelp (name);
	    return 1;
	case '?':
	    dohelp (name);
	    return 1;
	case 'f':
	    fullscreen = SDL_WINDOW_FULLSCREEN;
	    break;
	case 'g':
	    sscanf (optarg, "%dx%d", &width, &height);
	    break;
	case 'h':
	    dohelp (name);
	    return EXIT_SUCCESS;
	case 'v':
	    doversion (name);
	    return EXIT_SUCCESS;
	case 'w':
	    fullscreen = 0;
	    break;
	default:
	    printf ("Unknown error (option: %c)\n", c);
	    dohelp (name);
	    return 2;
	}
#endif

    SDL_Init (SDL_INIT_VIDEO);

    /* Try to create a modern OpenGL context first */
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    window = SDL_CreateWindow("glpong (C) 2001-2025 Erik Greenwald", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL | fullscreen);
    SDL_GLContext context = SDL_GL_CreateContext(window);

    if (!context) {
        /* Fallback to legacy OpenGL */
        printf("Failed to create OpenGL 3.3 context, falling back to legacy OpenGL\n");
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, 0);
        context = SDL_GL_CreateContext(window);
        if (!context) {
            fprintf(stderr, "Failed to create OpenGL context: %s\n", SDL_GetError());
            SDL_Quit();
            exit(-1);
        }
    }

    /* Enable V-Sync */
    SDL_GL_SetSwapInterval(1);

    atexit (SDL_Quit);

    SDL_ShowCursor (0);

    g = game_init ();

    input_init ();
    physics_init ();
    text_init ();
    timer_init ();
    sound_init ();
    video_init (width, height);

    map_new ();
    main_add_map ();

    while (input_do (g))
    {
	timer_update ();
	ai_do (g);
	physics_do (g);
	video_do (g);
    }
    game_end (g);
    sound_close ();
    printf ("%s\n", timer_report (buf));
    SDL_Quit ();
    return 0;
}
