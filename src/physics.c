#include <stdio.h>
#include <math.h>
#include "game.h"
#include "physics.h"
#include "sound.h"
#include "timer.h"

int
sign (float x)
{
    if (x > 0)
	return 1;
    if (x < 0)
	return -1;
    return 0;
}

void
physics_init (game_t * g)
{
    return;
}

void
physics_do (game_t * g)
{
    if (fabs (g->ballX) > 4.0 && (sign (g->ballX) == sign (g->ballI)))
	g->ballI *= -1;

    if (g->machineX > 3)
	g->machineX = 3;
    if (g->machineX < -3)
	g->machineX = -3;
    if (g->playerX > 3)
	g->playerX = 3;
    if (g->playerX < -3)
	g->playerX = -3;

    if (g->ballY > 8.0 && g->ballJ > 0)
    {
	if (fabs (g->playerX - g->ballX) > 1.0)
	{
	    g->machinescore++;
	    game_newball (g);
	    sound_play (SOUND_NNGNGNG);

	} else
	{
	    g->ballI += 2.0 * -sin ((g->playerX - g->ballX));
	    g->ballJ *= 2.0 * -cos (1 * (g->playerX - g->ballX));
	    sound_play (SOUND_BOINK);
	}
    }

    if (g->ballY < -8.0 && g->ballJ < 0)
    {
	if (fabs (g->machineX - g->ballX) > 1.0)
	{
	    g->playerscore++;
	    game_newball (g);
	    sound_play (SOUND_NNGNGNG);
	} else
	{
	    g->ballI += 2.0 * -sin ((g->machineX - g->ballX));
	    g->ballJ *= -2.0 * cos (1 * (g->machineX - g->ballX));
	    sound_play (SOUND_BOINK);
	}
    }

    if(fabs(g->ballJ)<.3)
	if(g->ballJ<0)g->ballJ=-.3;
	else
		g->ballJ=.3;

    if(g->ballJ>100)g->ballJ=100;
    if(g->ballJ<-100)g->ballJ=-100;

    g->ballX += g->ballI * timer_delta ();
    g->ballY += g->ballJ * timer_delta ();
    return;
}
