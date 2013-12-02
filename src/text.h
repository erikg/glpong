
/*****************************************************************************
 * glpong - opengl/sdl game of the original video game; pong.                *
 * Copyright (C) 2001-2013 Erik Greenwald <erik@elfga.com>                   *
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

#ifndef __TEXT_H_
#define __TEXT_H_

#define TEXT_HUMAN 10
#define TEXT_MACHINE 11
#define TEXT_FPS 12

void text_destroy ();
void text_draw_static (int id, int x, int y, int w, int h);
void text_draw_static_ca (int id, int x, int y, int w, int h);
void text_draw_string (char *string, int x, int y, int w, int h);
void text_draw_string_ca (char *string, int x, int y, int w, int h);
void text_init ();
void text_mode (int w, int h);

#endif
