#ifndef MINI_MAP_H
#define MINI_MAP_H

#include <SFML/Graphics.hpp>


class Mini_map{
public:
    Mini_map();
    sf::RectangleShape rect_shape_;
    sf::RectangleShape& rect_shape(){
        return rect_shape_;
    };

};
#endif // MINI_MAP_H
