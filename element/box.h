#ifndef Box_H_INCLUDED
#define Box_H_INCLUDED

#include "../shapes/Rectangle.h"
#include "element.h"

typedef struct Box {
    float x, y, w, h;
    ALLEGRO_COLOR c;
    Shape *hitbox;
} Box;

Elements *New_Box(int label);
void Box_update(Elements *const ele);
void Box_draw(Elements *const ele);
void Box_destroy(Elements *const ele);

#endif
