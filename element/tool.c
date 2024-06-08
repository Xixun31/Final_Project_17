#include "tool.h"
#include "../shapes/Circle.h"
#include "../shapes/Shape.h"
#include "../global.h"
#include "paddle.h"
#include <allegro5/allegro_primitives.h>

Elements *New_Tool(int label, float x, float y) {
    Tool *pDerivedObj = (Tool *)malloc(sizeof(Tool));
    Elements *pObj = New_Elements(label);

    // Initialize ball properties
    pDerivedObj->x = x + 75/2;
    pDerivedObj->y = y + 75/ 2;
    pDerivedObj->r = 10;
    pDerivedObj->dy = 5;
    if(random() % 4 == 0){
        pDerivedObj->c = al_map_rgb(205, 150, 50);
    }else if(random() % 4 == 1){
        pDerivedObj->c = al_map_rgb(50, 200, 100);
    }else if(random() % 4 == 2){
        pDerivedObj->c = al_map_rgb(50, 100, 200);
    }else if(random() % 4 == 3){
        pDerivedObj->c = al_map_rgb(200, 50, 100);
    }
    pDerivedObj->hitbox = New_Circle(pDerivedObj->x, pDerivedObj->y, pDerivedObj->r);

    pObj->inter_obj[pObj->inter_len++] = Paddle_L;

    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Tool_update;
    pObj->Interact = Tool_interact;
    pObj->Draw = Tool_draw;
    pObj->Destroy = Tool_destroy;

    return pObj;
}

void Tool_update(Elements *const ele) {
    Tool *Obj = ((Tool *)(ele->pDerivedObj));

    Obj->y += Obj->dy;
    if(Obj->y >= HEIGHT){
        ele->dele = true;
    }

    Shape *hitbox = Obj->hitbox;
    hitbox->update_center_y(hitbox, Obj->dy);
}

void Tool_interact(Elements *const self, Elements *const ele) {
    Tool *Obj = ((Tool *)(self->pDerivedObj));

    if (ele->label == Paddle_L)
    {
        Paddle *pad = ((Paddle *)(ele->pDerivedObj));
        if (pad->hitbox->overlap(pad->hitbox, Obj->hitbox))
        {
            self->dele = true;
        }
    }
}

void Tool_draw(Elements *const ele) {
    Tool *Obj = ((Tool *)(ele->pDerivedObj));
    al_draw_filled_circle(Obj->x, Obj->y, Obj->r, Obj->c);
}

void Tool_destroy(Elements *const ele) {
    Tool *Obj = ((Tool *)(ele->pDerivedObj));
    free(Obj->hitbox);
    free(Obj);
    free(ele);
}
