#include <SDL.h>

#include "input.h"
#include "game.h"
#include "timer.h"

static char state[SDLK_LAST];

void
input_init (game_t * g)
{
	memset(state,0,SDLK_LAST);
    return;
}

int
input_do (game_t * g)
{
    static SDL_Event ev;

    if (SDL_PollEvent (&ev) != 0)
	switch (ev.type)
	{
	case SDL_KEYDOWN:
	    if (ev.key.keysym.sym == 27)
		return 0;
	    else if (ev.key.keysym.sym == SDLK_F10)
		video_screenshot ();
	    else
		state[ev.key.keysym.sym] = 1;
	    break;

	case SDL_KEYUP:
	    state[ev.key.keysym.sym] = 0;
	    break;
	default:
	}
    if (state[SDLK_RIGHT])
	g->playerX += 4.0 * timer_delta ();
    if (state[SDLK_LEFT])
	g->playerX -= 4.0 * timer_delta ();
    return 1;
}
