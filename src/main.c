
/*****************************************************************************
 * glpong - opengl/sdl game of the original video game; pong.                *
 * Copyright (C) 2001-2003 Erik Greenwald <erik@smluc.org>                   *
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
 * $Id: main.c,v 1.15 2003/07/27 14:49:34 erik Exp $ 
 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

#include "ai.h"
#include "game.h"
#include "input.h"
#include "map.h"
#include "physics.h"
#include "sound.h"
#include "text.h"
#include "timer.h"
#include "video.h"

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
main (int argc, char **argv)
{
    game_t *g;
    char buf[BUFSIZ];

    if (argc > 1)
	printf ("%s: I don't do parms yet\n", argv[0]);

    SDL_Init (SDL_INIT_VIDEO);
    if (argc == 1)
	SDL_SetVideoMode (640, 480, 32, SDL_OPENGL | SDL_DOUBLEBUF);
    else
	SDL_SetVideoMode (640, 480, 32,
	    SDL_OPENGL | SDL_DOUBLEBUF | SDL_FULLSCREEN);
    atexit (SDL_Quit);

    SDL_ShowCursor (0);
    SDL_WM_SetCaption ("glpong (C) 2001-2003 Erik Greenwald", "glpong");

    g = game_init ();

    input_init ();
    physics_init ();
    text_init ();
    timer_init ();
    sound_init ();
    video_init ();

    map_new ();
    main_add_map ();

    while (input_do (g))
    {
	timer_update ();
	ai_do (g);
	physics_do (g);
	video_do (g);
    }
    printf ("%s\n", timer_report (buf));
    SDL_Quit ();
    return 0;
}
