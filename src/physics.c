
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
 * $Id: physics.c,v 1.12 2003/07/27 14:49:34 erik Exp $ 
 */

#include <stdio.h>
#include <math.h>
#include "game.h"
#include "physics.h"
#include "sound.h"
#include "timer.h"

#define MAXVEL 70.0
#define VELAMP 1.4

#define sign(x) (x>0?1:x<0?-1:0)

void
physics_init ()
{
    return;
}

void
physics_do (game_t * g)
{
    float ballvel =
	sqrt (g->ball->vel[0] * g->ball->vel[0] +
	g->ball->vel[1] * g->ball->vel[1] + g->ball->vel[2] * g->ball->vel[2]);

    /*
     * keep the paddles on the grid 
     */
    if (g->player[MACHINE].X > 3)
	g->player[MACHINE].X = 3;
    if (g->player[MACHINE].X < -3)
	g->player[MACHINE].X = -3;
    if (g->player[PLAYER].X > 3)
	g->player[PLAYER].X = 3;
    if (g->player[PLAYER].X < -3)
	g->player[PLAYER].X = -3;

    /*
     * wall bounce 
     */
    if (fabs (g->ball->pos[0]) > 4.0
	&& (sign (g->ball->pos[0]) == sign (g->ball->vel[1])))
	g->ball->vel[1] *= -1;

    /*
     * goal made 
     */
    if (g->ball->pos[1] > 8.0 && g->ball->vel[0] > 0)
    {
	if (fabs (g->player[PLAYER].X - g->ball->pos[0]) > 1.0)
	{
	    g->player[MACHINE].score++;
	    game_newball (g);
	    sound_play (SOUND_NNGNGNG, NULL, NULL, NULL);

	} else
	{
	    g->ball->vel[1] +=
		VELAMP * -sin ((g->player[PLAYER].X - g->ball->pos[0]));
	    g->ball->vel[0] *=
		VELAMP * -cos (1 * (g->player[PLAYER].X - g->ball->pos[0]));
	    sound_play (SOUND_BOINK, NULL, NULL, NULL);
	}
    }

    if (g->ball->pos[1] < -8.0 && g->ball->vel[0] < 0)
    {
	if (fabs (g->player[MACHINE].X - g->ball->pos[0]) > 1.0)
	{
	    g->player[PLAYER].score++;
	    game_newball (g);
	    sound_play (SOUND_NNGNGNG, NULL, NULL, NULL);
	} else
	{
	    g->ball->vel[1] +=
		VELAMP * -sin ((g->player[MACHINE].X - g->ball->pos[0]));
	    g->ball->vel[0] *=
		-VELAMP * cos (1 * (g->player[MACHINE].X - g->ball->pos[0]));
	    sound_play (SOUND_BOINK, NULL, NULL, NULL);
	}
    }

    /*
     * cap ball velocity 
     */
    if (g->ball->vel[0] > MAXVEL)
	g->ball->vel[0] = MAXVEL;
    if (g->ball->vel[0] < -MAXVEL)
	g->ball->vel[0] = -MAXVEL;

    /*
     * update ball location 
     */
    g->ball->pos[0] += g->ball->vel[1] * timer_delta ();
    g->ball->pos[1] += g->ball->vel[0] * timer_delta ();

    return;
}
