
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
 * $Id: physics.c,v 1.10 2003/07/24 15:57:22 erik Exp $ 
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
	/* keep the paddles on the grid */
    if (g->machineX > 3)
	g->machineX = 3;
    if (g->machineX < -3)
	g->machineX = -3;
    if (g->playerX > 3)
	g->playerX = 3;
    if (g->playerX < -3)
	g->playerX = -3;

	/* wall bounce */
    if (fabs (g->ball_pos[0]) > 4.0 && (sign (g->ball_pos[0]) == sign (g->ball_vel[1])))
	g->ball_vel[1] *= -1;

    	/* goal made */
    if (g->ball_pos[1] > 8.0 && g->ball_vel[0] > 0)
      {
	  if (fabs (g->playerX - g->ball_pos[0]) > 1.0)
	    {
		g->machinescore++;
		game_newball (g);
		sound_play (SOUND_NNGNGNG, NULL, NULL, NULL);

	    }
	  else
	    {
		g->ball_vel[1] += VELAMP * -sin ((g->playerX - g->ball_pos[0]));
		g->ball_vel[0] *= VELAMP * -cos (1 * (g->playerX - g->ball_pos[0]));
		sound_play (SOUND_BOINK, NULL, NULL, NULL);
	    }
      }

    if (g->ball_pos[1] < -8.0 && g->ball_vel[0] < 0)
      {
	  if (fabs (g->machineX - g->ball_pos[0]) > 1.0)
	    {
		g->playerscore++;
		game_newball (g);
		sound_play (SOUND_NNGNGNG, NULL, NULL, NULL);
	    }
	  else
	    {
		g->ball_vel[1] += VELAMP * -sin ((g->machineX - g->ball_pos[0]));
		g->ball_vel[0] *= -VELAMP * cos (1 * (g->machineX - g->ball_pos[0]));
		sound_play (SOUND_BOINK, NULL, NULL, NULL);
	    }
      }

    	/* cap ball velocity */
    if (g->ball_vel[0] > MAXVEL)
	g->ball_vel[0] = MAXVEL;
    if (g->ball_vel[0] < -MAXVEL)
	g->ball_vel[0] = -MAXVEL;

    	/* update ball location */
    g->ball_pos[0] += g->ball_vel[1] * timer_delta ();
    g->ball_pos[1] += g->ball_vel[0] * timer_delta ();

    return;
}
