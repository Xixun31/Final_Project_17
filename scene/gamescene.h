#ifndef GAMESCENE_H_INCLUDED
#define GAMESCENE_H_INCLUDED
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <time.h>
#include "scene.h"
#include "../shapes/Circle.h"
#include "../element/element.h"
#include "../element/charater.h"
#include "../element/floor.h"
#include "../element/teleport.h"
#include "../element/tree.h"
#include "../element/projectile.h"
#include "../element/paddle.h"
#include "../element/nball.h"
#include "../element/ball.h"
#include "../element/box.h"
#include "../element/tool.h"
#include "../element/top.h"

/*
   [game scene object]
*/
typedef enum EleType
{
    Floor_L,
    Teleport_L,
    Tree_L,
    Character_L,
    Projectile_L,
    Paddle_L,
    Nball_L,
    Ball_L,
    Box_L,
    Tool_L,
    Top_L
} EleType;
typedef struct _GameScene
{
    ALLEGRO_BITMAP *background;
    ALLEGRO_BITMAP *heart_image; 
    ALLEGRO_FONT *font1;
    int title_x, title_y, score, life;
    char score_show[4], bexist[4];
    ALLEGRO_SAMPLE_INSTANCE *box_sound;
    bool mouse_over_set, mouse_over_resume, mouse_over_menu, mouse_over_restart, pause, win;
    double last;
    ALLEGRO_SAMPLE *song;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;

} GameScene;
Scene *New_GameScene(int label);
void game_scene_update(Scene *self);
void game_scene_draw(Scene *self);
void game_scene_destroy(Scene *self);
void format_time(int elapsed_seconds, char *buffer, int size);
void score(Scene *self);
void life_show(Scene *self);
void life(Scene *self, int life);

#endif
