#include "gamescene.h"
#include "gameover.h"
#include "../global.h"
#include "sceneManager.h"
#include <stdio.h>
/*
   [GameScene function]
*/

Scene *New_GameScene(int label)
{
    int i, j;
    GameScene *pDerivedObj = (GameScene *)malloc(sizeof(GameScene));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->font1 = al_load_ttf_font("assets/font/DIN Condensed Bold.ttf", 28, 0);
    pDerivedObj->background = al_load_bitmap("assets/image/stage.jpg");
    pDerivedObj->heart_image = al_load_bitmap("assets/image/heart.png"); 

    if (!pDerivedObj->background || !pDerivedObj->heart_image) {
        fprintf(stderr, "Failed to load background or heart image!\n");
        al_destroy_font(pDerivedObj->font1);
        if (pDerivedObj->background) al_destroy_bitmap(pDerivedObj->background);
        if (pDerivedObj->heart_image) al_destroy_bitmap(pDerivedObj->heart_image);
        free(pDerivedObj);
        return NULL;
    }

    pObj->pDerivedObj = pDerivedObj;

    ALLEGRO_SAMPLE *sample = al_load_sample("assets/sound/box.wav");
    pDerivedObj->box_sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(pDerivedObj->box_sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(pDerivedObj->box_sound, al_get_default_mixer());

    start_time = al_get_time();
    pDerivedObj->pause = false;
    pDerivedObj->last = 0;
    pDerivedObj->mouse_over_set = false;
    pDerivedObj->mouse_over_resume = false;
    pDerivedObj->mouse_over_menu = false;
    pDerivedObj->mouse_over_restart = false;
    pDerivedObj->score = 0;
    pDerivedObj->life = 3;
    pDerivedObj->win = false;
    pDerivedObj->title_x = WIDTH / 2;
    pDerivedObj->title_y = HEIGHT / 2;
    GAME_LOSE = false;
    box_exist = 0;
    ball_exist = 0;
    GAME_START_TIME = al_get_time();
    GAME_TEMPORARY_TIME = 0;
    GAME_CURRENT_TIME = 0;
    GAME_PAUSE_TIME = 0;
    change_l = 0;
    change_s = 0;
    change_r = 0;
    // register element
    _Register_elements(pObj, New_Paddle(Paddle_L));
    _Register_elements(pObj, New_Nball(Nball_L));
    _Register_elements(pObj, New_Top(Top_L));
    for(i=0;i<11;i++){
        for(j=0;j<3;j++){
            _Register_elements(pObj, New_Box(Box_L, i, j));
        }
    }
    // setting derived object function
    pObj->Update = game_scene_update;
    pObj->Draw = game_scene_draw;
    pObj->Destroy = game_scene_destroy;
    return pObj;
}

void game_scene_update(Scene *self)
{
    ALLEGRO_MOUSE_STATE mouse_state;
    al_get_mouse_state(&mouse_state);
    int i;

    ElementVec allEle = _Get_all_elements(self);
    GameScene *Obj = ((GameScene *)(self->pDerivedObj));

    Obj->mouse_over_set = (mouse_state.x >= Obj->title_x + 385 && mouse_state.x <= Obj->title_x + 415 &&
                                mouse_state.y >= Obj->title_y - 305 && mouse_state.y <= Obj->title_y - 265);
    Obj->mouse_over_resume = (mouse_state.x >= Obj->title_x + 300 && mouse_state.x <= Obj->title_x + 370 &&
                                mouse_state.y >= Obj->title_y - 300 && mouse_state.y <= Obj->title_y - 280);
    Obj->mouse_over_menu = (mouse_state.x >= Obj->title_x + 125 && mouse_state.x <= Obj->title_x + 185 &&
                                mouse_state.y >= Obj->title_y - 300 && mouse_state.y <= Obj->title_y - 280);
    Obj->mouse_over_restart = (mouse_state.x >= Obj->title_x + 200 && mouse_state.x <= Obj->title_x + 280 &&
                                mouse_state.y >= Obj->title_y - 300 && mouse_state.y <= Obj->title_y - 280);

    if (mouse_state.buttons & 1) {
        if (Obj->mouse_over_set) {
            Obj->pause = true;
        }
        if (Obj->mouse_over_resume) {
            Obj->pause = false;
        }
        if (Obj->mouse_over_restart) {
            Obj->pause = false;
            self->scene_end = true;
            window = 1;
        }
        if (Obj->mouse_over_menu) {
            Obj->pause = false;
            self->scene_end = true;
            window = 0;
        }
    }

    if (!Obj->pause){
        for (int i = 0; i < allEle.len; i++)
        {
            allEle.arr[i]->Update(allEle.arr[i]);
        }
    }
    // update every element
    // run interact for every element
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        // run every interact object
        for (int j = 0; j < ele->inter_len; j++)
        {
            int inter_label = ele->inter_obj[j];
            ElementVec labelEle = _Get_label_elements(self, inter_label);
            for (int i = 0; i < labelEle.len; i++)
            {
                ele->Interact(ele, labelEle.arr[i]);
            }
        }
    }
    // remove element
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        if (ele->dele)
            _Remove_elements(self, ele);
    }

    if (key_state[ALLEGRO_KEY_G] || (Obj->life <= 0)) {
        self->scene_end = true;
        GAME_LOSE = true;
        window = 4;
    }
    if (key_state[ALLEGRO_KEY_W] || !box_exist) {
        self->scene_end = true;
        GAME_WIN = true;
        window = 5;
    }
    if(GAME_CURRENT_TIME - Obj->last > NEXTTIME){
        al_play_sample_instance(Obj->box_sound);
        for(i=0;i<11;i++){
            _Register_elements(self, New_Box(Box_L, i, -1));
        }
        Obj->last = GAME_CURRENT_TIME;
    }
}

