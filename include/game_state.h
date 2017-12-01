#ifndef GAME_STATE_H
#define GAME_STATE_H


#include <SFML/Graphics.hpp>


class Application;


class Game_state{
public:
    Application *application;
    //double game_time;
    Game_state(Application *app);

    virtual void input(Application *app) = 0;
    virtual void input(const sf::Event &event) = 0;
    virtual void input() = 0;
    virtual void update(double dt, Application *app) = 0;
    virtual void draw(Application *app) = 0;
    //virtual void init() = 0;

    //sf::Texture *get_texture();
    //sf::Font *get_font();
    //sf::SoundBuffer *get_sound();
};
#endif // GAME_STATE_H
