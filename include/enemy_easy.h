#ifndef ENEMY_EASY_H_
#define ENEMY_EASY_H_

#include "enemy.h"
#include "config.h"

class Enemy_easy: public Enemy {
public:
    static int enemy_easy_cnt;
    Enemy_easy(double x, double y, double w, double h, double dx, double dy, int angle, int health, int damage, const sf::Texture& texture, int row, int col) :
    Enemy(x, y, w, h, dx, dy, angle, health, damage, texture, row, col) {
        ++enemy_easy_cnt;
        //animation_manager().set_animation("enemy_easy_default_movement");
        create_animations();
        set_type(Enemy_type::enemy_easy);
    }
    ~Enemy_easy() {
        --enemy_easy_cnt;
    }
    double get_dx_base() {
        return ENEMY_EASY_DX;
    }
    double get_dy_base() {
        return ENEMY_EASY_DY;
    }
    void create_animations();
};

#endif // ENEMY_EASY_H_
