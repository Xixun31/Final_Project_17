#ifndef ABOUT_H_INCLUDED
#define ABOUT_H_INCLUDED
#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
/*
   [About object]
*/
typedef struct _About
{
    ALLEGRO_FONT *font1;
    ALLEGRO_FONT *font2;
    ALLEGRO_SAMPLE *song;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;
    ALLEGRO_BITMAP *tool_images[4];
    int title_x, title_y;
    bool mouse_over_back;
} About;
Scene *New_About(int label);
void about_update(Scene *self);
void about_draw(Scene *self);
void about_destroy(Scene *self);

#endif