#include "gamescene.h"
#include "../global.h"
/*
   [GameScene function]
*/

double paused_time = 0;

Scene *New_GameScene(int label)
{
    start_time = al_get_time();
    

    GameScene *pDerivedObj = (GameScene *)malloc(sizeof(GameScene));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->font1 = al_load_ttf_font("assets/font/DIN Condensed Bold.ttf", 28, 0);
    pDerivedObj->background = al_load_bitmap("assets/image/stage.jpg");
    pObj->pDerivedObj = pDerivedObj;

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
    _Register_elements(pObj, New_Box(Box_L));
    // setting derived object function
    pObj->Update = game_scene_update;
    pObj->Draw = game_scene_draw;
    pObj->Destroy = game_scene_destroy;
    return pObj;
}
void game_scene_update(Scene *self)
{
    
    ElementVec allEle = _Get_all_elements(self);

    if (!key_state[ALLEGRO_KEY_ENTER]){
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
    al_draw_text(Obj->font1, al_map_rgb(255, 255, 255), Obj->title_x - 400, Obj->title_y - 300, ALLEGRO_ALIGN_LEFT, "TIME");
    double current_time = al_get_time();
    int elapsed_seconds = (int)(current_time - start_time);
    char time_str[10];
    format_time(elapsed_seconds, time_str, sizeof(time_str));
    al_draw_text(Obj->font1, al_map_rgb(255, 255, 255), Obj->title_x - 350, Obj->title_y - 300, ALLEGRO_ALIGN_LEFT, time_str);

    al_draw_text(Obj->font1, al_map_rgb(255, 255, 255), Obj->title_x - 275, Obj->title_y - 300, ALLEGRO_ALIGN_LEFT, "SCORE");

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
