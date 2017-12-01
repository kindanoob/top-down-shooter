#include <iostream>
#include <new>

#include "display.h"
#include "application.h"
#include "entity.h"


Display::Display(){
    std::cout << "Display()" << std::endl;
    sf::ContextSettings settings;
    settings.antialiasingLevel = ANTIALIASING_LEVEL;
    window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), SCREEN_TITLE, sf::Style::Default, settings);
    std::cout << "screen width: " << SCREEN_WIDTH << ", height: " << SCREEN_HEIGHT << std::endl;
    is_fullscreen = false;
    set_vertical_sync(true);

    //window -> setFramerateLimit(FRAME_RATE_LIMIT);
    view.setCenter(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
    view.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
    window -> setView(view);
    //initial_window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), SCREEN_TITLE, sf::Style::Default, settings);
}

Display::~Display(){
    std::cout << "~Display()" << std::endl;
}

//void Display::init(){
    //std::cout << "in Display constructor" << std::endl;
    //window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), SCREEN_TITLE, sf::Style::Default);
    //window = new sf::RenderWindow(sf::VideoMode(800, 600), "LOL", sf::Style::Default);
//};

void Display::clear(const sf::Color& clear_color){
    //window -> clear(sf::Color::White);
    window -> clear(clear_color);
};

void Display::draw(const sf::Drawable& drawable){
    window -> draw(drawable);
}

void Display::draw(Entity *e){
    e -> animation_manager().draw(*window, e);
}

void Display::display(){
    window -> display();
};

void Display::check_window_events(Application *app){
    sf::Event event;
    while(window -> pollEvent(event)){
        if(event.type == sf::Event::Closed){
            window -> close();
            //destroy();
            //return;
        }
    }
};

bool Display::is_open(){
    return window -> isOpen();
};


void Display::destroy(){
    delete this;
}


void Display::set_vertical_sync(bool b){
    window -> setVerticalSyncEnabled(b);
}


//void Display::update_view(double player_x, double player_y, offset_x, double offset_y){
void Display::update_view(double offset_x, double offset_y){
    view.setCenter(sf::Vector2f(SCREEN_WIDTH / 2 + 0 * offset_x, 0 * offset_y + SCREEN_HEIGHT / 2));
    view.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
    view.move(sf::Vector2f(offset_x, offset_y));
    window -> setView(view);
    //std::cout << "update view, offset x: " << offset_x << ", offset y: " <<
    //offset_y << std::endl;
}


void Display::view_reset_to_initial_state(){
    view.setCenter(VIEW_INITIAL_CENTER);
    view.setSize(VIEW_INITIAL_SIZE);
    window -> setView(view);
}
