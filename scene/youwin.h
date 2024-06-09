#ifndef YOUWIN_H_INCLUDED
#define YOUWIN_H_INCLUDED
#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "../algif5/src/algif.h"
/*
   [YOUWIN object]
*/
typedef struct _Youwin
{
    ALLEGRO_FONT *font1;
    ALLEGRO_FONT *font2;
    ALLEGRO_SAMPLE *song;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;
    int title_x, title_y;
    bool mouse_over_restart, mouse_over_menu;
    ALGIF_ANIMATION *gif_status;
    int state;

} Youwin;
Scene *New_Youwin(int label);
void youwin_update(Scene *self);
void youwin_draw(Scene *self);
void youwin_destroy(Scene *self);

#endif