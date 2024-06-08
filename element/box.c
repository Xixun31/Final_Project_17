#include "box.h"
#include "tool.h"
#include "../shapes/Rectangle.h"
#include "../shapes/Shape.h"
#include "../global.h"
#include <allegro5/allegro_primitives.h>
#include "../scene/sceneManager.h"
/*
   [Box function]
*/
Elements *New_Box(int label)
{
    Box *pDerivedObj = (Box *)malloc(sizeof(Box));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->x = WIDTH/2 - 75;
    pDerivedObj->y = 160;
    pDerivedObj->w = 75;
    pDerivedObj->h = 75;
    pDerivedObj->c = al_map_rgb(255, 255, 255);
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x, pDerivedObj->y, pDerivedObj->x + 3,
                                        pDerivedObj->y + pDerivedObj->h);
    pDerivedObj->hitboxr = New_Rectangle(pDerivedObj->x + pDerivedObj->w - 3, pDerivedObj->y, 
                                        pDerivedObj->x + pDerivedObj->w, pDerivedObj->y + pDerivedObj->h);
    pDerivedObj->hitboy = New_Rectangle(pDerivedObj->x, pDerivedObj->y + pDerivedObj->h - 3, 
                                        pDerivedObj->x + pDerivedObj->w, pDerivedObj->y + pDerivedObj->h);
    pDerivedObj->hitboyr = New_Rectangle(pDerivedObj->x, pDerivedObj->y, 
                                        pDerivedObj->x + pDerivedObj->w, pDerivedObj->y + 3);

    pObj->inter_obj[pObj->inter_len++] = Nball_L;

    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Box_update;
    pObj->Interact = Box_interact;
    pObj->Draw = Box_draw;
    pObj->Destroy = Box_destory;
    return pObj;
}
void Box_update(Elements *self) {}
void Box_interact(Elements *self, Elements *tar) {
    Box *Obj = ((Box *)(self->pDerivedObj));
    if (tar->label == Nball_L)
    {
        Nball *nb = ((Nball *)(tar->pDerivedObj));
        if (nb->hitbox->overlap(nb->hitbox, Obj->hitbox) || nb->hitbox->overlap(nb->hitbox, Obj->hitboxr)
         || nb->hitbox->overlap(nb->hitbox, Obj->hitboy) || nb->hitbox->overlap(nb->hitbox, Obj->hitboyr))
        {
            self->dele = true;
            _Register_elements(scene, New_Tool(Tool_L, Obj->x, Obj->y));
            _Register_elements(scene, New_Box(Box_L));
        }
    }
}
void Box_draw(Elements *self)
{
    Box *Obj = ((Box *)(self->pDerivedObj));
    al_draw_filled_rectangle(Obj->x, Obj->y, Obj->x + Obj->w, Obj->y + Obj->h, Obj->c);
}
void Box_destory(Elements *self)
{
    Box *Obj = ((Box *)(self->pDerivedObj));
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
