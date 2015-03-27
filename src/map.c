
/*****************************************************************************
 * glpong - opengl/sdl game of the original video game; pong.                *
 * Copyright (C) 2001-2015 Erik Greenwald <erik@elfga.com>                   *
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"

struct _ll {
    struct _ll *next;
    void *data;
} *map;

	/*
	 * wipes out existing map 
	 */
void
map_new ()
{
    map = NULL;
    return;
}

	/*
	 * adds a single triangle to the map 
	 */
int
map_add_tri (int type, float v[3][3])
{
    struct _ll *l = (struct _ll *)malloc (sizeof (struct _ll));
    struct map_tri *t = (struct map_tri *)malloc (sizeof (struct map_tri));

    if (l == NULL || t == NULL)
	return -1;
    memcpy (t->v, v, sizeof (float) * 3 * 3);
    t->type = type;
    l->data = t;
    l->next = map;
    map = l;
    return 0;
}

	/*
	 * apply <func> to each vertex in <type> list 
	 */
int
map_map_tri (void (*func) (struct map_tri * t))
{
    struct _ll *l = map;

    for (; l; l = l->next)
	func (l->data);
    return 0;
}
