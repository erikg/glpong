
/*****************************************************************************
 * glpong - opengl/sdl/openal pong game                                      *
 * Copyright (C) 2003 Erik Greenwald <erik@smluc.org>                        *
 *                                                                           *
 * This program takes a directory as an argument, then walks through the     *
 * directory looking for duplicate and partially duplicate files. If it      *
 * an exact duplicate, it deletes one and creates a hardlink to the other,   *
 * minimizing disk usage. If it finds a pair of files where they contain the *
 * same data up to the size of the smaller file, it will prompt if you want  *
 * to combine them. If you say yes, it will delete the smaller of the files  *
 * and hardlink to the larger.                                               *
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
 * $Id: main.c,v 1.4 2003/06/22 22:48:20 erik Exp $
 */

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
 * $Id: main.c,v 1.4 2003/06/22 22:48:20 erik Exp $ 
 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

#include "ai.h"
#include "game.h"
#include "input.h"
#include "physics.h"
#include "sound.h"
#include "text.h"
#include "timer.h"
#include "video.h"

int
main (int argc, char **argv)
{
    game_t *g;

    if(argc>1)printf("%s: I don't do parms yet\n", argv[0]);

    SDL_Init (SDL_INIT_VIDEO);
    if (argc == 1)
	SDL_SetVideoMode (640, 480, 32, SDL_OPENGL | SDL_DOUBLEBUF);
    else
	SDL_SetVideoMode (640, 480, 32,
	    SDL_OPENGL | SDL_DOUBLEBUF | SDL_FULLSCREEN);
    atexit (SDL_Quit);

    SDL_ShowCursor (0);
    SDL_WM_SetCaption ("glpong (C) 2001 Erik Greenwald", "glpong");

    g = game_init ();

    input_init ();
    physics_init ();
    text_init ();
    timer_init ();
	sound_init();
    video_init ();

    while (input_do (g))
    {
	timer_update ();
	ai_do (g);
	physics_do (g);
	video_do (g);
    }
    SDL_Quit ();
    return 0;
}
