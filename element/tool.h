#ifndef Tool_H
#define Tool_H

#include "../shapes/Circle.h"
#include "element.h"
#include "../scene/gamescene.h"

typedef struct Tool {
    float x, y, r, dy;
    ALLEGRO_COLOR c;
    Shape *hitbox;
} Tool;

Elements *New_Tool(int label, float x, float y);
void Tool_update(Elements *const ele);
void Tool_interact(Elements *const self, Elements *const ele);
void Tool_draw(Elements *const ele);
void Tool_destroy(Elements *const ele);

#endif