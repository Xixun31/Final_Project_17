#include "gamescene.h"
#include "../global.h"
/*
   [GameScene function]
*/

Scene *New_GameScene(int label)
{
    
    GameScene *pDerivedObj = (GameScene *)malloc(sizeof(GameScene));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->font1 = al_load_ttf_font("assets/font/DIN Condensed Bold.ttf", 28, 0);
    pDerivedObj->background = al_load_bitmap("assets/image/stage.jpg");
    pObj->pDerivedObj = pDerivedObj;

    pDerivedObj->elapsed_seconds = 0;
    pDerivedObj->start_time = al_get_time();

    pDerivedObj->pause = false;
    pDerivedObj->mouse_over_set = false;
    pDerivedObj->mouse_over_resume = false;

    pDerivedObj->title_x = WIDTH / 2;
    pDerivedObj->title_y = HEIGHT / 2;
    // register element
    _Register_elements(pObj, New_Floor(Floor_L));
    _Register_elements(pObj, New_Teleport(Teleport_L));
    _Register_elements(pObj, New_Tree(Tree_L));
    _Register_elements(pObj, New_Character(Character_L));
    _Register_elements(pObj, New_Paddle(Paddle_L));
    _Register_elements(pObj, New_Nball(Nball_L));
    _Register_elements(pObj, New_Ball(Ball_L));
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

    ElementVec allEle = _Get_all_elements(self);
    GameScene *Obj = ((GameScene *)(self->pDerivedObj));

    Obj->mouse_over_set = (mouse_state.x >= Obj->title_x + 385 && mouse_state.x <= Obj->title_x + 415 &&
                                mouse_state.y >= Obj->title_y - 305 && mouse_state.y <= Obj->title_y - 265);
    Obj->mouse_over_resume = (mouse_state.x >= Obj->title_x + 300 && mouse_state.x <= Obj->title_x + 370 &&
                                mouse_state.y >= Obj->title_y - 300 && mouse_state.y <= Obj->title_y - 280);

    if (mouse_state.buttons & 1) {
        if (Obj->mouse_over_set) {
            Obj->pause = true;
        }
        if (Obj->mouse_over_resume) {
            Obj->pause = false;
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
    
    
    Obj->current_time = al_get_time() - Obj->pause_time;
    if (!Obj->pause){
        Obj->temporary_time = Obj->current_time;
        format_time((int)Obj->temporary_time, time_str, sizeof(time_str));
        al_draw_text(Obj->font1, al_map_rgb(255, 255, 255), Obj->title_x - 350, Obj->title_y - 300, ALLEGRO_ALIGN_LEFT, time_str);
        /*
        Obj->elapsed_seconds = (Obj->current_time - Obj->start_time - Obj->pause_time);
        format_time((int)Obj->elapsed_seconds, time_str, sizeof(time_str));
        al_draw_text(Obj->font1, al_map_rgb(255, 255, 255), Obj->title_x - 350, Obj->title_y - 300, ALLEGRO_ALIGN_LEFT, time_str);
        */
    }
    else if(Obj->pause){
        Obj->current_time = Obj->temporary_time;
        Obj->pause_time = al_get_time() - Obj->temporary_time;
        format_time((int)Obj->temporary_time, time_str, sizeof(time_str));
        al_draw_text(Obj->font1, al_map_rgb(255, 255, 255), Obj->title_x - 350, Obj->title_y - 300, ALLEGRO_ALIGN_LEFT, time_str);
        /*
        Obj->pause_time = Obj->current_time - Obj->elapsed_seconds;
        format_time((int)Obj->elapsed_seconds, time_str, sizeof(time_str));
        al_draw_text(Obj->font1, al_map_rgb(255, 255, 255), Obj->title_x - 350, Obj->title_y - 300, ALLEGRO_ALIGN_LEFT, time_str);
        */
    }
    //draw score
    al_draw_text(Obj->font1, al_map_rgb(255, 255, 255), Obj->title_x - 275, Obj->title_y - 300, ALLEGRO_ALIGN_LEFT, "SCORE");
    
    //draw set
    ALLEGRO_COLOR set_color = Obj->mouse_over_set ? al_map_rgb(179, 209, 255) : al_map_rgb(255, 255, 255);
    al_draw_filled_circle(Obj->title_x + 400, Obj->title_y - 290, 3, set_color);
    al_draw_filled_circle(Obj->title_x + 400, Obj->title_y - 300, 3, set_color);
    al_draw_filled_circle(Obj->title_x + 400, Obj->title_y - 280, 3, set_color);

    if (Obj->pause) {
        ALLEGRO_COLOR resume_color = Obj->mouse_over_resume ? al_map_rgb(179, 209, 255) : al_map_rgb(255, 255, 255);
        al_draw_text(Obj->font1, al_map_rgb(255, 255, 255), Obj->title_x + 125, Obj->title_y - 300, ALLEGRO_ALIGN_LEFT, "MENU");
        al_draw_text(Obj->font1, al_map_rgb(255, 255, 255), Obj->title_x + 200, Obj->title_y - 300, ALLEGRO_ALIGN_LEFT, "RESTART");
        al_draw_text(Obj->font1, resume_color, Obj->title_x + 300, Obj->title_y - 300, ALLEGRO_ALIGN_LEFT, "RESUME");
    }

    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Draw(ele);
    }
}
void game_scene_destroy(Scene *self)
{
    GameScene *Obj = ((GameScene *)(self->pDerivedObj));
    ALLEGRO_BITMAP *background = Obj->background;
    al_destroy_bitmap(background);
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
