#ifndef Tool_H
#define Tool_H

#include "../shapes/Circle.h"
#include "element.h"
#include "../scene/gamescene.h"
#include <allegro5/allegro.h>

typedef struct Tool {
    float x, y, r, dy;
    ALLEGRO_COLOR c;
    Shape *hitbox;
    ALLEGRO_BITMAP *image;
    ALLEGRO_SAMPLE_INSTANCE *tool_sound, *gg_sound;
    int random_choice;
} Tool;

Elements *New_Tool(int label, float x, float y);
void Tool_update(Elements *const ele);
void Tool_interact(Elements *const self, Elements *const ele);
void Tool_draw(Elements *const ele);
void Tool_destroy(Elements *const ele);

#endif
