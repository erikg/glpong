#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

#include "ai.h"
#include "game.h"
#include "input.h"
#include "physics.h"
#include "sound.h"
#include "text.h"
#include "timer.h"
#include "video.h"

int
main (int argc, char **argv)
{
    game_t *g;

    if(argc>1)printf("%s: I don't do parms yet\n", argv[0]);

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

    input_init ();
    physics_init ();
    text_init ();
    timer_init ();
	sound_init();
    video_init ();

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
