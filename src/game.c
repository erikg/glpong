
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
 * $Id: game.c,v 1.5 2003/06/23 22:46:51 erik Exp $ 
 */

#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

#include "game.h"

	/* define pi if it's not already defined */
#ifndef M_PI
# ifdef PI
#   define M_PI PI
# else
#   define M_PI 3.14159265358979323846
# endif
#endif

game_t *
game_init ()
{
    game_t *g;

    g = (game_t *) malloc (sizeof (game_t));
    srand (time (0) + getpid ());
    g->playerX = 0;
    g->machineX = 0;
    g->playerscore = 0;
    g->machinescore = 0;
    game_newball (g);
    return g;
}

void
game_newball (game_t * g)
{
	float angle;
	do
	{
	angle = (float)rand() * (2.0*M_PI/(float)RAND_MAX);
	}
	while(cos(angle)>.8);
    g->ballX = 0;
    g->ballY = 0;
    g->ballI = 3.0 * sin(angle);
    g->ballJ = 3.0 * cos(angle);
}
