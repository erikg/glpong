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
