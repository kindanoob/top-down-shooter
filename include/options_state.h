#ifndef OPTIONS_STATE_H
#define OPTIONS_STATE_H

#include <SFML/Graphics.hpp>

#include "game_state.h"
#include "button.h"



class Application;


class Options_state: public Game_state{
public:
    Options_state(Application *app);
    ~Options_state();
    virtual void input(Application *app);
    virtual void input(const sf::Event &event);
    virtual void input();
    virtual void update(double dt, Application *app);
    virtual void draw(Application *app);

    //void init_entities(Application *app);
    void create_entities(Application *app);
    void create_back_button(Application *app);
    void draw_entities();
    sf::RenderWindow *window(){
        return window_;
    }
    Button *back_button(){
        return back_button_;
    }
private:
    sf::RenderWindow *window_;
    Button *back_button_;
};
#endif // OPTIONS_STATE_H
