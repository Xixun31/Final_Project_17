#include <allegro5/allegro_primitives.h>
#include "youwin.h"
#include "../algif5/src/algif.h"
#include <stdbool.h>
/*
   [youwin function]
*/
Scene *New_Youwin(int label)
{
    Youwin *pDerivedObj = (Youwin *)malloc(sizeof(Youwin));
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
    sprintf(buffer, "assets/image/youwin.gif");
    pDerivedObj->gif_status = algif_new_gif(buffer, -1);

    pDerivedObj->final_time = al_get_time() - start_time;
    // Loop the song until the display closes
    pDerivedObj->song = al_load_sample("assets/sound/youwin.wav");
    pDerivedObj->sample_instance = al_create_sample_instance(pDerivedObj->song);
    al_set_sample_instance_playmode(pDerivedObj->sample_instance, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance, al_get_default_mixer());
    pDerivedObj->state = 1;
    // set the volume of instance
    al_set_sample_instance_gain(pDerivedObj->sample_instance, 1.5);

    // Load background image
    pDerivedObj->background = al_load_bitmap("assets/image/youwin_background.png");
    if (!pDerivedObj->background) {
        fprintf(stderr, "Failed to load youwin background image!\n");
    }

    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Update = youwin_update;
    pObj->Draw = youwin_draw;
    pObj->Destroy = youwin_destroy;
    return pObj;
}

void youwin_update(Scene *self){
    ALLEGRO_MOUSE_STATE mouse_state;
    al_get_mouse_state(&mouse_state);

    Youwin *Obj = ((Youwin *)(self->pDerivedObj));
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

void youwin_draw(Scene *self)
{
    Youwin *Obj = ((Youwin *)(self->pDerivedObj));

    if (Obj->background) {
        al_draw_scaled_bitmap(Obj->background, 
                              0, 0, 
                              al_get_bitmap_width(Obj->background), al_get_bitmap_height(Obj->background), 
                              0, 0, WIDTH, HEIGHT, 0);
    }

    ALLEGRO_COLOR restart_color = Obj->mouse_over_restart ? al_map_rgb(179, 209, 255) : al_map_rgb(255, 255, 255);
    ALLEGRO_COLOR menu_color = Obj->mouse_over_menu ? al_map_rgb(179, 209, 255) : al_map_rgb(255, 255, 255);

    ALLEGRO_BITMAP *frame = algif_get_bitmap(Obj->gif_status, al_get_time());
    if (frame)
    {
        al_draw_bitmap(frame, -190, 20, 0);
    }

    al_draw_text(Obj->font2, al_map_rgb(255, 255, 255), Obj->title_x - 20, Obj->title_y + 20, ALLEGRO_ALIGN_RIGHT, "TIME");
    
    char time_str[10];
    format_time((int)Obj->final_time, time_str, sizeof(time_str));

    al_draw_text(Obj->font1, al_map_rgb(255, 255, 255), Obj->title_x + 20, Obj->title_y + 23, ALLEGRO_ALIGN_LEFT, time_str);

    al_draw_text(Obj->font1, restart_color, Obj->title_x - 30 , Obj->title_y + 110, ALLEGRO_ALIGN_RIGHT, "RESTART");
    al_draw_text(Obj->font1, menu_color, Obj->title_x + 30, Obj->title_y + 110, ALLEGRO_ALIGN_LEFT, "MENU");
    if (Obj->state) {
        al_play_sample_instance(Obj->sample_instance);
        Obj->state = 0;
    }
}

void youwin_destroy(Scene *self)
{
    Youwin *Obj = ((Youwin *)(self->pDerivedObj));
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
