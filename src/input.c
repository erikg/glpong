
/*****************************************************************************
 * glpong - opengl/sdl game of the original video game; pong.                *
 * Copyright (C) 2001-2010 Erik Greenwald <erik@smluc.org>                   *
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
 * $Id: input.c,v 1.15 2010/01/06 01:06:00 erik Exp $ 
 */

#include <SDL.h>
#include <string.h>

#include "game.h"
#include "input.h"
#include "timer.h"
#include "video.h"

static char state[SDLK_LAST];

void
input_init ()
{
    memset (state, 0, SDLK_LAST);
    return;
}

int
input_do (game_t * g)
{
    static SDL_Event ev;

    if (SDL_PollEvent (&ev) != 0)
	switch (ev.type)
	{
	case SDL_KEYDOWN:
	    if (ev.key.keysym.sym == 27)
		return 0;
	    else if (ev.key.keysym.sym == SDLK_F10)
		video_screenshot ();
	    else
		state[ev.key.keysym.sym] = 1;
	    break;
	case SDL_KEYUP:
	    state[ev.key.keysym.sym] = 0;
	    break;
	}
    if (state[SDLK_RIGHT])
	g->player[PLAYER].X += 4.0 * timer_delta ();
    if (state[SDLK_LEFT])
	g->player[PLAYER].X -= 4.0 * timer_delta ();
    return 1;
}
