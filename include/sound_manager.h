#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "resource_manager.h"

enum class Sound_name{
    player_shoot_sound, player_died_sound, enemy_easy_died_sound,
    enemy_medium_died_sound
};


class Sound_manager: public Resource_manager<Sound_name, sf::SoundBuffer>{
public:
    Sound_manager();
    ~Sound_manager();
    void add_player_sounds();
};
#endif // SOUND_MANAGER_H
