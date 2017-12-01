#include <iostream>


#include "player.h"
#include "enemy.h"
#include "config.h"
#include "util.h"


int Enemy::cnt = 0;//initialize number of enemies with 0


void Enemy::update(double dt){
    animation_manager().tick(dt);//update the current sprite
    get_sprite().setOrigin(get_origin_x(), get_origin_y());


    double angle = get_sprite().getRotation();
    double player_angle = get_player_angle();
    double angle_diff = player_angle - angle;
    if(angle_diff > 180){
        angle_diff -= 360;
    }
    if(fabs(angle_diff) > EPSILON){
        get_sprite().rotate(angle_diff);
    }


    set_dx(get_dx_base() * cos(player_angle / 180.0 * PI));
    set_dy(get_dx_base() * sin(player_angle / 180.0 * PI));
    //set_dx(0);
    //set_dy(-0.02);
    set_x(get_x() + dt * get_dx());
    set_y(get_y() + dt * get_dy());
    get_sprite().setPosition(sf::Vector2f(get_x(), get_y()));
    //std::cout << "x: " << get_x() << ", y: " << get_y() << std::endl;



    //set_angle(angle_diff);
    //std::cout << "angle: " << angle << ", player angle: " << get_player_angle() <<
    //", diff: " << angle_diff << ", dt: " << dt << std::endl;

    //std::cout << "angle: " << player_angle << ", dx: " << get_dx() << ", dy: " << get_dy() << std::endl;
}


bool Enemy::check_collision_with_enemy(Enemy *e){
    if(!get_is_alive()){
        return false;
    }
    double dsq = Util::dist_squared(get_x(), get_y(), e -> get_x(), e -> get_y());
    double sum_radius = 16 + 16;
    double cutoff = sum_radius * sum_radius;
    //std::cout << "dsq: " << dsq << ", cutoff: " << cutoff << std::endl;
    if(dsq >= cutoff){
        //std::cout << "returned false" << std::endl;
        return false;
    }
    double shift = 16 + 16 - Util::dist(get_x(), get_y(), e -> get_x(), e -> get_y());
    double v_x = -get_x() + e -> get_x();
    double v_y = -get_y() + e -> get_y();
    double len = Util::length(v_x, v_y);
    v_x /= len;
    v_y /= len;
    //shift /= 2;
    v_x *= shift;
    v_y *= shift;
    double new_enemy_x = e -> get_x() + v_x;
    double new_enemy_y = e -> get_y() + v_y;
    //bool found_collision = false;
    if((new_enemy_x > 16 + 32) && (new_enemy_x < MAP_WIDTH_IN_PIXELS - 16 - 32)){
        e -> set_x(new_enemy_x);
        //set_x(get_x() - v_x);
        //found_collision = true;
    }
    if((new_enemy_y > INFO_RECT_SHAPE_HEIGHT + 16 + 32) && (new_enemy_y < INFO_RECT_SHAPE_HEIGHT + MAP_HEIGHT_IN_PIXELS - 16 - 32)){
        e -> set_y(new_enemy_y);
        //set_y(get_y() - v_y);
        //found_collision = true;
    }
    //e -> set_x(new_enemy_x);
    //e -> set_y(new_enemy_y);
    //return found_collision;
    return true;
}


bool Enemy::check_collision_with_player(Player *p){
    if(!get_is_alive()){
        return false;
    }
    double dsq = Util::dist_squared(get_x(), get_y(), p -> get_x(), p -> get_y());
    double sum_radius = 16 + 16;
    double cutoff = sum_radius * sum_radius;
    if(dsq + EPSILON >= cutoff){
        return false;
    }
    double shift = 16 + 16 - Util::dist(get_x(), get_y(), p -> get_x(), p -> get_y());
    double v_x = -get_x() + p -> get_x();
    double v_y = -get_y() + p -> get_y();
    double len = Util::length(v_x, v_y);
    v_x /= len;
    v_y /= len;
    //shift /= 2;
    v_x *= shift;
    v_y *= shift;
    double new_player_x = p -> get_x() + v_x;
    double new_player_y = p -> get_y() + v_y;
    bool found_collision = false;
    if((new_player_x > 16 + 32) && (new_player_x < MAP_WIDTH_IN_PIXELS - 16 - 32)){
        //p -> set_x(new_player_x);
        //set_x(get_x() - v_x);
        //found_collision = true;
    }
    if((new_player_y > INFO_RECT_SHAPE_HEIGHT + 16 + 32) && (new_player_y < INFO_RECT_SHAPE_HEIGHT + MAP_HEIGHT_IN_PIXELS - 16 - 32)){
        //p -> set_y(new_player_y);
        //set_y(get_y() - v_y);
        //found_collision = true;
    }
    p -> set_x(new_player_x);
    p -> set_y(new_player_y);
    //return found_collision;
    return true;
    //set_x(get_x() - v_x);
    //set_y(get_y() - v_y);
}



