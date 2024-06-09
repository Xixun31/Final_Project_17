#include "nball.h"
#include "../shapes/Circle.h"
#include "../shapes/Shape.h"
#include "../global.h"
#include "paddle.h"
#include <allegro5/allegro_primitives.h>

double last_click_time_box = 0, last_click_time_paddle = 0;
const double CLICK_DELAY_PADDLE = 0.07, CLICK_DELAY_BOX = 0.01; // 0.5秒的延遲

Elements *New_Nball(int label) {
    Nball *pDerivedObj = (Nball *)malloc(sizeof(Nball));
    Elements *pObj = New_Elements(label);

    // Initialize ball properties
    pDerivedObj->x = rand() % WIDTH;
    pDerivedObj->y = HEIGHT * 4 / 5 + (rand() % (HEIGHT / 5)) - 70;
    pDerivedObj->r = 10;
    switch (level)
    {
    case 0:
        pDerivedObj->dx = 5;
        pDerivedObj->dy = -5;
        break;
    case 1:
        pDerivedObj->dx = 7.5;
        pDerivedObj->dy = -7.5;
        break;
    case 2:
        pDerivedObj->dx = 10;
        pDerivedObj->dy = -10;
        break;
    default:
        break;
    }
    
    pDerivedObj->c = al_map_rgb(255, 0, 0);
    pDerivedObj->hitbox = New_Circle(pDerivedObj->x, pDerivedObj->y, pDerivedObj->r);

    pObj->inter_obj[pObj->inter_len++] = Paddle_L;
    pObj->inter_obj[pObj->inter_len++] = Box_L;

    ALLEGRO_SAMPLE *sample = al_load_sample("assets/sound/bounce.wav");
    pDerivedObj->bounce_Sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(pDerivedObj->bounce_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(pDerivedObj->bounce_Sound, al_get_default_mixer());
    pDerivedObj->state = 0;

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
        // if(Obj->dx > 0) Obj->dx += 0.3;
        // else Obj->dx -= 0.3;
        Obj->dx *= -1;
    }
    if (Obj->y - Obj->r < 85) {
        // if(Obj->dy > 0) Obj->dy += 0.3;
        // else Obj->dy -= 0.3;
        Obj->dy *= -1;
    }
    if (Obj->y + Obj->r > HEIGHT){
        ele->dele = true;
    }
    // Update ball position
    Obj->x += Obj->dx;
    Obj->y += Obj->dy;

    // Update hitbox position
    Shape *hitbox = Obj->hitbox;
    hitbox->update_center_x(hitbox, Obj->dx);
    hitbox->update_center_y(hitbox, Obj->dy);
}

void Nball_interact(Elements *const self, Elements *const ele) {
    Nball *Obj = ((Nball *)(self->pDerivedObj));
    double current_time = al_get_time();
    
    if (current_time - last_click_time_paddle > CLICK_DELAY_PADDLE){
        if (ele->label == Paddle_L)
        {
            Paddle *pad = ((Paddle *)(ele->pDerivedObj));
            if (pad->hitbox->overlap(pad->hitbox, Obj->hitbox))
            {
                al_play_sample_instance(Obj->bounce_Sound);
                Obj->dy *= -1;
                last_click_time_paddle = current_time;
            }
        }
    }
    if (current_time - last_click_time_box > CLICK_DELAY_BOX){
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
                last_click_time_box = current_time;
            }else if (boxr && boyl)
            {
                if(Obj->dx < 0) Obj->dx *= -1;
                if(Obj->dy < 0) Obj->dy *= -1;
                last_click_time_box = current_time;
            }else if (boyr && boxl)
            {
                if(Obj->dx > 0) Obj->dx *= -1;
                if(Obj->dy > 0) Obj->dy *= -1;
                last_click_time_box = current_time;
            }else if (boyr && boxr)
            {
                if(Obj->dx < 0) Obj->dx *= -1;
                if(Obj->dy > 0) Obj->dy *= -1;
                last_click_time_box = current_time;
            }else if (boxr || boxl)
            {
                Obj->dx *= -1;
                last_click_time_box = current_time;
            }else if(boyr || boyl)
            {
                Obj->dy *= -1;
                last_click_time_box = current_time;
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
    al_destroy_sample_instance(Obj->bounce_Sound);
    free(Obj->hitbox);
    free(Obj);
    free(ele);
}

