#ifndef PLAYER_H_
#define PLAYER_H_


#include <SFML/Audio.hpp>

#include "entity.h"
#include "config.h"


class Application;
class Enemy;


class Player: public Entity {
public:
    Player(double x, double y, double w, double h, double dx, double dy, int angle, int health, int damage, sf::Texture &texture, int row, int col, sf::Texture aim_texture, int aim_row, int aim_col):
        Entity(x, y, w, h, dx, dy, angle, health, damage, texture, row, col){
        sf::FloatRect r = get_sprite().getGlobalBounds();
        set_center_x(x);
        set_center_y(y);
        set_origin_x(get_texture().getSize().y / 2); //<--- ATTENTION

        set_aim_texture(aim_texture);
        set_aim_sprite(get_aim_texture());
        get_aim_sprite().setOrigin(sf::Vector2f(get_aim_texture().getSize().x / 2, get_aim_texture().getSize().y / 2));
        animation_manager().set_animation("player_aim_animation");


        get_sprite().setPosition(sf::Vector2f(50, 100));
        create_animations();
        animation_manager().set_animation("player_default_animation");


        //test_sound_buffer.loadFromFile("resources/sounds/player_shoot1.wav");;
        //test_sound.setBuffer(test_sound_buffer);
        //test_sound.setVolume(0);

    };
    void get_input_from_player(sf::RenderWindow *window);
    void update(double dt);
    void create_animations();
    void set_is_shooting(bool b){
        is_shooting = b;
    }
    bool get_is_shooting(){
        return is_shooting;
    }
    void set_center_x(double x){
        center_x_ = x;
    }
    void set_center_y(double y){
        center_y_ = y;
    }
    double get_center_x(){
        return center_x_;
    }
    double get_center_y(){
        return center_y_;
    }
    void set_gun_x(double x){
        gun_x_ = x;
    }
    void set_gun_y(double y){
        gun_y_ = y;
    }
    double get_gun_x(){
        return gun_x_;
    }
    double get_gun_y(){
        return gun_y_;
    }
    sf::Vector2f get_gun(){
        return sf::Vector2f(get_gun_x(), get_gun_y());
    }
    int get_invul_duration(){
        return invul_duration_;
    }
    void set_invul_duration(int invul_duration){
        invul_duration_ = invul_duration;
    }
    bool check_collision_with_enemy(Enemy * enemy);
    void set_aim_texture(const sf::Texture& aim_texture){
        aim_texture_ = aim_texture;
    }
    sf::Texture& get_aim_texture(){
        return aim_texture_;
    }
    sf::Sprite& get_aim_sprite(){
        return aim_sprite_;
    }
    void set_aim_sprite(const sf::Texture& aim_texture){
        get_aim_sprite().setTexture(aim_texture);
    }
    void update_aim_sprite();
    sf::Vector2i& get_mouse_world_position(){
        return mouse_world_position_;
    }
    void set_mouse_world_position(sf::Vector2i mouse_world_position){
        get_mouse_world_position() = mouse_world_position;
    }
    void update_mouse_world_position(Application *app);
    void set_shoot_sound(sf::SoundBuffer& buff){
        //std::cout << "shoot buff duration: " << buff.getDuration().asMilliseconds() << std::endl;
        shoot_sound_.setBuffer(buff);
        shoot_sound_.setVolume(10);
    }
    sf::Sound& shoot_sound(){
        return shoot_sound_;
    }
    sf::Sound test_sound;
    sf::SoundBuffer test_sound_buffer;
    void play_shoot_sound(){
        shoot_sound().play();
    }
    //void set_shoot_duration_in_milliseconds(int shoot_duration_in_milliseconds){
        //shoot_duration_in_milliseconds_ = shoot_duration_in_milliseconds;
    //}
    long long aftershot_delay(){
        return aftershot_delay_;
    }
    void set_aftershot_delay(long long aftershot_delay){
        aftershot_delay_ = aftershot_delay;
    }
    sf::Vector2f direction(){
        return sf::Vector2f(get_gun() - get_position());
    }

private:
    bool is_shooting = false;
    double center_x_;
    double center_y_;
    double gun_x_;
    double gun_y_;
    int invul_duration_ = 0;
    sf::Texture aim_texture_;
    sf::Sprite aim_sprite_;
    sf::Vector2i mouse_world_position_;
    sf::Sound shoot_sound_;
    //set aftershot delay so that it is not triggered before player made first shot
    long long aftershot_delay_ = 100 * AFTERSHOT_DELAY_IN_MILLISECONDS + 0LL;
    //int shoot_duration_in_milliseconds_;

};

#endif // PLAYER_H_
