#include <iostream>


#include "button.h"


Button::Button(const sf::Vector2f& rect_shape_size,
               const sf::Vector2f& rect_shape_position,
               const sf::Color& rect_shape_color,
               const double rect_shape_outline_thickness,
               const sf::Color& rect_shape_outline_color,
               const sf::Font& font,
               const std::string& button_text_string,
               const int text_character_size,
               const sf::Color& text_color){
               //rect_shape_size_(rect_shape_size), rect_shape_position_(rect_shape_position),
               //rect_shape_outline_color_(rect_shape_outline_color){
               //rect_shape_color_(rect_shape_color), rect_shape_outline_thickness_(rect_shape_outline_thickness),
    //rect_shape_.setOrigin(sf::Vector2f(button_rect.left + button_rect.width / 2, button_rect.top + button_rect.height / 2));
    rect_shape_.setSize(rect_shape_size);
    //auto button_rect = rect_shape().getGlobalBounds();
    auto button_rect = rect_shape().getLocalBounds();
    rect_shape_.setPosition(rect_shape_position);
    rect_shape_.setFillColor(rect_shape_color);

    //rect_shape_.setFillColor(sf::Color(255, 0, 0));
    rect_shape_.setOutlineThickness(rect_shape_outline_thickness);
    rect_shape_.setOutlineColor(rect_shape_outline_color);

    button_text_.setFont(font);
    button_text_.setCharacterSize(text_character_size);
    button_text_.setString(button_text_string);
    //auto text_rect = button_text().getGlobalBounds();
    auto text_rect = button_text().getLocalBounds();

    std::cout << "text rect, width: " << text_rect.width << ", height: " <<
    text_rect.height << std::endl;
    std::cout << "button rect, width: " << button_rect.width << ", height: " <<
    button_rect.height << std::endl;
    button_text_.setOrigin(sf::Vector2f(text_rect.width / 2, text_rect.height / 2));
    //button_text_.setOrigin(sf::Vector2f(10, 0));
    //button_text_.setPosition(rect_shape_position);
    //button_text_.setPosition(rect_shape_position);
    button_text_.setPosition(rect_shape_position + sf::Vector2f(button_rect.width / 2, button_rect.height / 2));
    button_text_.setColor(text_color);

}

