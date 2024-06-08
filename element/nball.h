#ifndef NBALL_H
#define NBALL_H

#include "../shapes/Circle.h"
#include "element.h"
#include "../scene/gamescene.h"

typedef struct Nball {
    float x, y, r, dx, dy;
    ALLEGRO_COLOR c;
    Shape *hitbox;
    ALLEGRO_SAMPLE_INSTANCE *bounce_Sound;
    int state;
} Nball;

Elements *New_Nball(int label);
void Nball_update(Elements *const ele);
void Nball_interact(Elements *const self, Elements *const ele);
void Nball_draw(Elements *const ele);
void Nball_destroy(Elements *const ele);

#endif
