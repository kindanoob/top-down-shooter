

#include "enemy_easy.h"


int Enemy_easy::enemy_easy_cnt = 0;



void Enemy_easy::create_animations(){
    //animation_manager().create("enemy_easy_default_movement", get_texture(), 0 * get_w(), 0 * get_h(), get_w(), get_h(), 4, 0.005, get_w());
    animation_manager().create("enemy_easy_default_movement", get_texture(), 0, 0, 32, 32, ENEMY_EASY_ANIMATION_FRAMES_COUNT, ENEMY_EASY_ANIMATION_SPEED, 32);
}
