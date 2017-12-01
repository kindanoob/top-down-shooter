


#include "mini_map.h"
#include "config.h"

Mini_map::Mini_map(){
    rect_shape().setSize(sf::Vector2f(MINI_MAP_WIDTH_IN_PIXELS, MINI_MAP_HEIGHT_IN_PIXELS));
    rect_shape().setOrigin(MINI_MAP_WIDTH_IN_PIXELS / 2, MINI_MAP_HEIGHT_IN_PIXELS / 2);
    //rect_shape().setPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2) + sf::Vector2f(player -> get_offset_x(), player -> get_offset_y()));
    rect_shape().setFillColor(sf::Color(255, 255, 255, 0));
    rect_shape().setOutlineThickness(MINI_MAP_OUTLINE_THICKNESS);
    rect_shape().setOutlineColor(MINI_MAP_OUTLINE_COLOR);
}
