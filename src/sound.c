
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
 * $Id: sound.c,v 1.9 2003/06/28 15:48:41 erik Exp $ 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <SDL.h>
#include <SDL_audio.h>

#include "sound.h"

static ALuint wave[2];
static ALuint source;

void
sound_load (ALuint id, char *name)
{
    char filename[BUFSIZ];
    Uint32 len=0;
    Uint8 *buf=NULL;
    SDL_AudioSpec spec,*spec2;

    memset(&spec,0,sizeof(spec));
    spec.format=AUDIO_S16MSB;
    spec.channels=1;

    snprintf (filename, BUFSIZ, "%s/%s", DATADIR, name);
    if ((spec2=SDL_LoadWAV (filename, &spec, &buf, &len)) == NULL)
      {
	  printf ("Unable to load sound %s\n", filename);
	  return -1;
      }
    printf("Loaded sound %s into id %d\n", filename, id);
    printf("format: %x\nchannels: %x\nfreq: %d\n", spec2->format, spec2->channels, spec2->freq);
    alBufferData (id, AL_FORMAT_MONO16, buf, len, spec2->freq);
    free (buf);
    return;
}

void
sound_init ()
{
    static void *context_id;
    ALCdevice *dev;

    if ((dev = alcOpenDevice (NULL)) == NULL)
	return;
    if ((context_id = alcCreateContext (dev, NULL)) == NULL)
      {
	  alcCloseDevice (dev);
	  return;
      }
    alcMakeContextCurrent (context_id);

    alGenSources (1, &source);

    alGenBuffers(2,wave);
    sound_load (wave[SOUND_BOINK], "/boink.wav");
    sound_load (wave[SOUND_NNGNGNG], "/lose.wav");

    alDistanceModel (AL_DISTANCE_MODEL);
    alSourcef(source, AL_REFERENCE_DISTANCE, 22.0);

    return;
}

void
sound_play (int sound, float *noisepos, float *playerpos, float *playeror)
{
	float zero[4] = {0,0,0,0};
	float fwd[4] = {0,1,0,0};
/*
    alSourcefv (wave[sound], AL_POSITION, noisepos);
    alListenerfv (AL_POSITION, playerpos);
    alListenerfv (AL_ORIENTATION, playeror);
*/
    alSourcefv (source, AL_POSITION, zero);
    alListenerfv (AL_POSITION, zero);
    alListenerfv (AL_ORIENTATION, fwd);
    alSourcei(source, AL_BUFFER, wave[sound]);
    alSourcei(source, AL_GAIN, 1);
    alSourcei(source, AL_LOOPING, 0);
    alSourcePlay (source);
    printf("Playing %d\n", wave[sound]);
    return;
}
