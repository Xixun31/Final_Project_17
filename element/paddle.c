#include "paddle.h"
#include "../shapes/Rectangle.h"
#include "../shapes/Shape.h"
#include "../global.h"
#include <allegro5/allegro_primitives.h>

double Temporary_Time = 0;
const double Suspend_Time = 5;
int change = 0;

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

    pObj->inter_obj[pObj->inter_len++] = Tool_L;

    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Paddle_update;
    pObj->Draw = Paddle_draw;
    pObj->Destroy = Paddle_destroy;
    pObj->Interact = Paddle_interact;

    return pObj;
}

void Paddle_update(Elements *const ele) {
    Paddle *Obj = ((Paddle *)(ele->pDerivedObj));

    

    // Move paddle based on keyboard input
    if (Obj->state == STOP_P)
    {
        if (key_state[ALLEGRO_KEY_LEFT] && Obj->x> 0) {
            Obj->state = MOVE_PL;
        }
        else if (key_state[ALLEGRO_KEY_RIGHT] && Obj->x + Obj->w < WIDTH) {
            Obj->state = MOVE_PR;
        }
        else{
            Obj->state = STOP_P;
        }
    }
    else if (Obj->state == MOVE_PL)
    {
        if (key_state[ALLEGRO_KEY_LEFT] && Obj->x> 0) {
            _Paddle_update_position(ele, -10);
            Obj->state = MOVE_PL;
        }
        else Obj->state = STOP_P;
    }
    else if (Obj->state == MOVE_PR)
    {
        if (key_state[ALLEGRO_KEY_RIGHT] && Obj->x + Obj->w < WIDTH) {
            _Paddle_update_position(ele, 10);
            Obj->state = MOVE_PR;
        }
        else Obj->state = STOP_P;
    }
    if((al_get_time() > Temporary_Time + Suspend_Time) && change){
        {
            Obj->x += 50;
            Obj->w -= 100;
            change = 0;
            Obj->hitbox = New_Rectangle(Obj->x, Obj->y, Obj->x + Obj->w,Obj->y + Obj->h);
        }
    }
}
void Paddle_draw(Elements *const ele) {
    Paddle *Obj = ((Paddle *)(ele->pDerivedObj));
    al_draw_filled_rectangle(Obj->x, Obj->y, Obj->x + Obj->w, Obj->y + Obj->h, Obj->c);
}
void Paddle_interact(Elements *self, Elements *tar) {
    Paddle *Obj = ((Paddle *)(self->pDerivedObj));

    if (tar->label == Tool_L)
    {   
        Tool *tl = ((Tool *)(tar->pDerivedObj));
        if (tl->hitbox->overlap(tl->hitbox, Obj->hitbox))
        {
            Obj->x -= 50;
            Obj->w += 100;
            Temporary_Time = al_get_time();
            change = 1;
            Obj->hitbox = New_Rectangle(Obj->x, Obj->y, Obj->x + Obj->w,Obj->y + Obj->h);
        }
    }
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
