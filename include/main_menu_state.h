#ifndef MAIN_MENU_H
#define MAIN_MENU_H


#include <SFML/Graphics.hpp>

#include "game_state.h"

class Application;
class Button;


class Main_menu_state: public Game_state{
public:
    Main_menu_state(Application *app);
    ~Main_menu_state();
    sf::Font font;
    sf::Text menu_text;
    sf::Text new_game_text;
    void create_menu_text(const sf::Font &font, const unsigned int text_size);
    void create_menu_font();
    void create_rect();
    sf::RectangleShape menu_rect;
    sf::RectangleShape new_game_button_rect;
    void input(const sf::Event &event);
    void input();
    void input(Application *app);
    void update(double dt, Application *app);
    void draw(Application *app);
    void init_entities();
    Button *new_game_button(){
        return new_game_button_;
    }
    Button *options_button(){
        return options_button_;
    }
    Button *exit_button(){
        return exit_button_;
    }
private:
    Button *new_game_button_;
    Button *options_button_;
    Button *exit_button_;
};

#endif // MAIN_MENU_H
