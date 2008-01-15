
/*****************************************************************************
 * glpong - opengl/sdl game of the original video game; pong.                *
 * Copyright (C) 2001-2008 Erik Greenwald <erik@smluc.org>                   *
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
 * $Id: physics.c,v 1.35 2008/01/15 04:33:23 erik Exp $
 */

#include <stdio.h>
#include <string.h>
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

#define PRINTVECTOR(x) printf("\t%.2f\t%.2f\t%.2f", x[0], x[1], x[2]);
#if 0
float
clamp (float low, float high, float val)
{
    return val < low ? low : val > high ? high : val;
}
#endif
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
#if 0
float *
add (float v[3], float a[3], float b[3])
{
    v[0] = a[0] + b[0];
    v[1] = a[1] + b[1];
    v[2] = a[2] + b[2];
    return v;
}
#endif
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
#if 0
float
det2 (float a, float b, float c, float d)
{
    return a * d - b * c;

}

float
det3 (float a, float b, float c, float d, float e, float f, float h, float i, float j)
{
    /*
     return a * (e * j - f * i) - d * (b * j - c * i) + h * (b * f - c * e);
     */
    return a * det2 (e, f, i, j) - d * det2 (b, c, i, j) + h * det2 (b, c, e, f);
}

float
det4 (float a, float b, float c, float d, float e, float f, float h, float i, float j, float k, float l, float m, float n, float o, float p, float q)
{
    //return a * (f * (l * p - m * o) - k * (h * q - i * p) + o * (h * m - i * l)) - e * (b * (l * p - m * o) - k * (c * q - d * p) + o * (c * m - d * l)) + j * (b * (h * p - i * o) - f * (c * q - d * p) + o * (c * i - d * h)) - n * (b * (h * l - i * k) - f * (c * m - d * l) + k * (c * i - d * h));
    return a * det3 (f, h, i, k, l, m, o, p, q) - e * det3 (b, c, d, k, l, m, o, p, q) + j * det3 (b, c, d, f, h, i, o, p, q) - n * det3 (b, c, d, f, h, i, k, l, m);

}

int
signedVolume (float a[3], float b[3], float c[3], float d[3])
{
    return det4 (a[0], a[1], a[2], 1, b[0], b[1], b[2], 1, c[0], c[1], c[2], 1, d[0], d[1], d[2], 1) / 6;
}

enum
{
    VERTEX,
    EDGE_AC,
    EDGE_BC,
    EDGE_AB,
    IN,
    OUT
};

int
testIntersection (float ro[3], float re[3], float a[3], float b[3], float c[3])
{
    int i = signedVolume (ro, re, a, c);
    int j = signedVolume (ro, re, b, c);
    int k = signedVolume (ro, re, a, b);

    if (((i == 0) && (j == 0)) || ((i == 0) && (k == 0)) || ((j == 0) && (k == 0)))
	return VERTEX;
    if ((i == 0) && (i == k))
	return EDGE_AC;
    if ((j == 0) && (i == k))
	return EDGE_BC;
    if ((k == 0) && (i == j))
	return EDGE_AB;
    if ((i == j) && (j == k))
	return IN;
    return OUT;
}
#endif
/***** Physics stuff ******************************************************/

void
physics_init ()
{
    return;
}

float up[3] = {0, 1, 0};
float bvel[3], *bpos;
float nearestdist, nearestnorm[3], n[3];
int nearesttype;
game_t *game;

float
dist (float p0[3], float p1[3])
{
    float w[3], a[3], d;

    subtract (w, p0, p1);
    normalize (n, cross (a, w, up));
    d = dot (subtract (a, p0, bpos), n) - game->ball->radius;
    if (d <= 0 || d > nearestdist)
	return -1.0;
    nearestdist = d;
    memcpy (nearestnorm, n, sizeof (float) * 3);
    return nearestdist;
}

void
physdist (struct map_tri *m)
{
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
    float dt;
#if 0
    float ballvelleft = magnitude (g->ball[0].vel) * timer_delta ();
#endif

    dt = timer_delta ();

    game = g;

    memcpy (bvel, g->ball[0].vel, sizeof (float) * 3);

    /*
     * keep the paddles on the grid
     */
    for (i = 0; i <= 1; ++i)
	if (fabs (g->player[i].X) > 3)
	    g->player[i].X = sign (g->player[i].X) * 3;

    bpos = g->ball->pos;
#if 0
    do
    {
	nearestdist = 999999.9;	/* effectively infinity... */
	map_map_tri (physdist);
	//printf ("(ballvelleft) %.2f  (nearestdist) %.2f  (pos) %.2f %.2f %.2f  (vel) %.2f %.2f %.2f\n", ballvelleft, nearestdist, bpos[0], bpos[1], bpos[2], bvel[0], bvel[1], bvel[2]);
	switch (nearesttype)
	{
	case MAP_WALL:
	    {
		float t[3], a[3];

		scale (t, normalize (a, bvel), clamp (0.0, 9999, nearestdist));
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
#endif

    /*
     * TODO remove this hack, use 'real' cd
     */
#define WALL 3.95
    if (fabs (g->ball[0].pos[0]) > WALL)
    {
	g->ball[0].pos[0] = 3.945 * sign (g->ball[0].vel[0]);
	g->ball[0].vel[0] *= -1;
	sound_play (SOUND_BOINK, NULL, NULL, NULL);
    }
#undef WALL

    /*
     * paddle bounce
     */
#if 0
    //printf ("%f seconds\n", timer_delta ());
#endif
#define PADDLEHALFWIDTH 1.0
    i = sign (g->ball[0].vel[1]) < 0 ? 1 : 0;	/* select player in risk */
    if (fabs (g->ball[0].pos[1]) <= 8.0
	&& fabs (g->ball[0].pos[1] + g->ball[0].vel[1] * timer_delta ()) >=
	8.0)
    {
	if (fabs (g->player[i].X - g->ball[0].pos[0]) <= PADDLEHALFWIDTH)
	{
	    g->ball[0].pos[1] = 7.845 * sign (g->ball[0].vel[1]);
	    g->ball[0].vel[1] *=
		VELAMP * -cos (g->player[i].X - g->ball[0].pos[0]);
	    g->ball[0].vel[0] +=
		VELAMP * -sin (g->player[i].X - g->ball[0].pos[0]);
	    sound_play (SOUND_BOINK, NULL, NULL, NULL);
	}
    }
#undef PADDLEHALFWIDTH

#if 0
GOAL:
#endif

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
    g->ball[0].pos[0] += g->ball[0].vel[0] * timer_delta ();
    g->ball[0].pos[1] += g->ball[0].vel[1] * timer_delta ();

    return;
}
