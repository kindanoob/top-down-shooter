

#include "config.h"
#include "font_manager.h"


Font_manager::Font_manager(){
    add_resource(Font_name::arial_font, FONTS_PATH + "arial.ttf");
    add_resource(Font_name::ubuntu_font, FONTS_PATH + "ubuntu.ttf");
    add_resource(Font_name::cyrillic_font, FONTS_PATH + "cyrillic.ttf");
}
