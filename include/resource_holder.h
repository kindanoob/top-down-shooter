#ifndef RESOURCE_HOLDER_H_
#define RESOURCE_HOLDER_H_

//#include "texture_manager.h"
//#include "font_manager.h"
//#include "sound_manager.h"

class Font_manager;
class Texture_manager;
class Sound_manager;
class Music_manager;


class Resource_holder {
public:
    Resource_holder();
    Texture_manager *textures;
    Font_manager *fonts;
    Sound_manager *sounds;
    Music_manager *music;
    //const sf::Texture& get_texture(Texture_name name) const;
    //const sf::Font& get_font(Font_name name) const;
    //const sf::SoundBuffer& get_sound_buffer(Sound_name name) const;
private:
    //Sound_manager sounds;
};

#endif // RESOURCE_HOLDER_H_
