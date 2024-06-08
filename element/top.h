#ifndef Top_H_INCLUDED
#define Top_H_INCLUDED

#include "../shapes/Rectangle.h"
#include "element.h"
#include "../scene/gamescene.h"

typedef struct Top {
    float x, y, w, h;
    ALLEGRO_COLOR c;
    Shape *hitbox;
} Top;

Elements *New_Top(int label);
void Top_update(Elements *const ele);
void Top_draw(Elements *const ele);
void Top_destroy(Elements *const ele);
void Top_interact(Elements *self, Elements *tar);

#endif
