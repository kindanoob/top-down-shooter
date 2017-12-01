
#include <iostream>
#include <sstream>

#include "application.h"
#include "display.h"
#include "main_menu_state.h"
#include "play_state.h"
#include "options_state.h"
#include "button.h"


Main_menu_state::Main_menu_state(Application *app): Game_state(app){
    init_entities();
    std::cout << "Main_menu_state()" << std::endl;
}


Main_menu_state::~Main_menu_state(){
    std::cout << "~Main_menu_state()" << std::endl;
}


void Main_menu_state::create_menu_font(){
    if(!font.loadFromFile(FONTS_PATH + "ubuntu.ttf")){
        std::cout << "Error. Create_menu_font failed to load." << std::endl;
    }
    else{
        std::cout << "Create_menu_font loaded successfully." << std::endl;
    }
}


void Main_menu_state::create_menu_text(const sf::Font &font, const unsigned int text_size){
    new_game_button_ = new Button(MENU_BUTTON_SIZE,
                                  MENU_NEW_GAME_BUTTON_POSITION,
                                  MENU_BUTTON_COLOR,
                                  MENU_BUTTON_OUTLINE_THICKNESS,
                                  MENU_BUTTON_OUTLINE_COLOR,
                                  font,
                                  "New game",
                                  MENU_CHARACTER_SIZE,
                                  MENU_TEXT_COLOR);


    options_button_ = new Button(MENU_BUTTON_SIZE,
                                  MENU_OPTIONS_BUTTON_POSITION,
                                  MENU_BUTTON_COLOR,
                                  MENU_BUTTON_OUTLINE_THICKNESS,
                                  MENU_BUTTON_OUTLINE_COLOR,
                                  font,
                                  "Options",
                                  MENU_CHARACTER_SIZE,
                                  MENU_TEXT_COLOR);

    exit_button_ = new Button(MENU_BUTTON_SIZE,
                                  MENU_EXIT_BUTTON_POSITION,
                                  MENU_BUTTON_COLOR,
                                  MENU_BUTTON_OUTLINE_THICKNESS,
                                  MENU_BUTTON_OUTLINE_COLOR,
                                  font,
                                  "Exit",
                                  MENU_CHARACTER_SIZE,
                                  MENU_TEXT_COLOR);
}


void Main_menu_state::input(Application *app){
    sf::Event event;
    while(app -> display -> window -> pollEvent(event)){
        if(event.type == sf::Event::Closed){
            app -> display -> window -> close();
        }
    }
    new_game_button() -> rect_shape().setFillColor(MENU_BUTTON_DEFAULT_COLOR);
    exit_button() -> set_rect_shape_fill_color(MENU_BUTTON_DEFAULT_COLOR);
    options_button() -> set_rect_shape_fill_color(MENU_BUTTON_DEFAULT_COLOR);

    auto mouse_position = application -> display -> window -> mapPixelToCoords(sf::Mouse::getPosition(*(application -> display -> window)));
    //auto mouse_position = application -> get_mouse_pos();
    //auto rect = new_game_button_rect.getGlobalBounds();
    //std::cout << "QQ, left: " << rect.left << ", top: " <<
    //rect.top << ", width: " << rect.width << ", height: " << rect.height << std::endl;
    //std::cout << "WW, x: " << new_game_button_rect.getSize().x << ", y: " <<
    //new_game_button_rect.getSize().y << std::endl;
    if(new_game_button() -> rect_shape().getGlobalBounds().contains(mouse_position)){
    //if(new_game_button.getLocalBounds().contains(mouse_position)){
        //std::cout << "intersect" << std::endl;
        new_game_button() -> set_rect_shape_fill_color(MENU_BUTTON_ON_SELECT_COLOR);
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            //std::cout << "mouse pressed" << std::endl;
            std::cout << "before Play_state()" << std::endl;
            Play_state *new_play_state = new Play_state(app);
            std::cout << "after Play_state()" << std::endl;
            application -> push_state(new_play_state);
            new_play_state -> init(app);
        }
    }
    else if(options_button() -> rect_shape().getGlobalBounds().contains(mouse_position)){
    //if(new_game_button.getLocalBounds().contains(mouse_position)){
        //std::cout << "intersect" << std::endl;
        options_button() -> set_rect_shape_fill_color(MENU_BUTTON_ON_SELECT_COLOR);
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            //std::cout << "options button pressed" << std::endl;
            Options_state* new_options_state = new Options_state(app);
            application -> push_state(new_options_state);
            //application -> push_state(app -> options_state);
            //std::cout << "options state " << new_options_state <<
            //" was pushed onto the stack" << std::endl;
            //new_options_state -> init(app);
        }
    }
    else if(exit_button() -> rect_shape().getGlobalBounds().contains(mouse_position)){
    //if(new_game_button.getLocalBounds().contains(mouse_position)){
        //std::cout << "intersect" << std::endl;
        exit_button() -> set_rect_shape_fill_color(MENU_BUTTON_ON_SELECT_COLOR);
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            //std::cout << "exit button pressed" << std::endl;
            app -> display -> window -> close();
            //Play_state *new_play_state = new Play_state(app);
            //application -> push_state(new_play_state);
            //new_play_state -> init(app);
        }
    }
}



void Main_menu_state::input(const sf::Event &event){}

void Main_menu_state::input(){}

void Main_menu_state::update(double dt, Application *app){}


void Main_menu_state::draw(Application *app){
    app -> display -> clear(MAIN_MENU_STATE_BACKGROUND_COLOR);
    app -> display -> draw(new_game_button() -> rect_shape());
    app -> display -> draw(new_game_button() -> button_text());

    app -> display -> draw(options_button() -> rect_shape());
    app -> display -> draw(options_button() -> button_text());

    app -> display -> draw(exit_button() -> rect_shape());
    app -> display -> draw(exit_button() -> button_text());
    //application -> display -> draw(new_game_button_rect);
    //app -> display -> draw(new_game_text);
}

void Main_menu_state::init_entities(){
    create_menu_font();
    create_menu_text(font, MENU_TEXT_SIZE);
    create_rect();
}


void Main_menu_state::create_rect(){
    menu_rect.setSize(sf::Vector2f(200, 75));
    menu_rect.setFillColor(sf::Color::White);
    menu_rect.setOutlineThickness(5);
    menu_rect.setOutlineColor(sf::Color::Black);
    menu_rect.setOrigin(menu_rect.getSize().x / 2, menu_rect.getSize().y / 2);
    menu_rect.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
}
