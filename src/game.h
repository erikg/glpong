#ifndef __GAME_H_
#define __GAME_H_

typedef struct game_s {
    float playerX;
    float machineX;
    float ballX, ballY;
    float ballI, ballJ;
    int playerscore, machinescore;
} game_t;

game_t *game_init ();
void game_newball (game_t * g);

#endif
