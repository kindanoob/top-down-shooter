
#include <iostream>

#include "music_manager.h"
#include "config.h"


Music_manager::Music_manager(){
    std::cout << "Music_manager()" << std::endl;
    add_play_state_music();
}

Music_manager::~Music_manager(){
    std::cout << "~Music_manager()" << std::endl;
}



void Music_manager::add_play_state_music(){
    if(!play_state_music_.openFromFile(MUSIC_PATH + "music.ogg")){
        std::cout << "Error. Failed to open music file." << std::endl;
    }
    play_state_music_.setVolume(PLAY_STATE_VOLUME_LEVEL);
}



