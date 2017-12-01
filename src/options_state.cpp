#include <iostream>



#include "application.h"
#include "display.h"
#include "options_state.h"
#include "play_state.h"
#include "button.h"
#include "resource_holder.h"
#include "font_manager.h"



Options_state::Options_state(Application *app): Game_state(app){
    std::cout << "Options_state()" << std::endl;
    window_ = new sf::RenderWindow(sf::VideoMode(OPTIONS_WINDOW_WIDTH, OPTIONS_WINDOW_HEIGHT), "Options");
    create_entities(app);

}

Options_state::~Options_state(){
    std::cout << "~Options_state()" << std::endl;
}

//void Options_state::init_entities(Application *app){
    //create_options_font();
    //create_back_button(app -> resource_holder -> fonts -> get_resource(Font_name::ubuntu_font), OPTIONS_STATE_TEXT_SIZE);
    //create_back_button();
//}

void Options_state::input(Application *app){
    //std::cout << "in input" << std::endl;
    while(window_ -> isOpen()){
        //std::cout << "in isOpen(), " << rand() << std::endl;
        sf::Event e;
        while(window_ -> pollEvent(e)){
            //std::cout << "in pollEvent()" << std::endl;
            if(e.type == sf::Event::Closed){
                window_ -> close();
                //app -> change_state(app -> main_menu_state);
                app -> pop_state();
                delete(this);
            }
        }
        back_button() -> set_rect_shape_fill_color(sf::Color(255, 255, 255));
        auto mouse_position = window_ -> mapPixelToCoords(sf::Mouse::getPosition(*(window_)));
        if(back_button() -> rect_shape().getGlobalBounds().contains(mouse_position)){
            //if(new_game_button.getLocalBounds().contains(mouse_position)){
            //std::cout << "intersect" << std::endl;
            back_button() -> set_rect_shape_fill_color(MENU_BUTTON_ON_SELECT_COLOR);
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                //std::cout << "mouse pressed" << std::endl;
                //Play_state *new_play_state = new Play_state(app);
                //application -> push_state(new_play_state);
                //new_play_state -> init(app);
                window() -> close();
                app -> pop_state();
            }
        }
        window_ -> clear(sf::Color(255, 255, 255));
        draw_entities();
        window_ -> display();
    }
};
void Options_state::input(const sf::Event &event){};
void Options_state::input(){};
void Options_state::update(double dt, Application *app){};
void Options_state::draw(Application *app){
    //app -> display -> draw(back_button_ -> rect_shape());
    //app -> display -> draw(back_button_ -> button_text());
    window_ -> draw(back_button_ -> rect_shape());
    window_ -> draw(back_button_ -> button_text());
    //window_ -> clear(sf::Color::Yellow);
    std::cout << "in draw" << std::endl;
}

void Options_state::create_entities(Application *app){
    create_back_button(app);
}

void Options_state::create_back_button(Application *app){
    std::cout << "back_button created" << std::endl;
    back_button_ = new Button(sf::Vector2f(80, 40),
                              sf::Vector2f(400, 325),
                              sf::Color(255, 255, 255),
                              3,
                              sf::Color(0, 0, 0),
                              app -> resource_holder -> fonts -> get_resource(Font_name::ubuntu_font),
                              "back",
                              20,
                              sf::Color(0, 0, 0)
                              );
}

void Options_state::draw_entities(){
    window_ -> draw(back_button_ -> rect_shape());
    window_ -> draw(back_button_ -> button_text());
}
