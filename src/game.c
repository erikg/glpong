#include <stdlib.h>
#include <math.h>
#include "game.h"

game_t *
game_init ()
{
    game_t *g;

    g = (game_t *) malloc (sizeof (game_t));
    srand (time (0) + getpid ());
    g->playerX = 0;
    g->machineX = 0;
    g->playerscore = 0;
    g->machinescore = 0;
    game_newball (g);
    return g;
}

void
game_newball (game_t * g)
{
	float angle;
	do
	{
	angle = (float)rand() * (2.0*M_PI/(float)RAND_MAX);
	}
	while(cos(angle)>.8);
    g->ballX = 0;
    g->ballY = 0;
    g->ballI = 3.0 * sin(angle);
    g->ballJ = 3.0 * cos(angle);
}
