#include <iostream>

#include "config.h"
#include "texture_manager.h"


Texture_manager::Texture_manager(){
    std::cout << "Texture_manager()" << std::endl;
    add_resource(Texture_name::player_texture, TEXTURES_PATH + "circle_pistol_right1.png");
    //add_resource(Texture_name::player_texture, TEXTURES_PATH + "circle_gun_right.png");
    //add_resource(Texture_name::player_texture, TEXTURES_PATH + "circle_weapon_2gun_right.png");
    //add_resource(Texture_name::player_texture, TEXTURES_PATH + "circle_weapon_2pistol_right.png");
    add_resource(Texture_name::enemy_easy_texture, TEXTURES_PATH + "circle_animation_yellow_transparent.png");
    add_resource(Texture_name::enemy_medium_texture, TEXTURES_PATH + "circle_animation_blue_transparent.png");
    //add_resource(Texture_name::bullet_texture, TEXTURES_PATH + "bullet_4_by_4.png");
    //add_resource(Texture_name::bullet_texture, TEXTURES_PATH + "bullet_16_by_16_black.png");
    //add_resource(Texture_name::bullet_fire_texture, TEXTURES_PATH + "bullet_fire_32_by_32_orange.png");
    add_resource(Texture_name::bullet_texture, TEXTURES_PATH + "bullet_default_and_fire14.png");
    //add_resource(Texture_name::bullet_texture, TEXTURES_PATH + "bullet_default_and_fire_long.png");

    //add_resource(Texture_name::player_aim_texture, TEXTURES_PATH + "aim8.png");
    add_resource(Texture_name::player_aim_texture, TEXTURES_PATH + "aim_large10.png");
    //add_resource(Texture_name::player_aim_texture, TEXTURES_PATH + "aim_large15.png");
    add_game_map_textures();
}


void Texture_manager::add_game_map_textures(){
    add_resource(Texture_name::game_map_texture, TEXTURES_PATH + "top_down_shooter_tileset6.png");
    /*
    add_resource(Texture_name::game_map_horizontal_texture, TEXTURES_PATH + "");
    add_resource(Texture_name::game_map_vertical_texture, TEXTURES_PATH + "");
    add_resource(Texture_name::game_map_top_left_corner_texture, TEXTURES_PATH + "");
    add_resource(Texture_name::game_map_top_right_corner_texture, TEXTURES_PATH + "");
    add_resource(Texture_name::game_map_bottom_left_corner_texture, TEXTURES_PATH + "");
    add_resource(Texture_name::game_map_bottom_right_corner_texture, TEXTURES_PATH + "");
    */
}
