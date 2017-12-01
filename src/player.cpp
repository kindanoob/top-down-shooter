#include <iostream>



#include "application.h"
#include "display.h"
#include "enemy.h"
#include "player.h"
#include "config.h"
#include "util.h"




void Player::get_input_from_player(sf::RenderWindow *window){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        set_dy(-PLAYER_DY);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        set_dy(PLAYER_DY);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        set_dx(-PLAYER_DX);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        set_dx(PLAYER_DX);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::K)){//kills the player
        set_is_alive(false);
    }
    //sf::Vector2i mouse_pos = sf::Mouse::getPosition(*window);
    sf::Vector2i mouse_pos = get_mouse_world_position();
    sf::Vector2f pos = get_sprite().getPosition();
    //std::cout << "pos x: " << pos.x << ", y: " << pos.y << ", mouse pos x: " <<
    //mouse_pos.x << ", y: " << mouse_pos.y << std::endl;

    double x = mouse_pos.x - pos.x;
    double y = mouse_pos.y - pos.y;

    int temp_angle = atan2(y, x) / PI * 180;
    if(temp_angle < 0){
        temp_angle += 360;
    }
    set_mouse_angle(temp_angle);
}


void Player::update(double dt){
    //std::cout << "in update() x: " << get_x() << ", y: " << get_y() << std::endl;

    //std::cout << "x: " << get_x() << ", y: " << get_y() << ", gun x: " <<
    //get_gun_x() << ", gun y: " << get_gun_y() << std::endl;
    //test_sound.play();
    //shoot_sound().play();
    //std::cout << "dx: " << get_dx() << ", dy: " << get_dy() << std::endl;

    update_aim_sprite();
    animation_manager().tick(dt);//update the current sprite
    get_sprite().setOrigin(get_origin_x(), get_origin_y());
    set_x(get_x() + dt * get_dx());
    set_y(get_y() + dt * get_dy());
    get_sprite().setPosition(sf::Vector2f(get_x(), get_y()));


    //set_center_x(get_center_x() + dt * get_dx());
    //set_center_y(get_center_y() + dt * get_dy());
    set_center_x(get_x() + dt * get_dx());
    set_center_y(get_y() + dt * get_dy());
    //std::cout << "in update() x: " << get_x() << ", y: " << get_y() << std::endl;//", center x: " <<
    //get_center_x() << ", center y: " << get_center_y() << std::endl;

    double angle_diff = get_mouse_angle() - get_sprite().getRotation();
    set_angle(angle_diff);
    get_sprite().rotate(angle_diff);
    //std::cout << "mouse angle: " << get_mouse_angle() << std::endl;
    //std::cout << "sprite angle: " << get_sprite().getRotation() << ", mouse angle: " <<
    //get_mouse_angle() << ", diff: " << angle_diff << ", rotate by: " <<
    //angle_diff * dt << ", dt: " << dt << std::endl;
    if(abs(angle_diff) > 0){
        //get_sprite().rotate(angle_diff * dt);
    }
    set_gun_x(get_center_x() + DIST_FROM_GUN_TO_PLAYER_CENTER * cos(get_sprite().getRotation() / 180.0 * PI));
    set_gun_y(get_center_y() + DIST_FROM_GUN_TO_PLAYER_CENTER * sin(get_sprite().getRotation() / 180.0 * PI));
    //std::cout << "player x: " << get_x() << ", y: " << get_y() << std::endl;
    //std::cout << "player x: " << get_x() << ", y: " << get_y() << ", center_x: " <<
    //get_center_x() << ", center_y: " << get_center_y() << ", gun_x: " <<
    //get_gun_x() << ", gun_y: " << get_gun_y() << std::endl;


    if(get_invul_duration() > 0){
        set_invul_duration(get_invul_duration() - dt);
        if(get_invul_duration() < 0){
            set_invul_duration(0);
        }
    }
}


