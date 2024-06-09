#include "tool.h"
#include "../shapes/Circle.h"
#include "../shapes/Shape.h"
#include "../global.h"
#include "paddle.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

Elements *New_Tool(int label, float x, float y) {
    Tool *pDerivedObj = (Tool *)malloc(sizeof(Tool));
    Elements *pObj = New_Elements(label);

    // Initialize ball properties
    pDerivedObj->x = x + 75 / 2;
    pDerivedObj->y = y + 75 / 2;
    pDerivedObj->r = 10;
    pDerivedObj->dy = 3;

    int random_choice = rand() % 6;
    switch (random_choice) {
        case 0:
            pDerivedObj->c = al_map_rgb(205, 150, 50);
            pDerivedObj->image = al_load_bitmap("assets/image/ball_extend.png");
            break;
        case 1:
            pDerivedObj->c = al_map_rgb(50, 200, 100);
            pDerivedObj->image = al_load_bitmap("assets/image/ball_shorten.png");
            break;
        case 2:
            pDerivedObj->c = al_map_rgb(50, 100, 200);
            pDerivedObj->image = al_load_bitmap("assets/image/ball_reverse.png");
            break;
        case 3:
            pDerivedObj->c = al_map_rgb(250, 50, 50);
            pDerivedObj->image = al_load_bitmap("assets/image/ball_add.png");
            break;
        case 4:
            pDerivedObj->c = al_map_rgb(255, 255, 255);
            pDerivedObj->image = al_load_bitmap("assets/image/ball_extend.png");
            break;
        case 5:
            pDerivedObj->c = al_map_rgb(255, 100, 155);
            pDerivedObj->image = al_load_bitmap("assets/image/ball_shorten.png");
            break;
        default:
            pDerivedObj->c = al_map_rgb(255, 255, 255);
            pDerivedObj->image = NULL;
            break;
    }
    
    if (!pDerivedObj->image) {
        fprintf(stderr, "Failed to load tool image!\n");
    }

    pDerivedObj->hitbox = New_Circle(pDerivedObj->x, pDerivedObj->y, pDerivedObj->r);

    if (!pDerivedObj->image) {
        fprintf(stderr, "Failed to load ball_extend image!\n");
        free(pDerivedObj);
        return NULL;  
    }

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
    if (Obj->image) {
        float target_width = Obj->r * 2;  
        float target_height = Obj->r * 2; 
        float src_width = al_get_bitmap_width(Obj->image);
        float src_height = al_get_bitmap_height(Obj->image);
        float dx = Obj->x - target_width / 2;
        float dy = Obj->y - target_height / 2;
        al_draw_scaled_bitmap(Obj->image,
                              0, 0, src_width, src_height,
                              dx, dy, target_width, target_height, 0);
    } else {
        al_draw_filled_circle(Obj->x, Obj->y, Obj->r, Obj->c);
    }
}


void Tool_destroy(Elements *const ele) {
    Tool *Obj = ((Tool *)(ele->pDerivedObj));
    al_destroy_bitmap(Obj->image);
    free(Obj->hitbox);
    free(Obj);
    free(ele);
}
