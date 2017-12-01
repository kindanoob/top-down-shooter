


#include "bullet.h"
#include "config.h"
#include "util.h"


void Bullet::update(double dt){
    ++ticks_alive_;
    //std::cout << "current anim: " << animation_manager().current_animation << std::endl;
    //long long ticks = ticks_alive();
    //set_ticks_alive(++ticks);
    animation_manager().tick(dt);//update the current sprite
    if(alive_duration() < BULLET_FIRE_ANIMATION_DURATION_IN_MILLISECONDS){
        set_x(get_x());
        set_y(get_y());
    }
    else{
        set_x(get_x() + dt * get_dx());
        set_y(get_y() + dt * get_dy());
    }
    if((fabs(get_x() - get_player_x()) > SCREEN_DIAG) || (fabs(get_y() - get_player_y()) > SCREEN_DIAG)){
        set_is_alive(false);
        //std::cout << "bullet deleted" << std::endl;
        //return;
    }
    if((get_x() <= 0) || (get_x() >= MAP_WIDTH_IN_PIXELS) ||
       (get_y() <= 0) || (get_y() >= MAP_HEIGHT_IN_PIXELS)){
        set_is_alive(false);
    }
    get_sprite().setPosition(get_x(), get_y());
}


void Bullet::create_animations(){
    //animation_manager().create("bullet_default_animation", resource_holder -> textures().get_resource(Texture_name::bullet_texture), 0, 0, 4, 4, 1, 0.005, 4);
    //animation_manager().create("bullet_default_animation", resource_holder -> textures().get_resource(Texture_name::bullet_texture), 0, 0, 16, 16, 1, 0.005, 16);
    //animation_manager().create("bullet_fire_animation", resource_holder -> textures().get_resource(Texture_name::bullet_fire_texture), 0, 0, 32, 32, 1, 0.005, 32);
    //animation_manager().create("bullet_default_animation", get_texture(), 0, 0, 16, 16, 1, 0.005, 16);
    //animation_manager().create("bullet_fire_animation", get_texture(), 0, 0, 32, 32, 1, 0.005, 32);

    animation_manager().create("bullet_default_animation", get_texture(), 0, 24, 16, 16, 1, 0.005, 16);
    animation_manager().create("bullet_fire_animation", get_texture(), 0, 0, 24, 24, 1, 0.005, 24);
    //animation_manager().create("bullet_fire_animation", get_texture(), 0, 0, 64, 32, 1, 0.005, 64);

    //std::cout << "bullet animation created" << std::endl;
}


void Bullet::set_animation(const std::string& animation_name){
    animation_manager().set_animation(animation_name);
}

bool Bullet::check_collision_with_map(std::vector<std::vector<char> >& char_map){
    double x = get_x();
    double y = get_y() - INFO_RECT_SHAPE_HEIGHT;
    if(Util::pixel_outside_of_map(x, y)){
        set_is_alive(false);
        return true;
    }
    for(int i = (x - get_BB_w() / 2) / MAP_TILE_WIDTH_IN_PIXELS; i < (x + get_BB_w() / 2) / MAP_TILE_WIDTH_IN_PIXELS; ++i){
        for(int j = (y - get_BB_h() / 2) / MAP_TILE_HEIGHT_IN_PIXELS; j < (y + get_BB_h() / 2) / MAP_TILE_HEIGHT_IN_PIXELS; ++j){
            //std::cout << "bullet collision, i: " << i << ", j: " << j <<
            //", height: " << char_map.size() << ", width: " << char_map[0].size() << std::endl;
            char curr = char_map[j][i];
            if(Util::is_collision_obstacle(curr)){
                set_is_alive(false);
                return true;
            }
        }
    }
    return false;
}