bool Player::check_collision_with_enemy(Enemy *e){
    if(!get_is_alive()){
        return false;
    }
    double d = Util::dist(get_x(), get_y(), e -> get_x(), e -> get_y());
    if(d < 16 + 16){
        if(get_invul_duration() == 0){
            set_health(get_health() - e -> get_damage());
            if(get_health() <= 0){
                set_is_alive(false);
                return false;
            }
            set_invul_duration(PLAYER_INVUL_DURATION);
        }
    }
    double dsq = Util::dist_squared(get_center_x(), get_center_y(), e -> get_x(), e -> get_y());
    double sum_radius = 16 + 16;
    double cutoff = sum_radius * sum_radius;
    if(dsq >= cutoff){
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
        //found_collision = true;
    }
    if((new_enemy_y > INFO_RECT_SHAPE_HEIGHT + 16 + 32) && (new_enemy_y < INFO_RECT_SHAPE_HEIGHT + MAP_HEIGHT_IN_PIXELS - 16 - 32)){
        e -> set_y(new_enemy_y);
        //found_collision = true;
    }
    //return found_collision;
    //e -> set_x(new_enemy_x);
    //e -> set_y(new_enemy_y);
    return  true;

    //set_x(get_x() - v_x);
    //set_y(get_y() - v_y);
}

void Player::create_animations(){
    animation_manager().create("player_default_animation", get_texture(), 0 * get_w(), 0 * get_h(), get_w(), get_h(), 1, 0.005, get_w());
    //animation_manager().create("player_aim_animation", get_aim_texture(), 0, 0, 16, 16, 1, 0.005, 16);
}


void Player::update_aim_sprite(){
    get_aim_sprite().setPosition(static_cast<sf::Vector2f>(get_mouse_world_position()));
    auto r = get_aim_sprite().getPosition();
    //std::cout << "aim pos, x: " << r.x << ", y: " << r.y << ", mouse pos, x: " <<
    //get_mouse_pos().x << ", y: " << get_mouse_pos().y << std::endl;
}


void Player::update_mouse_world_position(Application *app){
    //sf::Vector2i mouse_world_coord = app -> display -> window -> mapCoordsToPixel(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*(app -> display -> window))), app -> display -> view);
    ///sf::Vector2i mouse_world_coord = app -> display -> window -> mapCoordsToPixel(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*(app -> display -> window))));
    //sf::Vector2f temp = app -> display -> window -> mapPixelToCoords(static_cast<sf::Vector2i>(sf::Mouse::getPosition(*(app -> display -> window))));
    //sf::Vector2i mouse_world_coord = static_cast<sf::Vector2i>(temp);
    ///mouse_world_coord.x %= SCREEN_WIDTH;
    ///mouse_world_coord.y %= SCREEN_HEIGHT;
    ///set_mouse_pos(mouse_world_coord);
    //std::cout << "world pos, x: " << mouse_world_coord.x << ", y: " <<
    //mouse_world_coord.y << ", x: " << get_x() << ", y: " << get_y() << std::endl;
    auto r = sf::Mouse::getPosition(*(app -> display -> window));

    /*
    if((get_offset_x() < EPSILON) && (get_offset_y() < EPSILON)){
        //
    }
    else if(get_offset_x() < EPSILON){
        r.y += get_offset_y();
    }
    else if(get_offset_y() < EPSILON){
        r.x += get_offset_x();
    }
    else{
        r.x += get_offset_x();
        r.y += get_offset_y();
    }
    */

    auto ptoc = app -> display -> window -> mapPixelToCoords(r);
    set_mouse_world_position(static_cast<sf::Vector2i>(ptoc));
    //auto ctop = app -> display -> window -> mapCoordsToPixel(static_cast<sf::Vector2f>(r));
    //std::cout << "mouse pos, x: " << r.x << ", y: " << r.y << std::endl;
    //std::cout << "ptoc, pos, x: " << ptoc.x << ", y: " << ptoc.y << std::endl;
    //std::cout << "ctop, pos, x: " << ctop.x << ", y: " << ctop.y << std::endl;
    //auto v = app -> display -> window -> getView();
    //auto vr = v.getSize();
    //std::cout << "view, x: " << vr.x << ", y: " << vr.y << std::endl;
    //auto f = v.getViewport();
    //std::cout << "viewport, left: " << f.left << ", top: " << f.top <<
    //", width: " << f.width << ", height: " << f.height << std::endl;
    //auto vc = v.getCenter();
    //std::cout << "view center, x: " << vc.x << ", y: " << vc.y << std::endl;
}
