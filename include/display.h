#ifndef DISPLAY_H
#define DISPLAY_H


#include <SFML/Graphics.hpp>
#include "config.h"

class Application;
class Entity;


class Display{
public:
    //unsigned int width = 800;
    //unsigned int height = 600;
    //sf::String title = "Title yoyoyooooo.";
    sf::RenderWindow *window;
    sf::RenderWindow *initial_window;
    //void init(unsigned int width, unsigned int height, const sf::String &title);
    Display();
    ~Display();
    //void init();
    void clear(const sf::Color& clear_color);
    void draw(const sf::Drawable& drawable);
    void draw(Entity *e);
    void display();
    void check_window_events(Application *app);
    bool is_open();
    void destroy();
    bool is_fullscreen;
    void set_vertical_sync(bool b);
    sf::View view;
    void update_view(double offset_x, double offset_y);
    void view_reset_to_initial_state();
    void set_mouse_cursor_visible(bool visible){
        window -> setMouseCursorVisible(visible);
    }

};
#endif // DISPLAY_H
