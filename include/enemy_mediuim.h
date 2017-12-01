#ifndef ENEMY_MEDIUM_H
#define ENEMY_MEDIUM_H

#include "enemy.h"
#include "config.h"

class Enemy_medium: public Enemy{
public:
    static int enemy_medium_cnt;
    Enemy_medium(double x, double y, double w, double h, double dx, double dy, int angle, int health, int damage, const sf::Texture& texture, int row, int col):
        Enemy(x, y, w, h, dx, dy, angle, health, damage, texture, row, col){
            ++enemy_medium_cnt;
            //std::cout << "in Enemy_medium constructor, cnt: " << enemy_medium_cnt << std::endl;
            //animation_manager().set_animation("enemy_medium_movement_default");
            create_animations();
            set_type(Enemy_type::enemy_medium);
    }
    ~Enemy_medium(){
        //std::cout << "in medium destructor" << std::endl;
        --enemy_medium_cnt;
    }
    double get_dx_base(){
        return ENEMY_MEDIUM_DX;
    }
    double get_dy_base(){
        return ENEMY_MEDIUM_DY;
    }
    void create_animations();
};
#endif // ENEMY_MEDIUM_H
