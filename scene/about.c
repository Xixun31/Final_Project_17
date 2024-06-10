#include <allegro5/allegro_primitives.h>
#include "about.h"
#include <stdbool.h>

/*
   [about function]
*/
Scene *New_About(int label)
{
    About *pDerivedObj = (About *)malloc(sizeof(About));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->font1 = al_load_ttf_font("assets/font/DIN Condensed Bold.ttf", 32, 0);
    pDerivedObj->font2 = al_load_ttf_font("assets/font/DIN Condensed Bold.ttf", 40, 0);
    // Load sound
    pDerivedObj->song = al_load_sample("assets/sound/menu.wav");
    al_reserve_samples(20);
    pDerivedObj->sample_instance = al_create_sample_instance(pDerivedObj->song);
    pDerivedObj->title_x = WIDTH / 2;
    pDerivedObj->title_y = HEIGHT / 2;

    // Load tool images
    pDerivedObj->tool_images[0] = al_load_bitmap("assets/image/ball_extend.png");
    pDerivedObj->tool_images[1] = al_load_bitmap("assets/image/ball_shorten.png");
    pDerivedObj->tool_images[2] = al_load_bitmap("assets/image/ball_reverse.png");
    pDerivedObj->tool_images[3] = al_load_bitmap("assets/image/ball_add.png");
    pDerivedObj->tool_images[4] = al_load_bitmap("assets/image/bomb.png");
    pDerivedObj->tool_images[5] = al_load_bitmap("assets/image/ball_life.png"); 

    pDerivedObj->mouse_over_back = false;

    // Loop the song until the display closes
    al_set_sample_instance_playmode(pDerivedObj->sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance, al_get_default_mixer());
    // set the volume of instance
    al_set_sample_instance_gain(pDerivedObj->sample_instance, 1);
    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Update = about_update;
    pObj->Draw = about_draw;
    pObj->Destroy = about_destroy;
    return pObj;
}

void about_update(Scene *self)
{
    ALLEGRO_MOUSE_STATE mouse_state;
    al_get_mouse_state(&mouse_state);

    About *Obj = ((About *)(self->pDerivedObj));
    Obj->mouse_over_back = (mouse_state.x >= Obj->title_x - 355 && mouse_state.x <= Obj->title_x - 285 &&
                            mouse_state.y >= Obj->title_y + 230 && mouse_state.y <= Obj->title_y + 260);

    if (mouse_state.buttons & 1)
    {
        if (Obj->mouse_over_back)
        {
            self->scene_end = true;
            window = 0;
        }
    }
    return;
}

