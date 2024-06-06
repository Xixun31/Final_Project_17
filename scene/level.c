#include <allegro5/allegro_primitives.h>
#include "level.h"
#include <stdbool.h>
/*
   [Level function]
*/
Scene *New_Level(int label)
{
    Level *pDerivedObj = (Level *)malloc(sizeof(Level));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->font1 = al_load_ttf_font("assets/font/DIN Condensed Bold.ttf", 32, 0);
    pDerivedObj->font2 = al_load_ttf_font("assets/font/DIN Condensed Bold.ttf", 64, 0);
    // Load sound
    pDerivedObj->song = al_load_sample("assets/sound/menu.mp3");
    al_reserve_samples(20);
    pDerivedObj->sample_instance = al_create_sample_instance(pDerivedObj->song);
    pDerivedObj->title_x = WIDTH / 2;
    pDerivedObj->title_y = HEIGHT / 2;

    pDerivedObj->mouse_over_easy = false;
    pDerivedObj->mouse_over_medium = false;
    pDerivedObj->mouse_over_hard = false;
    // Loop the song until the display closes
    al_set_sample_instance_playmode(pDerivedObj->sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance, al_get_default_mixer());
    // set the volume of instance
    al_set_sample_instance_gain(pDerivedObj->sample_instance, 0.1);
    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Update = level_update;
    pObj->Draw = level_draw;
    pObj->Destroy = level_destroy;
    return pObj;
}
void level_update(Scene *self)
{
    ALLEGRO_MOUSE_STATE mouse_state;
    al_get_mouse_state(&mouse_state);

    Level *Obj = ((Level *)(self->pDerivedObj));

    Obj->mouse_over_easy = (mouse_state.x >= Obj->title_x - 300 && mouse_state.x <= Obj->title_x - 240 &&
                                mouse_state.y >= Obj->title_y - 40 && mouse_state.y <= Obj->title_y - 15);

    Obj->mouse_over_medium = (mouse_state.x >= Obj->title_x - 300 && mouse_state.x <= Obj->title_x - 220 &&
                             mouse_state.y >= Obj->title_y  && mouse_state.y <= Obj->title_y + 25);

    Obj->mouse_over_hard = (mouse_state.x >= Obj->title_x - 300 && mouse_state.x <= Obj->title_x - 240 &&
                             mouse_state.y >= Obj->title_y + 40 && mouse_state.y <= Obj->title_y + 65);


    if (mouse_state.buttons & 1) {
        if (Obj->mouse_over_easy) {
            self->scene_end = true;
            window = 0;
        }
        else if (Obj->mouse_over_medium){
            self->scene_end = true;
            window = 0;
        }
        else if (Obj->mouse_over_hard){
            self->scene_end = true;
            window = 0;
        }
       
    }
    return;
}
void level_draw(Scene *self)
{
    Level *Obj = ((Level *)(self->pDerivedObj));

    ALLEGRO_COLOR easy_color = Obj->mouse_over_easy ? al_map_rgb(179, 209, 255) : al_map_rgb(255, 255, 255);
    ALLEGRO_COLOR medium_color = Obj->mouse_over_medium ? al_map_rgb(179, 209, 255) : al_map_rgb(255, 255, 255);
    ALLEGRO_COLOR hard_color = Obj->mouse_over_hard ? al_map_rgb(179, 209, 255) : al_map_rgb(255, 255, 255);

    al_draw_text(Obj->font1, easy_color, Obj->title_x - 300, Obj->title_y - 40, ALLEGRO_ALIGN_LEFT, "EASY");//y = 25,x = 70
    al_draw_text(Obj->font1, medium_color, Obj->title_x - 300, Obj->title_y, ALLEGRO_ALIGN_LEFT, "MEDIUM");
    al_draw_text(Obj->font1, hard_color, Obj->title_x - 300, Obj->title_y + 40, ALLEGRO_ALIGN_LEFT, "HARD");

    al_draw_text(Obj->font2, al_map_rgb(255, 255, 255), Obj->title_x - 300, Obj->title_y - 160, ALLEGRO_ALIGN_LEFT, "CHOOSE LEVEL");

    al_play_sample_instance(Obj->sample_instance);
}
void level_destroy(Scene *self)
{
    Level *Obj = ((Level *)(self->pDerivedObj));
    al_destroy_font(Obj->font1);
    al_destroy_font(Obj->font2);
    al_destroy_sample(Obj->song);
    al_destroy_sample_instance(Obj->sample_instance);
    free(Obj);
    free(self);
}
