#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>
#include <GL/gl.h>

#include "game.h"
#include "text.h"
#include "timer.h"
#include "video.h"

GLfloat light_position[] = { -2, 5.0, 6, 0.0 };
char buf[1024];
GLuint refl;

void
draw_paddle (int reflective, float x)
{
    /*
     * range of x is [-3,3] 
     */
    float left, right;

    left = 0.0833333333333333*x+.25;
    right = 0.0833333333333333*x+.75;
    if (reflective)
    {
	glEnable (GL_TEXTURE_2D);
    }
    glBindTexture (GL_TEXTURE_2D, refl);
    glBegin (GL_QUADS);
    glTexCoord2d (left, 1);
    glNormal3f (-.1, -.1, 1);
    glVertex3f (-1, -.3, .1);
    glTexCoord2d (left, 0);
    glNormal3f (-.1, .1, 1);
    glVertex3f (-1, .3, .1);
    glTexCoord2d (right, 0);
    glNormal3f (.1, .1, 1);
    glVertex3f (1, .3, .1);
    glTexCoord2d (right, 1);
    glNormal3f (.1, -.1, 1);
    glVertex3f (1, -.3, .1);
    glEnd ();
    glDisable (GL_TEXTURE_2D);

    glBegin (GL_QUADS);
    glNormal3f (-.1, 1, -.1);
    glVertex3f (-1, .3, -.1);
    glNormal3f (-.1, 1, .1);
    glVertex3f (-1, .3, .1);
    glNormal3f (.1, 1, .1);
    glVertex3f (1, .3, .1);
    glNormal3f (.1, 1, -.1);
    glVertex3f (1, .3, -.1);

    glNormal3f (1, 0, 0);
    glVertex3f (1, -.3, -.1);
    glVertex3f (1, -.3, .1);
    glVertex3f (1, .3, .1);
    glVertex3f (1, .3, -.1);

    glNormal3f (-1, 0, 0);
    glVertex3f (-1, -.3, -.1);
    glVertex3f (-1, -.3, .1);
    glVertex3f (-1, .3, .1);
    glVertex3f (-1, .3, -.1);
    glEnd ();
    return;
}

static void
reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glFrustum (-w / h, w / h, -1, 1, 1.5, 33);
    glMatrixMode (GL_MODELVIEW);
    return;
}

unsigned int
video_load_texture (char *file, unsigned int *texid)
{
  SDL_Surface *t = NULL;
  char buf[BUFSIZ];

  glEnable (GL_TEXTURE_2D);
  glGenTextures (1, texid);

  snprintf(buf,BUFSIZ,"%s/%s",DATADIR,file);
  printf("trying %s\n", buf);
  t = IMG_Load (buf);

  if (t == NULL)
  {
	  snprintf(buf,BUFSIZ,"../data/%s",file);
	  printf("trying %s\n", buf);
	  t = IMG_Load (buf);
  }
  if (t == NULL)
  {
	  snprintf(buf,BUFSIZ,"data/%s",file);
	  printf("trying %s\n", buf);
	  t = IMG_Load (buf);
  }
  if (t == NULL)
  {
	  fprintf(stderr, "Cannot load texture: %s\nAborting...\n", file);
	  SDL_Quit();
	  exit(-1);
  }
  glBindTexture (GL_TEXTURE_2D, *texid);
  glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, t->w, t->h, 0,
		(t->format->BytesPerPixel == 3) ? GL_RGB : GL_RGBA,
		GL_UNSIGNED_BYTE, t->pixels);
  SDL_FreeSurface (t);
  return *texid;
}

static void
form_reflmap ()
{
  video_load_texture ("refl.png", &refl);
  glTexGeni (GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
  glTexGeni (GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  return;
}

void
video_init ()
{
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat light_ambient[] = { 0, 0, 0, 0 };

    form_reflmap ();

    glShadeModel (GL_SMOOTH);
    glMaterialfv (GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv (GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv (GL_LIGHT1, GL_AMBIENT, light_ambient);

    glEnable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
    glEnable (GL_DEPTH_TEST);

    reshape (640, 480);
    return;
}

int angle = 0;

void
video_do (game_t * g)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity ();

    glTranslatef (0, 0, -15);
    glPushMatrix ();
    glRotatef (20, 1, 0, 0);

    glLightfv (GL_LIGHT0, GL_POSITION, light_position);

    /*
     * machine paddle 
     */
    glColor3f (0, 0, 1);
    glPushMatrix ();
    glTranslatef (g->machineX, 0, -8);
    draw_paddle (1, g->machineX);
    glPopMatrix ();

    /*
     * human paddle 
     */
    glColor3f (1, 1, 0);
    glPushMatrix ();
    glTranslatef (g->playerX, 0, 8);
    draw_paddle (0, g->playerX);
    glPopMatrix ();

    /*
     * ball 
     */
    glDisable (GL_LIGHTING);
    glPushMatrix ();
    glTranslatef (g->ballX, 0, g->ballY);
    glColor3f (1, 1, 1);
    glBegin (GL_QUADS);
    glVertex3f (-.1, -.3, -.1);
    glVertex3f (-.1, -.2, -.1);
    glVertex3f (.1, -.2, -.1);
    glVertex3f (.1, -.3, -.1);
    glEnd ();
    glPopMatrix ();

    /*
     * strips 
     */
    glColor3f (1, 0, 0);
    glBegin (GL_QUADS);
    glVertex3f (4.2, -.3, -9);
    glVertex3f (4.2, -.3, 9);
    glVertex3f (4.0, -.3, 9);
    glVertex3f (4.0, -.3, -9);

    glVertex3f (-4.2, -.3, -9);
    glVertex3f (-4.2, -.3, 9);
    glVertex3f (-4.0, -.3, 9);
    glVertex3f (-4.0, -.3, -9);
    glEnd ();

    /*
     * text 
     */
    glPopMatrix ();
    glColor3f (1, 1, 1);
    text_draw_static (TEXT_MACHINE, 7, 8, 2, 1);
    text_draw_static (TEXT_HUMAN, -9, 8, 2, 1);
    text_draw_static (TEXT_FPS, 0, -9, 1.2, 1);
    sprintf (buf, "% 2d", g->machinescore);
    text_draw_string (buf, 7, 7, 2, 1);
    sprintf (buf, "% 2d", g->playerscore);
    text_draw_string (buf, -9, 7, 2, 1);
    sprintf (buf, "% .0f", timer_fps ());
    text_draw_string (buf, -2, -9, 1.2, 1);
    glEnable (GL_LIGHTING);

    SDL_GL_SwapBuffers ();
    return;
}

static void
flip_surface (SDL_Surface * s)
{
    int x;
    Uint8 *buf;
    buf = (Uint8 *)malloc(s->pitch);

    for (x = 0; x < (480 / 2); x++)
    {
	memcpy (buf, (Uint8 *) (s->pixels + x * s->pitch), s->pitch);
	memcpy ((Uint8 *) (s->pixels + x * s->pitch),
	    (Uint8 *) (s->pixels + (479 - x) * s->pitch), s->pitch);
	memcpy ((Uint8 *) (s->pixels + (479 - x) * s->pitch), buf, s->pitch);
    }
    return;
}

void
video_screenshot ()
{
    SDL_Surface *ss;

    ss = SDL_CreateRGBSurface (0, 640, 480, 24, 0, 0, 0, 0);
    glReadPixels (0, 0, 640, 480, GL_BGR, GL_UNSIGNED_BYTE, ss->pixels);
    flip_surface (ss);
    SDL_SaveBMP (ss, "screenshot.bmp");
    return;
}
