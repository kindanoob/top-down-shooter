#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SFML/Graphics.hpp>
//#include <map>
#include "resource_manager.h"

enum class Texture_name{
    player_texture, enemy_easy_texture, enemy_medium_texture,
    bullet_texture, player_aim_texture, game_map_texture,
    //bullet_fire_texture
    //game_map_horizontal_texture,
    //game_map_vertical_texture, game_map_top_left_corner_texture,
    //game_map_top_right_corner_texture, game_map_bottom_left_corner_texture,
    //game_map_bottom_right_corner_texture
};

class Texture_manager: public Resource_manager<Texture_name, sf::Texture>{
public:
    Texture_manager();
    void add_game_map_textures();
};
#endif // TEXTURE_MANAGER_H
