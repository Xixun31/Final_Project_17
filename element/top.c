#include "top.h"
#include "../shapes/Rectangle.h"
#include "../shapes/Shape.h"
#include "../global.h"
#include <allegro5/allegro_primitives.h>

Elements *New_Top(int label) {
    Top *pDerivedObj = (Top *)malloc(sizeof(Top));
    Elements *pObj = New_Elements(label);

    // Initialize Top properties
    pDerivedObj->x = 0;
    pDerivedObj->y = 80;
    pDerivedObj->w = WIDTH;
    pDerivedObj->h = 5;
    pDerivedObj->c = al_map_rgb(105, 105, 105);
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x, pDerivedObj->y, pDerivedObj->x + pDerivedObj->w,
                                        pDerivedObj->y + pDerivedObj->h);

    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Top_update;
    pObj->Draw = Top_draw;
    pObj->Destroy = Top_destroy;
    pObj->Interact = Top_interact;

    return pObj;
}

void Top_update(Elements *const ele) {}

void Top_draw(Elements *const ele) {
    Top *Obj = ((Top *)(ele->pDerivedObj));
    al_draw_filled_rectangle(Obj->x, Obj->y, Obj->x + Obj->w, Obj->y + Obj->h, Obj->c);
}
void Top_interact(Elements *self, Elements *tar) {}

void Top_destroy(Elements *const ele) {
    Top *Obj = ((Top *)(ele->pDerivedObj));
    free(Obj->hitbox);
    free(Obj);
    free(ele);
}