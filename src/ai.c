#include <stdlib.h>
#include "game.h"
#include "ai.h"
#include "timer.h"

void
ai_init (game_t * g)
{
    return;
}

void
ai_do (game_t * g)
{
    /*
     * don't act if the ball is going towards hoomon 
     */
    if (g->ballJ > 0)
	return;

    if (g->machineX > g->ballX)
	g->machineX -= timer_delta () * 4.0;
    if (g->machineX < g->ballX)
	g->machineX += timer_delta () * 4.0;
    return;
}
