#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED
#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
/*
   [Level object]
*/
typedef struct _Level
{
    ALLEGRO_FONT *font1;
    ALLEGRO_FONT *font2;
    ALLEGRO_SAMPLE *song;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;
    int title_x, title_y;
    bool mouse_over_easy, mouse_over_medium, mouse_over_hard;
} Level;
Scene *New_Level(int label);
void level_update(Scene *self);
void level_draw(Scene *self);
void level_destroy(Scene *self);

#endif