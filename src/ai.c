
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
 * $Id: ai.c,v 1.5 2003/06/23 22:46:51 erik Exp $ 
 */

#include <stdlib.h>
#include "game.h"
#include "ai.h"
#include "timer.h"

void
ai_do (game_t * g)
{
    /*
     * don't act if the ball is going towards hoomon 
     */
    if (g->ballJ > 0)
	return;

    if (g->machineX > g->ballX)
	g->machineX -= timer_delta () * 4.0;
    if (g->machineX < g->ballX)
	g->machineX += timer_delta () * 4.0;
    return;
}
