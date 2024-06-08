#include "nball.h"
#include "../shapes/Circle.h"
#include "../shapes/Shape.h"
#include "../global.h"
#include "paddle.h"
#include <allegro5/allegro_primitives.h>

double last_click_time = 0;
const double CLICK_DELAY = 0.2; // 0.5秒的延遲

Elements *New_Nball(int label) {
    Nball *pDerivedObj = (Nball *)malloc(sizeof(Nball));
    Elements *pObj = New_Elements(label);

    // Initialize ball properties
    pDerivedObj->x = WIDTH / 2;
    pDerivedObj->y = HEIGHT / 2;
    pDerivedObj->r = 10;
    switch (level)
    {
    case 0:
        pDerivedObj->dx = 5;
        pDerivedObj->dy = 5;
        break;
    case 1:
        pDerivedObj->dx = 10;
        pDerivedObj->dy = 10;
        break;
    case 2:
        pDerivedObj->dx = 15;
        pDerivedObj->dy = 15;
        break;
    default:
        break;
    }
    
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
        // if(Obj->dx > 0) Obj->dx += 0.3;
        // else Obj->dx -= 0.3;
        Obj->dx *= -1;
    }
    if (Obj->y - Obj->r < 75 || Obj->y + Obj->r > HEIGHT) {
        // if(Obj->dy > 0) Obj->dy += 0.3;
        // else Obj->dy -= 0.3;
        Obj->dy *= -1;
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

    if (current_time - last_click_time > CLICK_DELAY){
        if (ele->label == Paddle_L)
        {
            Paddle *pad = ((Paddle *)(ele->pDerivedObj));
            if (pad->hitbox->overlap(pad->hitbox, Obj->hitbox))
            {
                Obj->dy *= -1;
                last_click_time = current_time;
            }
        }else if(ele->label == Box_L){
        Box *box = ((Box *)(ele->pDerivedObj));
        if((box->hitbox->overlap(box->hitbox, Obj->hitbox) || box->hitboxr->overlap(box->hitboxr, Obj->hitbox))
        && (box->hitboy->overlap(box->hitboy, Obj->hitbox) || box->hitboyr->overlap(box->hitboyr, Obj->hitbox)))
        {
            Obj->dx *= -1;
            Obj->dy *= -1;
            last_click_time = current_time;
        }else if (box->hitbox->overlap(box->hitbox, Obj->hitbox) || box->hitboxr->overlap(box->hitboxr, Obj->hitbox))
        {
            Obj->dx *= -1;
            last_click_time = current_time;
        }else if(box->hitboy->overlap(box->hitboy, Obj->hitbox) || box->hitboyr->overlap(box->hitboyr, Obj->hitbox)){
            Obj->dy *= -1;
            last_click_time = current_time;
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
