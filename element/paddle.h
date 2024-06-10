#ifndef PADDLE_H_INCLUDED
#define PADDLE_H_INCLUDED

#include "../shapes/Rectangle.h"
#include "element.h"
#include "../scene/gamescene.h"
typedef enum PaddleType
{
    STOP_P = 0,
    MOVE_PL,
    MOVE_PR
} PaddleType;

typedef struct Paddle {
    float x, y, w, h;
    int dx;
    ALLEGRO_COLOR c;
    ALLEGRO_BITMAP *image;
    Shape *hitbox;
    int state;
    bool keyr, keyl;
} Paddle;

Elements *New_Paddle(int label);
void Paddle_update(Elements *const ele);
void Paddle_draw(Elements *const ele);
void Paddle_destroy(Elements *const ele);
void _Paddle_update_position(Elements *self, int dx);
void Paddle_interact(Elements *self, Elements *tar);
int compare_colors(ALLEGRO_COLOR c1, ALLEGRO_COLOR c2);

#endif