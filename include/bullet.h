#ifndef BULLET_H
#define BULLET_H

#include <iostream>

#include "entity.h"

class Bullet: public Entity{
public:
    Bullet(double x, double y, double w, double h, double dx, double dy, int angle, int health, int damage, const sf::Texture& texture, int row, int col):
        Entity(x, y, w, h, dx, dy, angle, health, damage, texture, row, col){
        //std::cout << "in bullet constructor" << std::endl;
        set_bounding_box(sf::FloatRect(0, 0, 16, 16));
        create_animations();
        //set_animation("bullet_fire_animation");
        //set_animation("bullet_default_animation");
        //set_animation("bullet_animation");
    }
    ~Bullet(){
        //std::cout << "in bullet destructor" << std::endl;
    }
    void update(double dt);
    double get_player_x(){
        return player_x_;
    }
    void set_player_x(double player_x){
        player_x_ = player_x;
    }
    double get_player_y(){
        return player_y_;
    }
    void set_player_y(double player_y){
        player_y_ = player_y;
    }
    void create_animations();
    //bool check_collision_with_map(std::vector<std::string> &game_map);
    bool check_collision_with_map(std::vector<std::vector<char> >& char_map);
    void set_animation(const std::string& animation_name);
private:
    double player_x_;
    double player_y_;
};
#endif // BULLET_H
