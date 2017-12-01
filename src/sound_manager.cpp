
#include <iostream>

#include "sound_manager.h"
#include "config.h"


Sound_manager::Sound_manager(){
    std::cout << "Sound_manager()" << std::endl;
    add_player_sounds();
}

Sound_manager::~Sound_manager(){
    std::cout << "~Sound_manager()" << std::endl;
}



void Sound_manager::add_player_sounds(){
    add_resource(Sound_name::player_shoot_sound, SOUNDS_PATH + "sound.wav");
}
