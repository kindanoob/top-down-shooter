#ifndef FONT_MANAGER_H
#define FONT_MANAGER_H

#include <SFML/Graphics.hpp>
#include <map>
#include "resource_manager.h"

enum class Font_name{
    ubuntu_font, arial_font, cyrillic_font
};

class Font_manager: public Resource_manager<Font_name, sf::Font>{
public:
    Font_manager();
};


#endif // FONT_MANAGER_H
