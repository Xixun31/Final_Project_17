#include <allegro5/allegro_primitives.h>
#include "menu.h"
#include <stdbool.h>
/*
   [Menu function]
*/
Scene *New_Menu(int label)
{
    Menu *pDerivedObj = (Menu *)malloc(sizeof(Menu));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->font = al_load_ttf_font("assets/font/DIN Condensed Bold.ttf", 32, 0);
    // Load sound
    pDerivedObj->song = al_load_sample("assets/sound/menu.mp3");
    al_reserve_samples(20);
    pDerivedObj->sample_instance = al_create_sample_instance(pDerivedObj->song);
    pDerivedObj->title_x = WIDTH / 2;
    pDerivedObj->title_y = HEIGHT / 2;
    // Loop the song until the display closes
    al_set_sample_instance_playmode(pDerivedObj->sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance, al_get_default_mixer());
    // set the volume of instance
    al_set_sample_instance_gain(pDerivedObj->sample_instance, 0.1);
    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Update = menu_update;
    pObj->Draw = menu_draw;
    pObj->Destroy = menu_destroy;
    return pObj;
}
void menu_update(Scene *self)
{
    if (key_state[ALLEGRO_KEY_ENTER])
    {
        self->scene_end = true;
        window = 1;
    }
    return;
}
void menu_draw(Scene *self)
{
    Menu *Obj = ((Menu *)(self->pDerivedObj));
    al_draw_text(Obj->font, al_map_rgb(255, 255, 255), Obj->title_x, Obj->title_y - 150, ALLEGRO_ALIGN_CENTRE, "NEW GAME");
    al_draw_rectangle(Obj->title_x - 100, Obj->title_y - 170, Obj->title_x + 100, Obj->title_y - 110, al_map_rgb(255, 255, 255), 3);
    al_draw_text(Obj->font, al_map_rgb(255, 255, 255), Obj->title_x, Obj->title_y - 50, ALLEGRO_ALIGN_CENTRE, "LEVEL");
    al_draw_rectangle(Obj->title_x - 100, Obj->title_y - 70, Obj->title_x + 100, Obj->title_y - 10, al_map_rgb(255, 255, 255), 3);
    al_draw_text(Obj->font, al_map_rgb(255, 255, 255), Obj->title_x, Obj->title_y + 50, ALLEGRO_ALIGN_CENTRE, "ABOUT");
    al_draw_rectangle(Obj->title_x - 100, Obj->title_y + 30, Obj->title_x + 100, Obj->title_y + 90, al_map_rgb(255, 255, 255), 3);
    al_play_sample_instance(Obj->sample_instance);
}
void menu_destroy(Scene *self)
{
    Menu *Obj = ((Menu *)(self->pDerivedObj));
    al_destroy_font(Obj->font);
    al_destroy_sample(Obj->song);
    al_destroy_sample_instance(Obj->sample_instance);
    free(Obj);
    free(self);
}