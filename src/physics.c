
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
 * $Id: physics.c,v 1.18 2003/07/31 04:09:52 erik Exp $ 
 */
#include <stdio.h>
#include <math.h>
#include "game.h"
#include "map.h"
#include "physics.h"
#include "sound.h"
#include "timer.h"

#define MAXVEL 70.0
#define VELAMP 1.4

#define sign(x) (x>0?1:x<0?-1:0)

/***** Math stuff *********************************************************/

float
dot (float a[3], float b[3])
{
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

float *
cross (float v[3], float a[3], float b[3])
{
    v[0] = (a[1] * b[2] - a[2] * b[1]);
    v[1] = (a[2] * b[0] - a[0] * b[2]);
    v[2] = (a[0] * b[1] - a[1] * b[0]);
    return v;
}

float *
add (float v[3], float a[3], float b[3])
{
    v[0] = a[0] + b[0];
    v[1] = a[1] + b[1];
    v[2] = a[2] + b[2];
    return v;
}

float *
subtract (float v[3], float a[3], float b[3])
{
    v[0] = a[0] - b[0];
    v[1] = a[1] - b[1];
    v[2] = a[2] - b[2];
    return v;
}

float *
scale (float v[3], float a[3], float scale)
{
    v[0] = a[0] * scale;
    v[1] = a[1] * scale;
    v[2] = a[2] * scale;
    return v;
}

float
magnitude (float a[3])
{
    return sqrt (dot (a, a));
}

float *
normalize (float v[3], float a[3])
{
    return scale (v, a, 1.0 / magnitude (a));
}

/***** Physics stuff ******************************************************/

void
physics_init ()
{
    return;
}

float up[3] = { 0, 0, 1 };
float bvel[3], *bpos;
float nearestdist, nearestnorm[3], n[3];
int nearesttype;

float
dist (float p0[3], float p1[3])
{
    float w[3], a[3], d;

    subtract (w, p0, p1);
    normalize (n, cross (a, w, up));
    d = dot (subtract (a, p0, bpos), n);
    if (d < 0 || d > nearestdist)
	return -1.0;
    nearestdist = d;
    memcpy (nearestnorm, n, sizeof (float) * 3);
}

void
physdist (struct map_tri *m)
{
    float x;

    if (dist (m->v[0], m->v[1]) >= 0)
	nearesttype = m->type;
    if (dist (m->v[0], m->v[2]) >= 0)
	nearesttype = m->type;
    if (dist (m->v[1], m->v[2]) >= 0)
	nearesttype = m->type;
}

void
physics_do (game_t * g)
{
    int i;
    float ballvelleft = magnitude (g->ball[0].vel);

    memcpy (bvel, g->ball[0].vel, sizeof (float) * 3);

    /*
     * keep the paddles on the grid 
     */
    for (i = 0; i <= 1; ++i)
	if (fabs (g->player[i].X) > 3)
	    g->player[i].X = sign (g->player[i].X) * 3;

    /*
     * wall bounce 
     *
     if (fabs (g->ball[0].pos[0]) > 4.0
     && (sign (g->ball[0].pos[0]) == sign (g->ball[0].vel[1])))
     g->ball[0].vel[1] *= -1;
     */
    bpos = g->ball->pos;
    do
      {
	  printf ("%.2f %.2f %.2f   ->   %.2f %.2f %.2f\n",
		  bpos[0], bpos[1], bpos[2], bvel[0], bvel[1], bvel[2]);
	  map_map_tri (physdist);
	  switch (nearesttype)
	    {
	    case MAP_WALL:
		{
		    float t[3];

		    scale (t, bvel, nearestdist);
		    add (bpos, bpos, t);
		    bvel[0] = -bvel[0];
		}
		break;
	    case MAP_GATE:
		goto GOAL;
		break;
	    default:
		printf ("Unknown collision type: %d\n", nearesttype);
		exit (-1);
	    };
	  ballvelleft -= nearestdist;
      }
    while (ballvelleft > nearestdist);
    memcpy (g->ball[0].vel, bvel, sizeof (float) * 3);

    /*
     * paddle bounce
     *
     i = sign (g->ball[0].vel[1]) > 0 ? 1 : 0;
     if (fabs (g->ball[0].pos[1]) > 8.0
     && fabs (g->player[i].X - g->ball[0].pos[0]) < 1.0)
     {
     g->ball[0].vel[1] +=
     VELAMP * -sin ((g->player[i].X - g->ball[0].pos[0]));
     g->ball[0].vel[0] *=
     VELAMP * -cos (1 * (g->player[i].X - g->ball[0].pos[0]));
     sound_play (SOUND_BOINK, NULL, NULL, NULL);
     }
     */
  GOAL:
    /*
     * goal made 
     */
    if (fabs (g->ball[0].pos[1]) > 9.0)
      {
	  g->player[sign (g->ball[0].pos[1]) == -1 ? 0 : 1].score++;
	  game_newball (g);
	  sound_play (SOUND_NNGNGNG, NULL, NULL, NULL);
      }

    /*
     * cap ball velocity 
     */
    if (g->ball[0].vel[0] > MAXVEL)
	g->ball[0].vel[0] = MAXVEL;
    if (g->ball[0].vel[0] < -MAXVEL)
	g->ball[0].vel[0] = -MAXVEL;

    /*
     * update ball location 
     */
    g->ball[0].pos[0] += g->ball[0].vel[1] * timer_delta ();
    g->ball[0].pos[1] += g->ball[0].vel[0] * timer_delta ();

    return;
}
