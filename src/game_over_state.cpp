
#include <iostream>
#include <sstream>

#include "application.h"
#include "display.h"
#include "game_over_state.h"




Game_over_state::Game_over_state(Application *app): Game_state(app){
    init_entities();
    std::cout << "Game_over_state()" << std::endl;
}

Game_over_state::~Game_over_state(){
    std::cout << "~Game_over_state()" << std::endl;
}

void Game_over_state::create_game_over_font(){
    font.loadFromFile(FONTS_PATH + "ubuntu.ttf");
}


void Game_over_state::create_game_over_text(const sf::Font &font, const unsigned int text_size){
    game_over_text.setFont(font);
    game_over_text.setCharacterSize(text_size);
    game_over_text.setColor(sf::Color::Black);
}


void Game_over_state::create_score_text(const sf::Font &font, const unsigned int text_size){
    score_text.setFont(font);
    score_text.setCharacterSize(text_size);
    score_text.setColor(sf::Color::Black);
    score_text.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 50);
}

void Game_over_state::create_press_any_key_text(const sf::Font &font, const unsigned int text_size){
    press_any_key_text.setFont(font);
    press_any_key_text.setCharacterSize(text_size);
    press_any_key_text.setColor(sf::Color::Black);
    press_any_key_text.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 125);
    press_any_key_text.setString("Press Enter to go to the main menu.");
}

void Game_over_state::draw(Application *app){
    app -> display -> clear(GAME_OVER_STATE_BACKGROUND_COLOR);
    app -> display -> draw(game_over_text);
    app -> display -> draw(score_text);
    app -> display -> draw(press_any_key_text);
}


void Game_over_state::init_entities(){
    create_game_over_font();
    create_game_over_text(font, GAME_OVER_TEXT_SIZE);
    create_score_text(font, SCORE_TEXT_SIZE);
    create_press_any_key_text(font, PRESS_ANY_KEY_TEXT_SIZE);
}


void Game_over_state::input(const sf::Event &event){};

void Game_over_state::input(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
        application -> pop_state();
    }
};


void Game_over_state::input(Application *app){
    sf::Event event;
    while(app -> display -> window -> pollEvent(event)){
        if(event.type == sf::Event::Closed){
            app -> display -> window -> close();
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
        ///Player score reset is here!
        app -> set_player_score(0);
        application -> pop_state();
        delete(this);
    }
};

void Game_over_state::update(double dt, Application *app){
    std::ostringstream game_over_text_stringstream;
    game_over_text_stringstream << "Game is over." << std::endl;
    game_over_text.setString(game_over_text_stringstream.str());
    sf::FloatRect rect = game_over_text.getLocalBounds();
    game_over_text.setOrigin(rect.width / 2, rect.height / 2);
    game_over_text.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

    std::ostringstream score_text_stringstream;
    score_text_stringstream << "Final score: " << application -> player_score() << std::endl;
    //score_text_stringstream << "Player " << application -> player_score << " : " << application -> bot_score << " Bot" << std::endl;
    score_text.setString(score_text_stringstream.str());
    sf::FloatRect score_rect = score_text.getLocalBounds();
    score_text.setOrigin(score_rect.width / 2, score_rect.height / 2);
    score_text.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + game_over_text.getLocalBounds().height);

    sf::FloatRect any_key_rect = press_any_key_text.getLocalBounds();
    press_any_key_text.setOrigin(any_key_rect.width / 2, any_key_rect.height / 2);
    press_any_key_text.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + game_over_text.getLocalBounds().height + score_text.getLocalBounds().height);
};




