#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <memory>
#include <stack>

#include "singleton.h"



class Display;
class Game_state;
class Play_state;
class Delay_state;
class Game_over_state;
class Main_menu_state;
class Options_state;
class Resource_holder;



class Application {
public:
    Application();
    Display *display;
    int fps_count;
    ~Application();
    void run();
    int bot_score = 0;
    Resource_holder *resource_holder;

    void push_state(Game_state *state);
    void pop_state();
    void change_state(Game_state *state);
    //std::unique_ptr<Game_state> state() {
    Game_state *state() {
        return states.top();
    }
    void destroy();
    void show_fps();
    void load_resources();

    std::stack<Game_state *> states;
    void set_player_score(int player_score) {
        player_score_ = player_score;
    }
    int player_score() {
        return player_score_;
    }
    void reset_player_score();

    Main_menu_state *main_menu_state;
    Play_state *play_state;
    Delay_state *delay_state;
    Game_over_state *game_over_state;
    Options_state *options_state;
private:
    int player_score_ = 0;
};

#endif // APPLICATION_H_

