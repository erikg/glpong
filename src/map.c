
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
 * $Id: map.c,v 1.2 2003/07/19 19:20:48 erik Exp $
 */

#include <stdio.h>
#include <stdlib.h>
#include "map.h"

#define memdup(d,s) memcpy(malloc(s),d,s)

struct _ll
{
    struct _ll *next;
    void *data;
}
*map[MAP_LAST];

	/* wipes out existing map */
void
map_new ()
{
    int i;

    for (i = 0; i < MAP_LAST; ++i)
      {
	  /* memleak, need proper clearing */
	  map[i] = NULL;
      }
    return;
}

	/* adds a single triangle to the map */
int
map_add_tri (int type, float v[3][3])
{
    struct _ll *l = (struct _ll *) malloc (sizeof (struct _ll));

    if (l == NULL)
	return -1;
    l->data = memdup (v, sizeof (float) * 3 * 3);
    l->next = map[type];
    map[type] = l;
    return 0;
}

	/* apply <func> to each vertex in <type> list */
int
map_map_tri (int type, void (*func) (float v[3][3]))
{
    struct _ll *l;

    for (l = map[type]; l; l = l->next)
	func (l->data);
    return 0;
}
