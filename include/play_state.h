#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include <list>
#include <SFML/Graphics.hpp>

#include "game_state.h"



class Application;
class Player;
class Enemy;
class Bullet;
class Game_map;
class Mini_map;


class Play_state: public Game_state{
public:
    void init();
    Play_state(Application *app);
    ~Play_state();
    Player *player;
    std::list<Enemy *> enemy_list;
    std::list<Bullet *> bullet_list;

    //sf::Font font;
    //sf::Text score_text;
    //sf::Text fps_count_text;
    sf::Clock clock;
    //bool is_initialized = false;

    void create_score_text(const sf::Font &font, const unsigned int text_size);
    void create_font();
    void create_player(Application *app);
    void input();
    void input(const sf::Event &event);
    void input(Application *app);
    void update(double dt, Application *app);
    void draw(Application *app);
    void init_entities(Application *app);
    //sf::RectangleShape field_rect;
    //void create_field();
    void update_score();
    void create_fps_count_text(const sf::Font &font, const unsigned int text_size);
    void update_fps_count();
    void update_enemy_population(const sf::Texture &enemy_easy_texture,
                             const sf::Texture& enemy_medium_texture);
    void reset(Application *app);
    void set_initial_enemy_spawn(bool initial_enemy_spawn){
        initial_enemy_spawn_ = initial_enemy_spawn;
    }
    bool initial_enemy_spawn(){
        return initial_enemy_spawn_;
    }
    void update_info_text(Application *app);
    sf::RectangleShape& info_rect_shape(){
        return info_rect_shape_;
    }
    sf::Text& player_info_text(){
        return player_info_text_;
    }
    void update_info_panel();
    sf::Vector2f& info_rect_shape_initial_position(){
        return info_rect_shape_initial_position_;
    }
    void set_info_rect_shape_initial_position(const sf::Vector2f& info_rect_shape_initial_position){
        info_rect_shape_initial_position_ = info_rect_shape_initial_position;
    }
    sf::Vector2f& info_text_initial_position(){
        return info_text_initial_position_;
    }
    void set_info_text_initial_position(const sf::Vector2f info_text_initial_position){
        info_text_initial_position_ = info_text_initial_position;
    }
    void draw_map(Application *app);
    //void draw_map2(Application *app);
    void draw_map2(Application *app, const sf::Vector2f& dir);
    void draw_player_fov(Application *app);
    Game_map* game_map(){
        return game_map_;
    }
    void play_sounds();
    void init(Application *app);
    sf::Clock& play_state_clock(){
        return play_state_clock_;
    }
    void play_music(Application *app);
    bool show_mini_map(){
        return show_mini_map_;
    }
    void set_show_mini_map(bool show_mini_map){
        show_mini_map_ = show_mini_map;
    }
    void draw_mini_map(Application *app);
    //sf::RectangleShape& mini_map_rect_shape(){
        //return mini_map_rect_shape_;
    //}
    //void init_mini_map_rect_shape();
private:
    bool initial_enemy_spawn_ = true;//is true for the first wave of enemies, is used to
                                     //place enemies far from the player when the game starts
    sf::Text player_info_text_;
    sf::RectangleShape info_rect_shape_;
    sf::Vector2f info_rect_shape_initial_position_;
    sf::Vector2f info_text_initial_position_;
    Game_map* game_map_;
    sf::Clock play_state_clock_;
    bool show_mini_map_ = false;
    ///mini map
    //sf::RectangleShape mini_map_rect_shape_;
    Mini_map *mini_map;

};
#endif // PLAY_STATE_H
