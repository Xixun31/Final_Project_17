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
Elements *New_Box(int label, int col, int row)
{
    Box *pDerivedObj = (Box *)malloc(sizeof(Box));
    Elements *pObj = New_Elements(label);

    box_exist++;
    // setting derived object member
    pDerivedObj->x = col * 82;
    pDerivedObj->y = 85 + row * 82;
    pDerivedObj->w = 77;
    pDerivedObj->h = 77;
    pDerivedObj->dy = 82;
    pDerivedObj->last = 0;
    pDerivedObj->c = al_map_rgb(255, 255, 255);
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x, pDerivedObj->y, pDerivedObj->x + 5,
                                        pDerivedObj->y + pDerivedObj->h);
    pDerivedObj->hitboxr = New_Rectangle(pDerivedObj->x + pDerivedObj->w - 5, pDerivedObj->y, 
                                        pDerivedObj->x + pDerivedObj->w, pDerivedObj->y + pDerivedObj->h);
    pDerivedObj->hitboy = New_Rectangle(pDerivedObj->x, pDerivedObj->y + pDerivedObj->h - 5, 
                                        pDerivedObj->x + pDerivedObj->w, pDerivedObj->y + pDerivedObj->h);
    pDerivedObj->hitboyr = New_Rectangle(pDerivedObj->x, pDerivedObj->y, 
                                        pDerivedObj->x + pDerivedObj->w, pDerivedObj->y + 5);

    pObj->inter_obj[pObj->inter_len++] = Nball_L;

    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Box_update;
    pObj->Interact = Box_interact;
    pObj->Draw = Box_draw;
    pObj->Destroy = Box_destory;
    return pObj;
}
void Box_update(Elements *self) {
    double current, next = 13;
    current = GAME_CURRENT_TIME;

    Box *box = ((Box *)(self->pDerivedObj));
    if((box->y + box->h) > (HEIGHT - 100)){
        life(scene, -1);
        box_exist--;
        self->dele = true;
    }
    if(current - box->last > next)
    {   
        box->last = current;
        box->y += box->dy;
        box->hitbox->update_center_y(box->hitbox, box->dy);
        box->hitboxr->update_center_y(box->hitboxr, box->dy);
        box->hitboyr->update_center_y(box->hitboy, box->dy);
        box->hitboy->update_center_y(box->hitboyr, box->dy);
    }
    if(box_exist == 0) win(scene);
    if(GAME_LOSE || GAME_WIN){
        self->dele = true;
    }
}
void Box_interact(Elements *self, Elements *tar) {
    Box *Obj = ((Box *)(self->pDerivedObj));
    if (tar->label == Nball_L)
        {
        Nball *nb = ((Nball *)(tar->pDerivedObj));
        if (nb->hitbox->overlap(nb->hitbox, Obj->hitbox) || nb->hitbox->overlap(nb->hitbox, Obj->hitboxr)
         || nb->hitbox->overlap(nb->hitbox, Obj->hitboy) || nb->hitbox->overlap(nb->hitbox, Obj->hitboyr))
        {
            if(!(rand() % 3)) _Register_elements(scene, New_Tool(Tool_L, Obj->x, Obj->y));
            score(scene);
            box_exist--;
            self->dele = true;
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
