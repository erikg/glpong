#ifndef __TEXT_H_
#define __TEXT_H_

#define TEXT_HUMAN 10
#define TEXT_MACHINE 11
#define TEXT_FPS 12

void text_init ();
void text_draw_static (int id, float x, float y, float w, float h);
void text_draw_string (char *string, float x, float y, float w, float h);
void text_destroy ();

#endif
