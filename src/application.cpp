#include <iostream>
#include <memory>
#include  <utility>

#include "application.h"
#include "display.h"
#include "game_state.h"
#include "play_state.h"
//#include "delay_state.h"
#include "game_over_state.h"
#include "main_menu_state.h"
#include "options_state.h"
#include "resource_holder.h"



Application::Application(): player_score_(0){
    std::cout << "Application()" << std::endl;
    //std::unique_ptr<Resource_holder> resource_holder = std::make_unique<Resource_holder>();
    //std::unique_ptr<Resource_holder> resource_holder(new Resource_holder());
    resource_holder = new Resource_holder();
    //resource_holder.reset(new Resource_holder());
    display = new Display();
    //main_menu_state.reset(new Main_menu_state(this));
    //push_state(std::move(main_menu_state));
    main_menu_state = new Main_menu_state(this);
    push_state(main_menu_state);
    //delay_state = new Delay_state(this);
    //play_state = new Play_state(this);
    //push_state(play_state);
    //game_over_state = new Game_over_state(this);
    //options_state = new Options_state(this);
    //display -> init();
    //std::cout << "out Application constructor" << std::endl;
}

Application::~Application(){
    std::cout << "~Application()" << std::endl;
}

void Application::run(){
    sf::Clock clock;
    while(display -> is_open()){
        unsigned long long time = clock.getElapsedTime().asMicroseconds();
        if(time % 100 == 0){
        //if(true){
            fps_count = 1000000.0 / time;
        }
        //show_fps();
        //std::cout << "dt before: " << time;
        double dt = time / TIME_ADJUSTMENT_COEFF;
        //std::cout << ", dt after: " << dt << std::endl;
        //std::cout << time << ", " << dt << ", " << fps_count << std::endl;
        clock.restart();
        //display -> check_window_events(this);
        //display -> clear();
        //std::cout << "=================== input: ===================" << std::endl;
        states.top() -> input(this);
        //std::cout << "=================== update: ===================" << std::endl;
        states.top() -> update(dt, this);
        //std::cout << "=================== draw: ===================" << std::endl;
        states.top() -> draw(this);

        display -> display();
    }
    display -> destroy();
}


//void Application::push_state(std::unique_ptr<Game_state> state){
void Application::push_state(Game_state *state){
    states.push(state);
};


void Application::pop_state(){
    states.pop();
};


void Application::change_state(Game_state *state){
    states.pop();
    states.push(state);
};


void Application::destroy(){
    delete play_state;
    delete this;
}


void Application::show_fps(){
    std::cout << "FPS: " << fps_count << std::endl;
}


void Application::reset_player_score(){
    set_player_score(0);
}

//void Application::load_resources(){
    //resource_holder -> textures -> get_
//}
