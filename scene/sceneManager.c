#include "sceneManager.h"
#include "menu.h"
#include "gamescene.h"
#include "level.h"
Scene *scene = NULL;
void create_scene(SceneType type)
{
    switch (type)
    {
    case Menu_L:
        scene = New_Menu(Menu_L);
        break;
    case GameScene_L:
        scene = New_GameScene(GameScene_L);
        break;
    case Level_L:
        scene = New_Level(Level_L);
        break;
    default:
        break;
    }
}