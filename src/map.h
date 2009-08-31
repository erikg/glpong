
/*****************************************************************************
 * glpong - opengl/sdl game of the original video game; pong.                *
 * Copyright (C) 2001-2009 Erik Greenwald <erik@smluc.org>                   *
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
 * $Id: map.h,v 1.11 2009/08/31 16:42:16 erik Exp $
 */

#define MAP_WALL 0
#define MAP_GATE 1
#define MAP_LAST 2

struct map_tri {
    char type;			/* MAP_WALL or MAP_GATE */
    float v[3][3];		/* vertices of the tri */
};

	/*
	 * wipes out existing map 
	 */
void map_new ();

	/*
	 * adds a single triangle to the map 
	 */
int map_add_tri (int type, float v[3][3]);

	/*
	 * apply <func> to each vertex in <type> list 
	 */
int map_map_tri (void (*func) (struct map_tri *));
