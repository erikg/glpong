#include <SDL_timer.h>
#include "timer.h"

static double nowtime = 0, thentime = 0, deltatime = 0, fps = 0, fpstime = 0;
static int frames = 0;

void
timer_init ()
{
    nowtime = SDL_GetTicks ();
    timer_update ();
    return;
}

void
timer_update ()
{
    thentime = nowtime;
    nowtime = (double)SDL_GetTicks ();
    deltatime = (nowtime - thentime) / 1000;
    frames++;
    if (nowtime - fpstime > 500)
    {
	fps = 1000 * frames / (nowtime - fpstime);
	frames = 0;
	fpstime = nowtime;
    }
    return;
}

double
timer_delta ()
{
    return deltatime;
}

double
timer_fps ()
{
    return fps;
}
