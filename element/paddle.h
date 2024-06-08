#ifndef PADDLE_H_INCLUDED
#define PADDLE_H_INCLUDED

#include "../shapes/Rectangle.h"
#include "element.h"
#include "../scene/gamescene.h"

typedef struct Paddle {
    float x, y, w, h;
    ALLEGRO_COLOR c;
    Shape *hitbox;
} Paddle;

Elements *New_Paddle(int label);
void Paddle_update(Elements *const ele);
void Paddle_draw(Elements *const ele);
void Paddle_destroy(Elements *const ele);
void _Paddle_update_position(Elements *self, int dx);
void Paddle_interact(Elements *self, Elements *tar);

#endif
