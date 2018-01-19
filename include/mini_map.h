#ifndef MINI_MAP_H_
#define MINI_MAP_H_

#include <SFML/Graphics.hpp>


class Mini_map {
public:
    Mini_map();
    sf::RectangleShape rect_shape_;
    sf::RectangleShape& rect_shape() {
        return rect_shape_;
    };

};

#endif // MINI_MAP_H_
