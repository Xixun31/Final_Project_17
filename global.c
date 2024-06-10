#include "global.h"
#include "shapes/Shape.h"
#include <stdbool.h>
// variables for global usage
const double FPS = 60.0;
const int WIDTH = 900;
const int HEIGHT = 672;
int window = 0;
int level = 0;
int final_score = 0;
double start_time;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_EVENT event;
ALLEGRO_TIMER *fps = NULL;
bool key_state[ALLEGRO_KEY_MAX] = {false};
bool mouse_state[ALLEGRO_MOUSE_MAX_EXTRA_AXES] = {false};
Point mouse;
bool debug_mode = true;
double GAME_START_TIME = 0;
double GAME_CURRENT_TIME = 0;
double GAME_PAUSE_TIME = 0;
double GAME_TEMPORARY_TIME = 0;
int box_exist = 0, ball_exist = 0;
bool GAME_WIN = false, GAME_LOSE = false;
int change_l = 0, change_s = 0, change_r = 0;
int box_delete = 0;
double NEXTTIME = 13;