void score(Scene *self){
    GameScene *Obj = ((GameScene *)(self->pDerivedObj));
    Obj->score++;
    final_score = Obj->score;
}

void life(Scene *self, int life){
    GameScene *Obj = ((GameScene *)(self->pDerivedObj));
    Obj->life += life;
    if(Obj->life > 3) Obj->life = 3;
    life_show(self);
}

void life_show(Scene *self){
    GameScene *Obj = ((GameScene *)(self->pDerivedObj));
    float heart_size = 30;
    float heart_spacing = 30; 
    float heart_x_position = Obj->title_x - 180; 
    float heart_y_position = Obj->title_y - 305; 

    for (int i = 0; i < 3; i++) {
        if (i < Obj->life) {
            al_draw_scaled_bitmap(Obj->heart_image, 0, 0, al_get_bitmap_width(Obj->heart_image), al_get_bitmap_height(Obj->heart_image),
                                  heart_x_position + i * heart_spacing, heart_y_position, heart_size, heart_size, 0);
        } else {
            al_draw_filled_circle(heart_x_position + i * heart_spacing + heart_size / 2, heart_y_position + heart_size / 2, 10, al_map_rgb(64, 64, 64));
        }
    }
}


void game_scene_draw(Scene *self)
{
    GameScene *Obj = ((GameScene *)(self->pDerivedObj));
    al_clear_to_color(al_map_rgb(64, 64, 64));
    //GameScene *gs = ((GameScene *)(self->pDerivedObj));
    //al_draw_bitmap(gs->background, 0, 0, 0);
    
    //draw time
    al_draw_text(Obj->font1, al_map_rgb(255, 255, 255), Obj->title_x - 400, Obj->title_y - 300, ALLEGRO_ALIGN_LEFT, "TIME");
    char time_str[10];
    
    GAME_CURRENT_TIME = al_get_time() - GAME_PAUSE_TIME - GAME_START_TIME;
    if (!Obj->pause){
        GAME_TEMPORARY_TIME = GAME_CURRENT_TIME;
        format_time((int)GAME_TEMPORARY_TIME, time_str, sizeof(time_str));
        al_draw_text(Obj->font1, al_map_rgb(255, 255, 255), Obj->title_x - 350, Obj->title_y - 300, ALLEGRO_ALIGN_LEFT, time_str);
    }
    else if(Obj->pause){
        GAME_PAUSE_TIME = al_get_time() - GAME_TEMPORARY_TIME - GAME_START_TIME;
        format_time((int)GAME_TEMPORARY_TIME, time_str, sizeof(time_str));
        al_draw_text(Obj->font1, al_map_rgb(255, 255, 255), Obj->title_x - 350, Obj->title_y - 300, ALLEGRO_ALIGN_LEFT, time_str);
    }
    //draw score
    al_draw_text(Obj->font1, al_map_rgb(255, 255, 255), Obj->title_x - 275, Obj->title_y - 300, ALLEGRO_ALIGN_LEFT, "SCORE");
    sprintf(Obj->score_show, "%d", Obj->score);
    al_draw_text(Obj->font1, al_map_rgb(255, 255, 255), Obj->title_x - 210, Obj->title_y - 300, ALLEGRO_ALIGN_LEFT, Obj->score_show);
    
    //draw set
    ALLEGRO_COLOR set_color = Obj->mouse_over_set ? al_map_rgb(179, 209, 255) : al_map_rgb(255, 255, 255);
    al_draw_filled_circle(Obj->title_x + 400, Obj->title_y - 290, 3, set_color);
    al_draw_filled_circle(Obj->title_x + 400, Obj->title_y - 300, 3, set_color);
    al_draw_filled_circle(Obj->title_x + 400, Obj->title_y - 280, 3, set_color);

    if (Obj->pause) {
        ALLEGRO_COLOR resume_color = Obj->mouse_over_resume ? al_map_rgb(179, 209, 255) : al_map_rgb(255, 255, 255);
        ALLEGRO_COLOR restart_color = Obj->mouse_over_restart ? al_map_rgb(179, 209, 255) : al_map_rgb(255, 255, 255);
        ALLEGRO_COLOR menu_color = Obj->mouse_over_menu ? al_map_rgb(179, 209, 255) : al_map_rgb(255, 255, 255);
        al_draw_text(Obj->font1, menu_color, Obj->title_x + 125, Obj->title_y - 300, ALLEGRO_ALIGN_LEFT, "MENU");
        al_draw_text(Obj->font1, restart_color, Obj->title_x + 200, Obj->title_y - 300, ALLEGRO_ALIGN_LEFT, "RESTART");
        al_draw_text(Obj->font1, resume_color, Obj->title_x + 300, Obj->title_y - 300, ALLEGRO_ALIGN_LEFT, "RESUME");
    }

    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Draw(ele);
    }
    life_show(self);
}
void game_scene_destroy(Scene *self)
{
    GameScene *Obj = ((GameScene *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->background);
    al_destroy_bitmap(Obj->heart_image); 
    al_destroy_sample_instance(Obj->box_sound);
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Destroy(ele);
    }
    free(Obj);
    free(self);
}

void format_time(int elapsed_seconds, char *buffer, int size) {
    int minutes = elapsed_seconds / 60;
    int seconds = elapsed_seconds % 60;
    snprintf(buffer, size, "%02d:%02d", minutes, seconds);
}
