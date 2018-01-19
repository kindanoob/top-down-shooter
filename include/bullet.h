#ifndef BULLET_H_
#define BULLET_H_

#include <iostream>

#include "entity.h"

class Bullet: public Entity {
public:
    Bullet(double x, double y, double w, double h, double dx, double dy, int angle, int health, int damage, const sf::Texture& texture, int row, int col):
        Entity(x, y, w, h, dx, dy, angle, health, damage, texture, row, col){
        set_bounding_box(sf::FloatRect(0, 0, 16, 16));
        create_animations();
        //set_animation("bullet_fire_animation");
        //set_animation("bullet_default_animation");
        //set_animation("bullet_animation");
    }
    ~Bullet(){
        //
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
    bool check_collision_with_map(std::vector<std::vector<char> >& char_map);
    void set_animation(const std::string& animation_name);
private:
    double player_x_ = 0.0;
    double player_y_ = 0.0;
};

#endif // BULLET_H_
