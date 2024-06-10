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

    pDerivedObj->random_choice = rand() % 6;
    switch (pDerivedObj->random_choice) {
        case 0:
            pDerivedObj->c = al_map_rgb(205, 150, 50);
            pDerivedObj->image = al_load_bitmap("assets/image/ball_extend.png");
            pDerivedObj->dy = 3;
            break;
        case 1:
            pDerivedObj->c = al_map_rgb(50, 200, 100);
            pDerivedObj->image = al_load_bitmap("assets/image/ball_shorten.png");
            pDerivedObj->dy = 3;
            break;
        case 2:
            pDerivedObj->c = al_map_rgb(50, 100, 200);
            pDerivedObj->image = al_load_bitmap("assets/image/ball_reverse.png");
            pDerivedObj->dy = 7;
            break;
        case 3:
            pDerivedObj->c = al_map_rgb(150, 0, 10);
            pDerivedObj->image = al_load_bitmap("assets/image/ball_add.png");
            pDerivedObj->dy = 7;
            break;
        case 4:
            pDerivedObj->c = al_map_rgb(255, 255, 255);
            pDerivedObj->image = al_load_bitmap("assets/image/bomb.png");
            pDerivedObj->dy = 7;
            break;
        case 5:
            pDerivedObj->c = al_map_rgb(255, 100, 155);
            pDerivedObj->image = al_load_bitmap("assets/image/ball_life.png");
            pDerivedObj->dy = 3;
            break;
    }
    
    if (!pDerivedObj->image) {
        fprintf(stderr, "Failed to load tool image!\n");
    }

    pDerivedObj->hitbox = New_Circle(pDerivedObj->x, pDerivedObj->y, pDerivedObj->r);


    pObj->inter_obj[pObj->inter_len++] = Paddle_L;

    ALLEGRO_SAMPLE *sample = al_load_sample("assets/sound/tool.wav");
    pDerivedObj->tool_sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(pDerivedObj->tool_sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(pDerivedObj->tool_sound, al_get_default_mixer());

    ALLEGRO_SAMPLE *sample_ = al_load_sample("assets/sound/gg.wav");
    pDerivedObj->gg_sound = al_create_sample_instance(sample_);
    al_set_sample_instance_playmode(pDerivedObj->gg_sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(pDerivedObj->gg_sound, al_get_default_mixer());


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
    if(GAME_LOSE || GAME_WIN){
        ele->dele = true;
    }
}

void Tool_interact(Elements *const self, Elements *const ele) {
    Tool *Obj = ((Tool *)(self->pDerivedObj));

    if (ele->label == Paddle_L)
    {
        Paddle *pad = ((Paddle *)(ele->pDerivedObj));
        if (pad->hitbox->overlap(pad->hitbox, Obj->hitbox))
        {
            switch (Obj->random_choice)
            {
            case 0:
                al_play_sample_instance(Obj->tool_sound);                /* code */
                break;
            case 1:
                al_play_sample_instance(Obj->gg_sound);
                break;
            case 2:
                al_play_sample_instance(Obj->gg_sound);
                break;
            case 3:
                al_play_sample_instance(Obj->tool_sound);                /* code */
                break;
            case 4:
                al_play_sample_instance(Obj->gg_sound);
                break;
            case 5:
                al_play_sample_instance(Obj->tool_sound);                /* code */
                break;
            default:
                break;
            }

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
    al_destroy_sample_instance(Obj->tool_sound);
    al_destroy_sample_instance(Obj->gg_sound);
    al_destroy_bitmap(Obj->image);
    free(Obj->hitbox);
    free(Obj);
    free(ele);
}
