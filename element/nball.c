#include "nball.h"
#include "../shapes/Circle.h"
#include "../shapes/Shape.h"
#include "../global.h"
#include "paddle.h"
#include <allegro5/allegro_primitives.h>
#include "../scene/sceneManager.h"

Elements *New_Nball(int label) {
    Nball *pDerivedObj = (Nball *)malloc(sizeof(Nball));
    Elements *pObj = New_Elements(label);

    // Initialize ball properties
    pDerivedObj->x = rand() % WIDTH;
    pDerivedObj->y = HEIGHT * 4 / 5 + (rand() % (HEIGHT / 5)) - 70;
    pDerivedObj->r = 10;
    pDerivedObj->last = 0;
    pDerivedObj->delayb = 0.01;
    pDerivedObj->delayp = 0.2;
    ball_exist++;
    pDerivedObj->dx = 5;
    pDerivedObj->dy = -5;
    
    pDerivedObj->c = al_map_rgb(255, 0, 0);
    pDerivedObj->hitbox = New_Circle(pDerivedObj->x, pDerivedObj->y, pDerivedObj->r);

    pObj->inter_obj[pObj->inter_len++] = Paddle_L;
    pObj->inter_obj[pObj->inter_len++] = Box_L;

    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Nball_update;
    pObj->Interact = Nball_interact;
    pObj->Draw = Nball_draw;
    pObj->Destroy = Nball_destroy;

    return pObj;
}

void Nball_update(Elements *const ele) {
    Nball *Obj = ((Nball *)(ele->pDerivedObj));
    // Check for collision with screen borders
    if (Obj->x - Obj->r < 0 || Obj->x + Obj->r > WIDTH) {
        Obj->dx *= -1;
    }
    if (Obj->y - Obj->r < 85) {
        Obj->dy *= -1;
    }
    if(UNDEAD){
        if (Obj->y + Obj->r > HEIGHT - 100){
            Obj->dy *= -1;
        }
    }else{
        if (Obj->y + Obj->r > HEIGHT){
        ele->dele = true;
        ball_exist--;
        }
    }
    // Update ball position
    Obj->x += Obj->dx;
    Obj->y += Obj->dy;

    // Update hitbox position
    Shape *hitbox = Obj->hitbox;
    hitbox->update_center_x(hitbox, Obj->dx);
    hitbox->update_center_y(hitbox, Obj->dy);
    if(ball_exist == 0) life(scene, -3);
    if(GAME_LOSE || GAME_WIN){
        ele->dele = true;
    }
}

void Nball_interact(Elements *const self, Elements *const ele) {
    Nball *Obj = ((Nball *)(self->pDerivedObj));
    double current_time = al_get_time();
    
    if (current_time - Obj->last > Obj->delayp){
        if (ele->label == Paddle_L)
        {
            Paddle *pad = ((Paddle *)(ele->pDerivedObj));
            if (pad->hitbox->overlap(pad->hitbox, Obj->hitbox))
            {
                Obj->dy *= -1;
                Obj->last = current_time;
            }
        }
    }
    if (current_time - Obj->last > Obj->delayb){
        if(ele->label == Box_L){
            Box *box = ((Box *)(ele->pDerivedObj));
            bool boxl = box->hitbox->overlap(box->hitbox, Obj->hitbox);
            bool boxr = box->hitbox->overlap(box->hitboxr, Obj->hitbox);
            bool boyl = box->hitbox->overlap(box->hitboy, Obj->hitbox);
            bool boyr = box->hitbox->overlap(box->hitboyr, Obj->hitbox);

            if(boxl && boyl)
            {
                if(Obj->dx > 0) Obj->dx *= -1;
                if(Obj->dy < 0) Obj->dy *= -1;
                Obj->last = current_time;
            }else if (boxr && boyl)
            {
                if(Obj->dx < 0) Obj->dx *= -1;
                if(Obj->dy < 0) Obj->dy *= -1;
                Obj->last = current_time;
            }else if (boyr && boxl)
            {
                if(Obj->dx > 0) Obj->dx *= -1;
                if(Obj->dy > 0) Obj->dy *= -1;
                Obj->last = current_time;
            }else if (boyr && boxr)
            {
                if(Obj->dx < 0) Obj->dx *= -1;
                if(Obj->dy > 0) Obj->dy *= -1;
                Obj->last = current_time;
            }else if (boxr || boxl)
            {
                Obj->dx *= -1;
                Obj->last = current_time;
            }else if(boyr || boyl)
            {
                Obj->dy *= -1;
                Obj->last = current_time;
            }
        }
    }
}

void Nball_draw(Elements *const ele) {
    Nball *Obj = ((Nball *)(ele->pDerivedObj));
    al_draw_filled_circle(Obj->x, Obj->y, Obj->r, Obj->c);
}

void Nball_destroy(Elements *const ele) {
    Nball *Obj = ((Nball *)(ele->pDerivedObj));
    free(Obj->hitbox);
    free(Obj);
    free(ele);
}

