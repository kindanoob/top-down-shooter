#ifndef TEXTURE_MANAGER_H_
#define TEXTURE_MANAGER_H_

#include <SFML/Graphics.hpp>
#include "resource_manager.h"

enum class Texture_name {
    player_texture, 
    enemy_easy_texture, 
    enemy_medium_texture,
    bullet_texture, 
    player_aim_texture, 
    game_map_texture,
};


class Texture_manager: public Resource_manager<Texture_name, sf::Texture> {
public:
    Texture_manager();
    void add_game_map_textures();
};


#endif // TEXTURE_MANAGER_H_
