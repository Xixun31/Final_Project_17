#include "box.h"
#include "../shapes/Rectangle.h"
#include "../shapes/Shape.h"
#include "../global.h"
#include <allegro5/allegro_primitives.h>
#include "nball.h"

Elements *New_Box(int label) {
    Box *pDerivedObj = (Box *)malloc(sizeof(Box));
    Elements *pObj = New_Elements(label);

    // Initialize Box properties
    pDerivedObj->x = WIDTH - 50 ;
    pDerivedObj->y = HEIGHT - 50;
    pDerivedObj->w = 50;
    pDerivedObj->h = 50;
    pDerivedObj->c = al_map_rgb(205, 205, 205);
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x, pDerivedObj->y, pDerivedObj->x + pDerivedObj->w,
                                        pDerivedObj->y + pDerivedObj->h);

    pObj->inter_obj[pObj->inter_len++] = Nball_L;

    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Box_update;
    pObj->Draw = Box_draw;
    pObj->Destroy = Box_destroy;

    return pObj;
}

void Box_update(Elements *const ele) {

}
void Box_interact(Elements *self, Elements *tar){
    Box *Obj = ((Box *)(self->pDerivedObj));
    if (tar->label == Nball_L)
    {
        Nball *ba = ((Nball *)(tar->pDerivedObj));
        if (ba->hitbox->overlap(ba->hitbox, Obj->hitbox))
        {
            self->dele = true;
        }
    }
}
void Box_draw(Elements *const ele) {
    Box *Obj = ((Box *)(ele->pDerivedObj));
    al_draw_filled_rectangle(Obj->x, Obj->y, Obj->x + Obj->w, Obj->y + Obj->h, Obj->c);
}

void Box_destroy(Elements *const ele) {
    Box *Obj = ((Box *)(ele->pDerivedObj));
    free(Obj->hitbox);
    free(Obj);
    free(ele);
    // random call tool
}
