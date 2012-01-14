
/*****************************************************************************
 * glpong - opengl/sdl game of the original video game; pong.                *
 * Copyright (C) 2001-2010 Erik Greenwald <erik@brlcad.org>                   *
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
 * $Id: sound.c,v 1.28 2010/01/06 01:06:00 erik Exp $ 
 */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#ifdef HAVE_SOUND

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifdef __APPLE__
# include <OpenAL/al.h>
# include <OpenAL/alc.h>
#else
# include <AL/al.h>
# include <AL/alc.h>
#endif

#include <SDL.h>
#include <SDL_audio.h>
#include <SDL_endian.h>

#include "sound.h"

static ALuint wave[2];
static ALuint source;

void
sound_load (ALuint id, char *name)
{
    char filename[BUFSIZ];
    Uint32 len = 0, i;
    Uint8 *buf = NULL;
    SDL_AudioSpec spec, *spec2;

    memset (&spec, 0, sizeof (spec));
    spec.format = AUDIO_S16MSB;
    spec.channels = 1;

    snprintf (filename, BUFSIZ, "%s/%s", DATADIR, name);
    if ((spec2 = SDL_LoadWAV (filename, &spec, &buf, &len)) == NULL) {
	printf ("Unable to load sound %s\n", filename);
	return;
    }
    for (i = 0; i < len / 2; ++i)
	buf[i] = SDL_SwapLE16 (buf[i]);
    alBufferData (id, AL_FORMAT_MONO16, (Uint16 *)buf, len, spec2->freq);
    free (buf);
    return;
}

static void *context_id;
static ALCdevice *dev;
static int have_al = 0;

void
sound_init ()
{
    if (have_al)
	return;
    if ((dev = alcOpenDevice (NULL)) == NULL)
	return;
    if ((context_id = alcCreateContext (dev, NULL)) == NULL)
    {
	alcCloseDevice (dev);
	have_al = 0;
	return;
    }
    alcMakeContextCurrent (context_id);

    alGenSources (1, &source);

    alGenBuffers (2, wave);
    sound_load (wave[SOUND_BOINK], "/boink.wav");
    sound_load (wave[SOUND_NNGNGNG], "/lose.wav");

    alDistanceModel (AL_DISTANCE_MODEL);
    alSourcef (source, AL_REFERENCE_DISTANCE, 22.0);

    have_al = 1;
    return;
}

void
sound_close ()
{
    if (have_al)
    {
	alcDestroyContext (context_id);
	alcCloseDevice (dev);
    }
    return;
}

void
sound_play (int sound, float *noisepos, float *playerpos, float *playeror)
{
    ALfloat back[] = { 0, 0, -1, 0, 1, 0 };
    ALfloat fwd[] = { 0, 0, 1, 0, 1, 0 };
    ALfloat sourcepos[] = { 0, 0, 1 };
    ALfloat zero[] = { 0, 0, 0, 0 };

    alListenerfv (AL_VELOCITY, zero);
    alListenerfv (AL_POSITION, playerpos ? playerpos : zero);
    alListenerfv (AL_ORIENTATION, playeror ? playeror : fwd);

    alSourcefv (source, AL_ORIENTATION, back);
    alSourcefv (source, AL_POSITION, noisepos ? noisepos : sourcepos);
    alSourcefv (source, AL_VELOCITY, zero);
    alSourcei (source, AL_BUFFER, wave[sound]);
    alSourcei (source, AL_GAIN, 1);
    alSourcei (source, AL_LOOPING, 0);
    alSourcePlay (source);
    return;
}

#else

void
sound_init ()
{
    return;
}

void
sound_close ()
{
    return;
}

void
sound_play (int sound, float *noisepos, float *playerpos, float *playeror)
{
    return;
}

#endif
