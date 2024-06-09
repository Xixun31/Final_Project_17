#include <allegro5/allegro_primitives.h>
#include "gameover.h"
#include <stdbool.h>
/*
   [gameover function]
*/
Scene *New_Gameover(int label)
{
    Gameover *pDerivedObj = (Gameover *)malloc(sizeof(Gameover));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->font1 = al_load_ttf_font("assets/font/DIN Condensed Bold.ttf", 32, 0);
    pDerivedObj->font2 = al_load_ttf_font("assets/font/DIN Condensed Bold.ttf", 40, 0);
    // Load sound
    pDerivedObj->song = al_load_sample("assets/sound/menu.mp3");
    al_reserve_samples(20);
    pDerivedObj->sample_instance = al_create_sample_instance(pDerivedObj->song);
    pDerivedObj->title_x = WIDTH / 2;
    pDerivedObj->title_y = HEIGHT / 2;

    pDerivedObj->mouse_over_back = false;

    // Loop the song until the display closes
    al_set_sample_instance_playmode(pDerivedObj->sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance, al_get_default_mixer());
    // set the volume of instance
    al_set_sample_instance_gain(pDerivedObj->sample_instance, 0.1);
    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Update = gameover_update;
    pObj->Draw = gameover_draw;
    pObj->Destroy = gameover_destroy;
    return pObj;
}
void gameover_update(Scene *self){
    ALLEGRO_MOUSE_STATE mouse_state;
    al_get_mouse_state(&mouse_state);

    Gameover *Obj = ((Gameover *)(self->pDerivedObj));
    Obj->mouse_over_back = (mouse_state.x >= Obj->title_x - 355 && mouse_state.x <= Obj->title_x - 285 &&
                                mouse_state.y >= Obj->title_y + 210 && mouse_state.y <= Obj->title_y + 240);

    if (mouse_state.buttons & 1) {
        if (Obj->mouse_over_back) {
            self->scene_end = true;
            window = 0;
        }
    }
    return;
}
void gameover_draw(Scene *self)
{
    Gameover *Obj = ((Gameover *)(self->pDerivedObj));
    ALLEGRO_COLOR back_color = Obj->mouse_over_back ? al_map_rgb(179, 209, 255) : al_map_rgb(255, 255, 255);

    al_draw_text(Obj->font1, al_map_rgb(255, 255, 255), Obj->title_x - 220, Obj->title_y - 200, ALLEGRO_ALIGN_LEFT, "to move the paddle");
    al_draw_text(Obj->font1, al_map_rgb(255, 255, 255), Obj->title_x - 350, Obj->title_y - 150, ALLEGRO_ALIGN_LEFT, "Press    to pause the game");
    al_draw_filled_circle(Obj->title_x - 277, Obj->title_y - 147, 3, al_map_rgb(255, 255, 255));
    al_draw_filled_circle(Obj->title_x - 277, Obj->title_y - 137, 3, al_map_rgb(255, 255, 255));
    al_draw_filled_circle(Obj->title_x - 277, Obj->title_y - 127, 3, al_map_rgb(255, 255, 255));

    al_draw_filled_circle(Obj->title_x- 350, Obj->title_y - 30, 8, al_map_rgb(205, 150, 50));
    al_draw_text(Obj->font1, al_map_rgb(255, 255, 255), Obj->title_x - 320, Obj->title_y - 40, ALLEGRO_ALIGN_LEFT, "Extend the paddle");
    al_draw_filled_circle(Obj->title_x- 350, Obj->title_y + 20, 8, al_map_rgb(50, 200, 100));
    al_draw_text(Obj->font1, al_map_rgb(255, 255, 255), Obj->title_x - 320, Obj->title_y + 10, ALLEGRO_ALIGN_LEFT, "Shorten the paddle");
    al_draw_filled_circle(Obj->title_x- 350, Obj->title_y + 70, 8, al_map_rgb(50, 100, 200));
    al_draw_text(Obj->font1, al_map_rgb(255, 255, 255), Obj->title_x - 320, Obj->title_y + 60, ALLEGRO_ALIGN_LEFT, "Change the control direction of the paddle");
    al_draw_filled_circle(Obj->title_x- 350, Obj->title_y + 120, 8, al_map_rgb(200, 50, 100));
    al_draw_text(Obj->font1, al_map_rgb(255, 255, 255), Obj->title_x - 320, Obj->title_y + 110, ALLEGRO_ALIGN_LEFT, "Add one ball");

    al_draw_text(Obj->font2, back_color, Obj->title_x - 350, Obj->title_y + 210, ALLEGRO_ALIGN_LEFT, "Back");
    al_play_sample_instance(Obj->sample_instance);
}
void gameover_destroy(Scene *self)
{
    Gameover *Obj = ((Gameover *)(self->pDerivedObj));
    al_destroy_font(Obj->font1);
    al_destroy_font(Obj->font2);
    al_destroy_sample(Obj->song);
    al_destroy_sample_instance(Obj->sample_instance);
    free(Obj);
    free(self);
}