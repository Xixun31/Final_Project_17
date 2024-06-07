#include "paddle.h"
#include "../shapes/Rectangle.h"
#include "../shapes/Shape.h"
#include "../global.h"
#include <allegro5/allegro_primitives.h>



Elements *New_Paddle(int label) {
    Paddle *pDerivedObj = (Paddle *)malloc(sizeof(Paddle));
    Elements *pObj = New_Elements(label);

    // Initialize paddle properties
    pDerivedObj->x = WIDTH / 2 - 100;
    pDerivedObj->y = HEIGHT - 100;
    pDerivedObj->w = 200;
    pDerivedObj->h = 10;
    pDerivedObj->c = al_map_rgb(205, 205, 205);
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x, pDerivedObj->y, pDerivedObj->x + pDerivedObj->w,
                                        pDerivedObj->y + pDerivedObj->h);

    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Paddle_update;
    pObj->Draw = Paddle_draw;
    pObj->Destroy = Paddle_destroy;

    return pObj;
}

void Paddle_update(Elements *const ele) {
    Paddle *Obj = ((Paddle *)(ele->pDerivedObj));

    

    // Move paddle based on keyboard input
    if (key_state[ALLEGRO_KEY_LEFT] && Obj->x> 0) {
        _Paddle_update_position(ele, -10);
    }
    if (key_state[ALLEGRO_KEY_RIGHT] && Obj->x + Obj->w < WIDTH) {
        _Paddle_update_position(ele, 10);
    }
}

void Paddle_draw(Elements *const ele) {
    Paddle *Obj = ((Paddle *)(ele->pDerivedObj));
    al_draw_filled_rectangle(Obj->x, Obj->y, Obj->x + Obj->w, Obj->y + Obj->h, Obj->c);
}

void Paddle_destroy(Elements *const ele) {
    Paddle *Obj = ((Paddle *)(ele->pDerivedObj));
    free(Obj->hitbox);
    free(Obj);
    free(ele);
}

void _Paddle_update_position(Elements *self, int dx)
{
    Paddle *paddle = ((Paddle *)(self->pDerivedObj));
    paddle->x += dx;
    Shape *hitbox = paddle->hitbox;
    hitbox->update_center_x(hitbox, dx);
}
