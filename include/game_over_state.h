#ifndef GAME_OVER_H
#define GAME_OVER_H

#include <SFML/Graphics.hpp>

#include "game_state.h"

class Application;



class Game_over_state: public Game_state{
public:
    Game_over_state(Application *app);
    ~Game_over_state();
    sf::Font font;
    sf::Text game_over_text;
    sf::Text score_text;
    sf::Text press_any_key_text;
    void create_game_over_text(const sf::Font &font, const unsigned int text_size);
    void create_score_text(const sf::Font &font, const unsigned int text_size);
    void create_press_any_key_text(const sf::Font &font, const unsigned int text_size);
    void create_game_over_font();
    sf::RectangleShape field_rect;
    void input(const sf::Event &event);
    void input();
    void input(Application *app);
    void update(double dt, Application *app);
    void draw(Application *app);
    void init_entities();
};
#endif // GAME_OVER_H
