#include <stdio.h>
#include <SDL.h>
#include <GL/gl.h>

#include "game.h"
#include "input.h"
#include "physics.h"
#include "video.h"


int
main (int argc, char **argv)
{
    game_t *g;

    SDL_Init (SDL_INIT_VIDEO);
    if (argc == 1)
	SDL_SetVideoMode (640, 480, 32, SDL_OPENGL | SDL_DOUBLEBUF);
    else
	SDL_SetVideoMode (640, 480, 32,
	    SDL_OPENGL | SDL_DOUBLEBUF | SDL_FULLSCREEN);
    atexit (SDL_Quit);

    SDL_ShowCursor (0);
    SDL_WM_SetCaption ("glpong (C) 2001 Erik Greenwald", "glpong");

    g = game_init ();

    ai_init (g);
    input_init (g);
    physics_init (g);
    text_init ();
    timer_init ();
	sound_init();
    video_init (g);

    while (input_do (g))
    {
	timer_update ();
	ai_do (g);
	physics_do (g);
	video_do (g);
    }
    SDL_Quit ();
    return 0;
}
