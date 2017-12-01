


#include "enemy_mediuim.h"



int Enemy_medium::enemy_medium_cnt = 0;


void Enemy_medium::create_animations(){
    animation_manager().create("enemy_medium_default_movement", get_texture(), 0 * get_w(), 0 * get_h(), get_w(), get_h(), 4, ENEMY_MEDIUM_ANIMATION_SPEED, get_w());
}
