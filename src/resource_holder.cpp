#include <iostream>

#include "resource_holder.h"
#include "texture_manager.h"
#include "font_manager.h"
#include "sound_manager.h"
#include "music_manager.h"

/*
const Resource_holder& Resource_holder::get(){
    static Resource_holder holder;
    return holder;
};
*/


Resource_holder::Resource_holder(){
    std::cout << "Resource_holder()" << std::endl;
    textures = new Texture_manager();
    fonts = new Font_manager();
    sounds = new Sound_manager();
    music = new Music_manager();
}



//const sf::SoundBuffer& Resource_holder::get_sound_buffer(Sound_name name) const{
    //sounds.get_resource(name);
//};
