
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
 * $Id: timer.c,v 1.3 2003/06/22 22:48:20 erik Exp $
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
 * $Id: timer.c,v 1.3 2003/06/22 22:48:20 erik Exp $ 
 */

#include <SDL_timer.h>
#include "timer.h"

static double nowtime = 0, thentime = 0, deltatime = 0, fps = 0, fpstime = 0;
static int frames = 0;

void
timer_init ()
{
    nowtime = SDL_GetTicks ();
    timer_update ();
    return;
}

void
timer_update ()
{
    thentime = nowtime;
    nowtime = (double)SDL_GetTicks ();
    deltatime = (nowtime - thentime) / 1000;
    frames++;
    if (nowtime - fpstime > 500)
    {
	fps = 1000 * frames / (nowtime - fpstime);
	frames = 0;
	fpstime = nowtime;
    }
    return;
}

double
timer_delta ()
{
    return deltatime;
}

double
timer_fps ()
{
    return fps;
}