void about_draw(Scene *self)
{
    About *Obj = ((About *)(self->pDerivedObj));
    ALLEGRO_COLOR back_color = Obj->mouse_over_back ? al_map_rgb(179, 209, 255) : al_map_rgb(255, 255, 255);

    // Adjust the horizontal position of the text to align with the rest of the content
    float text_x_position = Obj->title_x - 350;

    al_draw_text(Obj->font1, al_map_rgb(255, 255, 255), text_x_position, Obj->title_y - 200, ALLEGRO_ALIGN_LEFT, "Use the left and right arrow on your keyboard to move the paddle");
    al_draw_text(Obj->font1, al_map_rgb(255, 255, 255), text_x_position, Obj->title_y - 150, ALLEGRO_ALIGN_LEFT, "Press    to pause the game");
    al_draw_filled_circle(Obj->title_x - 277, Obj->title_y - 147, 3, al_map_rgb(255, 255, 255));
    al_draw_filled_circle(Obj->title_x - 277, Obj->title_y - 137, 3, al_map_rgb(255, 255, 255));
    al_draw_filled_circle(Obj->title_x - 277, Obj->title_y - 127, 3, al_map_rgb(255, 255, 255));

    float scale_factor = 2.0; // Adjust this value to make images larger
    float img_size = 16 * scale_factor;
    float text_y_offset = 8;
    float text_x_offset = 10;

    al_draw_scaled_bitmap(Obj->tool_images[0], 0, 0, al_get_bitmap_width(Obj->tool_images[0]), al_get_bitmap_height(Obj->tool_images[0]), Obj->title_x - 350, Obj->title_y - 80 - img_size / 2 + text_y_offset, img_size, img_size, 0);
    al_draw_text(Obj->font1, al_map_rgb(255, 255, 255), Obj->title_x - 350 + img_size + text_x_offset, Obj->title_y - 80, ALLEGRO_ALIGN_LEFT, "Extend the paddle");

    al_draw_scaled_bitmap(Obj->tool_images[1], 0, 0, al_get_bitmap_width(Obj->tool_images[1]), al_get_bitmap_height(Obj->tool_images[1]), Obj->title_x - 350, Obj->title_y - 30 - img_size / 2 + text_y_offset, img_size, img_size, 0);
    al_draw_text(Obj->font1, al_map_rgb(255, 255, 255), Obj->title_x - 350 + img_size + text_x_offset, Obj->title_y - 30, ALLEGRO_ALIGN_LEFT, "Shorten the paddle");

    al_draw_scaled_bitmap(Obj->tool_images[2], 0, 0, al_get_bitmap_width(Obj->tool_images[2]), al_get_bitmap_height(Obj->tool_images[2]), Obj->title_x - 350, Obj->title_y + 20 - img_size / 2 + text_y_offset, img_size, img_size, 0);
    al_draw_text(Obj->font1, al_map_rgb(255, 255, 255), Obj->title_x - 350 + img_size + text_x_offset, Obj->title_y + 20, ALLEGRO_ALIGN_LEFT, "Change the control direction of the paddle");

    al_draw_scaled_bitmap(Obj->tool_images[3], 0, 0, al_get_bitmap_width(Obj->tool_images[3]), al_get_bitmap_height(Obj->tool_images[3]), Obj->title_x - 350, Obj->title_y + 70 - img_size / 2 + text_y_offset, img_size, img_size, 0);
    al_draw_text(Obj->font1, al_map_rgb(255, 255, 255), Obj->title_x - 350 + img_size + text_x_offset, Obj->title_y + 70, ALLEGRO_ALIGN_LEFT, "Add one ball");

    al_draw_scaled_bitmap(Obj->tool_images[4], 0, 0, al_get_bitmap_width(Obj->tool_images[4]), al_get_bitmap_height(Obj->tool_images[4]), Obj->title_x - 350, Obj->title_y + 120 - img_size / 2 + text_y_offset, img_size, img_size, 0);
    al_draw_text(Obj->font1, al_map_rgb(255, 255, 255), Obj->title_x - 350 + img_size + text_x_offset, Obj->title_y + 120, ALLEGRO_ALIGN_LEFT, "Bomb. Reduce one life");

    al_draw_scaled_bitmap(Obj->tool_images[5], 0, 0, al_get_bitmap_width(Obj->tool_images[5]), al_get_bitmap_height(Obj->tool_images[5]), Obj->title_x - 350, Obj->title_y + 170 - img_size / 2 + text_y_offset, img_size, img_size, 0);
    al_draw_text(Obj->font1, al_map_rgb(255, 255, 255), Obj->title_x - 350 + img_size + text_x_offset, Obj->title_y + 170, ALLEGRO_ALIGN_LEFT, "Life Ball. Restore one life");

    al_draw_text(Obj->font2, back_color, Obj->title_x - 350, Obj->title_y + 230, ALLEGRO_ALIGN_LEFT, "Back");
    al_play_sample_instance(Obj->sample_instance);
}
void about_destroy(Scene *self)
{
    About *Obj = ((About *)(self->pDerivedObj));
    al_destroy_font(Obj->font1);
    al_destroy_font(Obj->font2);
    al_destroy_sample(Obj->song);
    al_destroy_sample_instance(Obj->sample_instance);

    // Destroy tool images
    for (int i = 0; i < 6; i++) {
        al_destroy_bitmap(Obj->tool_images[i]);
    }

    free(Obj);
    free(self);
}
