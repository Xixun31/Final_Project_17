#include "paddle.h"
#include "../shapes/Rectangle.h"
#include "../shapes/Shape.h"
#include "../global.h"
#include <allegro5/allegro_primitives.h>
#include "../scene/sceneManager.h"

double Temporary_Time_l = 0, Temporary_Time_s = 0, Temporary_Time_r = 0;
const double Suspend_Time = 3, DELAY = 0.3;

Elements *New_Paddle(int label) {
    Paddle *pDerivedObj = (Paddle *)malloc(sizeof(Paddle));
    Elements *pObj = New_Elements(label);

    // Initialize paddle properties
    pDerivedObj->x = WIDTH / 2 - 100;
    pDerivedObj->y = HEIGHT - 50;
    pDerivedObj->w = 200;
    pDerivedObj->h = 10;
    pDerivedObj->dx = 13;
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
    if(change_r){
        Obj->keyr = key_state[ALLEGRO_KEY_LEFT];
        Obj->keyl = key_state[ALLEGRO_KEY_RIGHT];
    }else{
        Obj->keyr = key_state[ALLEGRO_KEY_RIGHT];
        Obj->keyl = key_state[ALLEGRO_KEY_LEFT];
    }

    // Move paddle based on keyboard input
    if (Obj->state == STOP_P)
    {
        if (Obj->keyl && Obj->x> 0) {
            Obj->state = MOVE_PL;
        }
        else if (Obj->keyr && Obj->x + Obj->w < WIDTH) {
            Obj->state = MOVE_PR;
        }
        else{
            Obj->state = STOP_P;
        }
    }
    else if (Obj->state == MOVE_PL)
    {
        if (Obj->keyl && Obj->x > 0) {
            _Paddle_update_position(ele, -Obj->dx);
            Obj->state = MOVE_PL;
        }
        else Obj->state = STOP_P;
    }
    else if (Obj->state == MOVE_PR)
    {
        if (Obj->keyr && Obj->x + Obj->w < WIDTH) {
            _Paddle_update_position(ele, Obj->dx);
            Obj->state = MOVE_PR;
        }
        else Obj->state = STOP_P;
    }
    if((al_get_time() > Temporary_Time_l + Suspend_Time) && change_l){
        Obj->x += 50;
        Obj->w -= 100;
        change_l --;
        Obj->hitbox = New_Rectangle(Obj->x, Obj->y, Obj->x + Obj->w, Obj->y + 1);
    }else if((al_get_time() > Temporary_Time_s + Suspend_Time) && change_s){
        Obj->x -= 50;
        Obj->w += 100;
        change_s --;
        Obj->hitbox = New_Rectangle(Obj->x, Obj->y, Obj->x + Obj->w, Obj->y + 1);
    }else if((al_get_time() > Temporary_Time_r + Suspend_Time) && change_r){
        change_r = 0;
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
        if (al_get_time() > (Temporary_Time_l + DELAY) && al_get_time() > (Temporary_Time_r + DELAY)
        && al_get_time() > (Temporary_Time_s + DELAY))
        {
            if (tl->hitbox->overlap(tl->hitbox, Obj->hitbox))
            {
                if(compare_colors(tl->c, al_map_rgb(205, 150, 50))){
                    Obj->x -= 50;
                    Obj->w += 100;
                    Temporary_Time_l = al_get_time();
                    change_l ++;
                    Obj->hitbox = New_Rectangle(Obj->x, Obj->y, Obj->x + Obj->w, Obj->y + 1);
                }else if(compare_colors(tl->c, al_map_rgb(50, 200, 100))){
                    Obj->x += 50;
                    Obj->w -= 100;
                    Temporary_Time_s = al_get_time();
                    change_s ++;
                    Obj->hitbox = New_Rectangle(Obj->x, Obj->y, Obj->x + Obj->w, Obj->y + 1);
                }else if(compare_colors(tl->c, al_map_rgb(50, 100, 200))){
                    Temporary_Time_r = al_get_time();
                    change_r = 1;
                }else if(compare_colors(tl->c, al_map_rgb(150, 0, 10)) || Obj->ball){
                    Obj->ball = false;
                    _Register_elements(scene, New_Nball(Nball_L));
                    Obj->ball = true;
                }else if(compare_colors(tl->c, al_map_rgb(255, 255, 255))){
                    life(scene, -1);
                }else if(compare_colors(tl->c, al_map_rgb(255, 100, 155))){
                    life(scene, 1);
                }
            }
        }
    }
}
int compare_colors(ALLEGRO_COLOR c1, ALLEGRO_COLOR c2) {
    return (c1.r == c2.r) && (c1.g == c2.g) && (c1.b == c2.b) && (c1.a == c2.a);
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
