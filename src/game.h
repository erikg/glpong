
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
 * $Id: game.h,v 1.10 2003/07/29 15:38:14 erik Exp $ 
 */

#ifndef __GAME_H_
#define __GAME_H_

typedef struct ball_s
{
    float pos[3], vel[3];
    float radius, speed;
}
ball_t;

typedef struct player_s
{
    float X;
    int score;
}
player_t;

#define PLAYER 0
#define MACHINE 1

typedef struct game_s
{
    player_t player[2];
    ball_t ball[1];
}
game_t;

game_t *game_init ();
void game_newball (game_t * g);

#endif
