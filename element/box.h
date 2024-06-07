#ifndef Box_H_INCLUDED
#define Box_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [Box object]
*/
typedef struct _Box
{
    float x, y, w, h;
    ALLEGRO_COLOR c;
    Shape *hitbox;
    Shape *hitboxr;
    Shape *hitboy;
    Shape *hitboyr;
} Box;
Elements *New_Box(int label);
void Box_update(Elements *self);
void Box_interact(Elements *self, Elements *tar);
void Box_draw(Elements *self);
void Box_destory(Elements *self);

#endif
