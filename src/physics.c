
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
 * $Id: physics.c,v 1.8 2003/06/27 14:11:44 erik Exp $ 
 */

#include <stdio.h>
#include <math.h>
#include "game.h"
#include "physics.h"
#include "sound.h"
#include "timer.h"

#define MAXVEL 70.0
#define VELAMP 1.4

int
sign (float x)
{
    if (x > 0)
	return 1;
    if (x < 0)
	return -1;
    return 0;
}

void
physics_init ()
{
    return;
}

void
physics_do (game_t * g)
{
    if (fabs (g->ballX) > 4.0 && (sign (g->ballX) == sign (g->ballI)))
	g->ballI *= -1;

    if (g->machineX > 3)
	g->machineX = 3;
    if (g->machineX < -3)
	g->machineX = -3;
    if (g->playerX > 3)
	g->playerX = 3;
    if (g->playerX < -3)
	g->playerX = -3;

    if (g->ballY > 8.0 && g->ballJ > 0)
      {
	  if (fabs (g->playerX - g->ballX) > 1.0)
	    {
		g->machinescore++;
		game_newball (g);
		sound_play (SOUND_NNGNGNG, NULL, NULL, NULL);

	    }
	  else
	    {
		g->ballI += VELAMP * -sin ((g->playerX - g->ballX));
		g->ballJ *= VELAMP * -cos (1 * (g->playerX - g->ballX));
		sound_play (SOUND_BOINK, NULL, NULL, NULL);
	    }
      }

    if (g->ballY < -8.0 && g->ballJ < 0)
      {
	  if (fabs (g->machineX - g->ballX) > 1.0)
	    {
		g->playerscore++;
		game_newball (g);
		sound_play (SOUND_NNGNGNG, NULL, NULL, NULL);
	    }
	  else
	    {
		g->ballI += VELAMP * -sin ((g->machineX - g->ballX));
		g->ballJ *= -VELAMP * cos (1 * (g->machineX - g->ballX));
		sound_play (SOUND_BOINK, NULL, NULL, NULL);
	    }
      }

    if (fabs (g->ballJ) < .3)
      {
	  if (g->ballJ < 0)
	      g->ballJ = -.3;
	  else
	      g->ballJ = .3;
      }

    if (g->ballJ > MAXVEL)
	g->ballJ = MAXVEL;
    if (g->ballJ < -MAXVEL)
	g->ballJ = -MAXVEL;

    g->ballX += g->ballI * timer_delta ();
    g->ballY += g->ballJ * timer_delta ();
    return;
}
