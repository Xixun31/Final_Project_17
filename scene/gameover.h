#ifndef GAMEOVER_H_INCLUDED
#define GAMEOVER_H_INCLUDED
#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "../algif5/src/algif.h"
/*
   [GAMEOVER object]
*/
typedef struct _Gameover
{
    ALLEGRO_FONT *font1;
    ALLEGRO_FONT *font2;
    ALLEGRO_SAMPLE *song;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;
    int title_x, title_y;
    bool mouse_over_restart, mouse_over_menu;
    ALGIF_ANIMATION *gif_status;
    ALLEGRO_BITMAP *background;
    int state;
    char score_str[4];

} Gameover;
Scene *New_Gameover(int label);
void gameover_update(Scene *self);
void gameover_draw(Scene *self);
void gameover_destroy(Scene *self);

#endif