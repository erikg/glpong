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
 * $Id: sound.c,v 1.3 2003/06/19 15:03:57 erik Exp $ 
 */

#include <unistd.h>
#include <SDL_mixer.h>

#include "sound.h"

static Mix_Chunk *wave[3];

void
sound_init ()
{
    if (Mix_OpenAudio (MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
    {
	fprintf (stderr, "Couldn't open audio: %s\n", SDL_GetError ());
    }

    wave[SOUND_BOINK] = Mix_LoadWAV (DATADIR"/boink.wav");
    wave[SOUND_NNGNGNG] = Mix_LoadWAV (DATADIR"/lose.wav");

    return;
}

void
sound_play (int sound)
{
    Mix_PlayChannel (0, wave[sound], 0);
    sleep (0);
    return;
}
