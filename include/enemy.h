#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>


#include "entity.h"

class Player;

enum class Enemy_type{enemy_easy, enemy_medium, enemy_hard};

class Enemy: public Entity{
public:
    static int cnt;
    Enemy(double x, double y, double w, double h, double dx, double dy, int angle, int health, int damage, const sf::Texture& texture, int row, int col):
    Entity(x, y, w, h, dx, dy, angle, health, damage, texture, row, col){
        //std::cout << "Enemy()" << std::endl;
        ++cnt;
        //std::cout << "in Enemy constructor, cnt: " << cnt << std::endl;
    }
    void update(double dt);
    void update_player_angle();
    int get_player_angle(){
        return player_angle_;
    }
    void set_player_angle(double player_angle){
        player_angle_ = player_angle;
        if(get_player_angle() < 0){
            player_angle_ += 360;
        }
    }
    bool check_collision_with_enemy(Enemy *e);
    bool check_collision_with_player(Player *p);
    virtual ~Enemy(){
        //std::cout << "in base destructor" << std::endl;
    }
    virtual double get_dx_base() = 0;
    virtual double get_dy_base() = 0;
    Enemy_type get_type(){
        return type_;
    }
    void set_type(Enemy_type type){
        type_ = type;
    }

private:
    int player_angle_;
    Enemy_type type_;
};
#endif // ENEMY_H
