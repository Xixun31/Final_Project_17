#include <allegro5/allegro_primitives.h>
#include "gameover.h"
#include "gamescene.h"
#include "../algif5/src/algif.h"
#include "../global.h"
#include "sceneManager.h"
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
    pDerivedObj->title_x = WIDTH / 2;
    pDerivedObj->title_y = HEIGHT / 2;

    pDerivedObj->mouse_over_restart = false;
    pDerivedObj->mouse_over_menu = false;

    char buffer[50];
    sprintf(buffer, "assets/image/Gameover.gif");
    pDerivedObj->gif_status = algif_new_gif(buffer, -1);

    pDerivedObj->background = al_load_bitmap("assets/image/gameover_background.png");
    if (!pDerivedObj->background) {
        fprintf(stderr, "Failed to load background image!\n");
    }

    // Loop the song until the display closes
    pDerivedObj->song = al_load_sample("assets/sound/Gameover.wav");
    pDerivedObj->sample_instance = al_create_sample_instance(pDerivedObj->song);
    al_set_sample_instance_playmode(pDerivedObj->sample_instance, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance, al_get_default_mixer());
    pDerivedObj->state = 1;
    // set the volume of instance
    al_set_sample_instance_gain(pDerivedObj->sample_instance, 1);
    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Update = gameover_update;
    pObj->Draw = gameover_draw;
    pObj->Destroy = gameover_destroy;
    return pObj;
}

void gameover_update(Scene *self)
{
    ALLEGRO_MOUSE_STATE mouse_state;
    al_get_mouse_state(&mouse_state);

    Gameover *Obj = ((Gameover *)(self->pDerivedObj));
    Obj->mouse_over_restart = (mouse_state.x >= Obj->title_x - 120 && mouse_state.x <= Obj->title_x - 20 &&
                               mouse_state.y >= Obj->title_y + 110 && mouse_state.y <= Obj->title_y + 140);
    Obj->mouse_over_menu = (mouse_state.x >= Obj->title_x + 40 && mouse_state.x <= Obj->title_x + 100 &&
                            mouse_state.y >= Obj->title_y + 115 && mouse_state.y <= Obj->title_y + 140);

    if (mouse_state.buttons & 1) {
        if (Obj->mouse_over_restart) {
            self->scene_end = true;
            window = 1;
        }
        if (Obj->mouse_over_menu) {
            self->scene_end = true;
            window = 0;
        }
    }
    return;
}

void gameover_draw(Scene *self)
{
    Gameover *Obj = ((Gameover *)(self->pDerivedObj));
    ALLEGRO_COLOR restart_color = Obj->mouse_over_restart ? al_map_rgb(179, 209, 255) : al_map_rgb(255, 255, 255);
    ALLEGRO_COLOR menu_color = Obj->mouse_over_menu ? al_map_rgb(179, 209, 255) : al_map_rgb(255, 255, 255);

    if (Obj->background) {
        al_draw_scaled_bitmap(Obj->background, 0, 0,
                              al_get_bitmap_width(Obj->background), al_get_bitmap_height(Obj->background),
                              0, 0, WIDTH, HEIGHT, 0);
    }

    ALLEGRO_BITMAP *frame = algif_get_bitmap(Obj->gif_status, al_get_time());
    if (frame) {
        al_draw_bitmap(frame, -220, -30, 0);
    }

    al_draw_text(Obj->font2, al_map_rgb(255, 255, 255), Obj->title_x - 45, Obj->title_y + 20, ALLEGRO_ALIGN_CENTRE, "YOUR SCORE");
    sprintf(Obj->score_str, "%d", final_score);
    al_draw_text(Obj->font2, al_map_rgb(255, 255, 255), Obj->title_x + 70, Obj->title_y + 20, ALLEGRO_ALIGN_CENTRE, Obj->score_str);
    al_draw_text(Obj->font1, restart_color, Obj->title_x - 30, Obj->title_y + 110, ALLEGRO_ALIGN_RIGHT, "RESTART");
    al_draw_text(Obj->font1, menu_color, Obj->title_x + 30, Obj->title_y + 110, ALLEGRO_ALIGN_LEFT, "MENU");

    if (Obj->state) {
        al_play_sample_instance(Obj->sample_instance);
        Obj->state = 0;
    }
}

void gameover_destroy(Scene *self)
{
    Gameover *Obj = ((Gameover *)(self->pDerivedObj));
    al_destroy_font(Obj->font1);
    al_destroy_font(Obj->font2);
    al_destroy_sample(Obj->song);
    al_destroy_sample_instance(Obj->sample_instance);
    algif_destroy_animation(Obj->gif_status);

    if (Obj->background) {
        al_destroy_bitmap(Obj->background);
    }

    free(Obj);
    free(self);
}
