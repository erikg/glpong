#ifndef __VIDEO_H_
#define __VIDEO_H_

#include "game.h"

void video_init ();
void video_do (game_t * g);
void video_screenshot ();
unsigned int video_load_texture (char *file, unsigned int *texid);


#endif
