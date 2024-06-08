#include "ball.h"
#include "../shapes/Circle.h"
#include "../global.h"
#include <allegro5/allegro_primitives.h>

Elements *New_Ball(int label){
    Ball *pDerivedObj = (Ball *)malloc(sizeof(Ball));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->x = mouse.x;
    pDerivedObj->y = mouse.y;
    pDerivedObj->r = 10;
    pDerivedObj->c = al_map_rgb(150, 50, 250);
    pDerivedObj->hitbox = New_Circle(pDerivedObj->x,pDerivedObj->y,pDerivedObj->r);
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Tree_L;
    pObj->inter_obj[pObj->inter_len++] = Character_L;
    pObj->inter_obj[pObj->inter_len++] = Paddle_L;
    pObj->inter_obj[pObj->inter_len++] = Nball_L;
    pObj->inter_obj[pObj->inter_len++] = Box_L;
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Ball_update;
    pObj->Interact = Ball_interact;
    pObj->Draw = Ball_draw;
    pObj->Destroy = Ball_destory;
    return pObj;

}
void Ball_update(Elements *self){
    Ball *Obj = ((Ball *)(self->pDerivedObj));
    Shape *hitbox = Obj->hitbox;
    hitbox->update_center_x(hitbox, mouse.x - Obj->x);
    hitbox->update_center_y(hitbox, mouse.y - Obj->y);
    Obj->x = mouse.x;
    Obj->y = mouse.y;
}
void Ball_interact(Elements *self, Elements *tar){
    Ball *Obj = ((Ball *)(self->pDerivedObj));
    /* if (tar->label == Tree_L)
    {
        Tree *tree = ((Tree *)(tar->pDerivedObj));
        if (tree->hitbox->overlap(tree->hitbox, Obj->hitbox))
        {
            Obj->c = al_map_rgb(50, 200, 150);
        }
    }
    else if (tar->label == Character_L)
    {
        Character *chara = ((Character *)(tar->pDerivedObj));
        if (chara->hitbox->overlap(chara->hitbox, Obj->hitbox))
        {
            Obj->c = al_map_rgb(50, 100, 200);
        }
    } */
    if (tar->label == Nball_L)
    {
        Nball *ba = ((Nball *)(tar->pDerivedObj));
        if (ba->hitbox->overlap(ba->hitbox, Obj->hitbox))
        {
            Obj->c = al_map_rgb(100, 100, 100);
        }
    }
    else if (tar->label == Paddle_L)
    {
        Paddle *pad = ((Paddle *)(tar->pDerivedObj));
        if (pad->hitbox->overlap(pad->hitbox, Obj->hitbox))
        {
            Obj->c = al_map_rgb(255, 50, 50);
        }
    }else if(tar->label == Box_L){
        Box *box = ((Box *)(tar->pDerivedObj));
        if (box->hitbox->overlap(box->hitbox, Obj->hitbox) || box->hitboxr->overlap(box->hitboxr, Obj->hitbox))
        {
            Obj->c = al_map_rgb(0, 250, 50);
        }else if(box->hitboy->overlap(box->hitboy, Obj->hitbox) || box->hitboyr->overlap(box->hitboyr, Obj->hitbox)){
            Obj->c = al_map_rgb(0, 50, 250);
        }else{
            Obj->c = al_map_rgb(150, 50, 250);
        }
    }
}
void Ball_draw(Elements *self){
    Ball *Obj = ((Ball *)(self->pDerivedObj));
    al_draw_circle(Obj->x, Obj->y, Obj->r, Obj->c, 5);
}
void Ball_destory(Elements *self){
    Ball *Obj = ((Ball *)(self->pDerivedObj));
    free(Obj->hitbox);
    free(Obj);
    free(self);
}