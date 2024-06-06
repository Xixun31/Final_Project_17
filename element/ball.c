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
    pDerivedObj->c = al_map_rgb(200, 100, 150);
    pDerivedObj->hitbox = New_Circle(pDerivedObj->x,pDerivedObj->y,pDerivedObj->r);
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Tree_L;
    pObj->inter_obj[pObj->inter_len++] = Character_L;
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
    Obj->x += mouse.x;
    Obj->y += mouse.y;
    Shape *hitbox = Obj->hitbox;
    hitbox->update_center_x(hitbox, mouse.x - Obj->x);
    hitbox->update_center_y(hitbox, mouse.y - Obj->y);
}
void Ball_interact(Elements *self, Elements *tar){
    Ball *Obj = ((Ball *)(self->pDerivedObj));
    if (tar->label == Tree_L)
    {
        Tree *tree = ((Tree *)(tar->pDerivedObj));
        if (tree->hitbox->overlap(tree->hitbox, Obj->hitbox))
        {
            Obj->c = al_map_rgb(50, 200, 200);
        }else{
            Obj->c = al_map_rgb(200, 100, 150);
        }
    }
    else if (tar->label == Character_L)
    {
        Character *chara = ((Character *)(tar->pDerivedObj));
        if (chara->hitbox->overlap(chara->hitbox, Obj->hitbox))
        {
            Obj->c = al_map_rgb(50, 100, 200);
        }else{
            Obj->c = al_map_rgb(200, 100, 150);
        }
    }
}
void Ball_draw(Elements *self){
    Ball *Obj = ((Ball *)(self->pDerivedObj));
    al_draw_circle(Obj->x, Obj->y, Obj->r, al_map_rgb(200, 100, 150), 5);
}
void Ball_destory(Elements *self){
    Ball *Obj = ((Ball *)(self->pDerivedObj));
    free(Obj->hitbox);
    free(Obj);
    free(self);
}