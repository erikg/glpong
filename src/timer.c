
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
 * $Id: timer.c,v 1.15 2004/04/18 01:39:29 erik Exp $ 
 */

#include <stdio.h>
#include <time.h>
#include <SDL_timer.h>
#include "timer.h"

static double nowtime = 0, thentime = 0, deltatime = 0, fps = 0, fpstime =
    0, min = 999, max = 0, firsttime = 0, clock0 = 0;
static int frames = 0, oframes = 0;

char *
timer_report (char *buf)
{
    double cpuseconds = (double)(clock () - clock0) / (double)CLOCKS_PER_SEC;
    double wallseconds = (nowtime - firsttime) / 1000.0;
    double avefps = (double)oframes / (double)wallseconds;

    snprintf (buf, BUFSIZ, "\
average fps:         %f\n\
min fps:             %f\n\
max fps:             %f\n\
seconds in game:     %f\n\
seconds of cpu time: %f\n\
%% cpu usage:        %f\n\
Max theoretical FPS: %f\n", avefps, 1.0 / max, 1.0 / min, wallseconds, cpuseconds, 100.0 * cpuseconds / wallseconds, oframes / cpuseconds);

    return buf;
}

void
timer_init ()
{
    nowtime = SDL_GetTicks ();
    firsttime = nowtime;
    clock0 = clock ();
    timer_update ();
    return;
}

void
timer_update ()
{
    thentime = nowtime;
    nowtime = (double)SDL_GetTicks ();
    deltatime = (nowtime - thentime) / 1000;
    if (deltatime < min)
	min = deltatime;
    if (deltatime > max)
	max = deltatime;
    frames++;
    oframes++;
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
