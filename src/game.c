
/*****************************************************************************
 * glpong - opengl/sdl game of the original video game; pong.                *
 * Copyright (C) 2001-2005 Erik Greenwald <erik@smluc.org>                   *
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
 * $Id: game.c,v 1.21 2005/03/18 17:44:26 erik Exp $ 
 */

#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

#include "game.h"

	/*
	 * define pi if it's not already defined 
	 */
#ifndef M_PI
# ifdef PI
#   define M_PI PI
# else
#   define M_PI 3.14159265358979323846
# endif
#endif

#define INITVEL 4.0
#define INITCOS 0.7

game_t *
game_init ()
{
    game_t *g;

    g = (game_t *) malloc (sizeof (game_t));
    srand (time (0) + getpid ());
    g->player[PLAYER].X = 0;
    g->player[MACHINE].X = 0;
    g->player[PLAYER].score = 0;
    g->player[MACHINE].score = 0;
    game_newball (g);
    return g;
}

void
game_newball (game_t * g)
{
    float angle;

    /* 
     * the puck emission would be towards one of the players relatively
     * aggressively, so it doesn't bounce side to side too much and get
     * boring...
     *
     * Probably a good heuristic is not to be any further than 45 degrees from
     * the play line... so our emission range would be (in radians)
     * [pi/4,3pi/4] and [5pi/4,7pi/4], the second being equilveant to
     * [-pi/4,-3pi/4]. With a single sweep being pi/2, what we can do is get
     * a random number between 0 and pi, and subtract pi/2 from that, resulting
     * in a range of [-pi/4,pi/4]. We can then use sign*(range + pi/4) to get
     * the output angle. 
     */
    angle = ((float)rand()/(float)RAND_MAX - 0.5) * M_PI;
    angle = (angle>0?1:-1) * (fabs(angle) + M_PI/4.0);

    g->ball->pos[0] = 0.0;
    g->ball->pos[1] = 0.0;
    g->ball->pos[2] = 0.0;
    g->ball->vel[0] = INITVEL * cos (angle);
    g->ball->vel[1] = INITVEL * sin (angle);
    g->ball->vel[2] = 0;
    g->ball->speed = INITVEL;
    g->ball->radius = .1;
}

void
game_end (game_t * g)
{
    free (g);
    return;
}
