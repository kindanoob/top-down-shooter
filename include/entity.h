#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <SFML/Graphics.hpp>

#include "animation_manager.h"
#include "weapon.h"


enum class Collision_direction{horizontal, vertical};


class Entity{
public:
    Entity(double x, double y, double w, double h, double dx, double dy, int angle, int health, int damage, sf::Texture texture, int row, int col):
        x_(x), y_(y), w_(w), h_(h), dx_(dx), dy_(dy), texture_(texture), angle_(angle), health_(health), damage_(damage), current_frame_(col){
        //std::cout << "Entity()" << std::endl;
        get_texture().setSmooth(true);
        set_origin();
        ///bounding box!
        set_bounding_box(sf::FloatRect(0, 0, h, h));
        //std::cout << "after entity" << std::endl;
        //set_origin_x(texture.getSize().y);//<--- ATTENTION
        //set_origin_y(texture.getSize().y);
        //sprite_.setTexture(texture_);
        //sprite_.setTextureRect(sf::IntRect(col * w, row * h, w, h));
        //sprite_.setOrigin(sf::Vector2f(origin_y / 2, origin_y / 2));
        //sprite_.setPosition(x, y);

        //rect = sf::FloatRect(x, y, w, h);
        //shape.setFillColor(color);
        //shape.setOutlineThickness(thickness);
        //shape.setOutlineColor(sf::Color::Black);
    }
    double get_x(){
        return x_;
    }
    double get_y(){
        return y_;
    }
    void set_x(double x){
        x_ = x;
    }
    void set_y(double y){
        y_ = y;
    }
    double get_origin_x(){
        return origin_x_;
    }
    double get_origin_y(){
        return origin_y_;
    }
    void set_origin_x(double origin_x){
        origin_x_ = origin_x;
    }
    void set_origin_y(double origin_y){
        origin_y_ = origin_y;
    }
    double get_w(){
        return w_;
    }
    double get_h(){
        return h_;
    }
    void set_w(double w){
        w_ = w;
    }
    void set_h(double h){
        h_ = h;
    }
    double get_offset_x(){
        return offset_x_;
    }
    double get_offset_y(){
        return offset_y_;
    }
    void set_offset_x(double offset_x){
        offset_x_ = offset_x;
    }
    void set_offset_y(double offset_y){
        offset_y_ = offset_y;
    }
    double get_dx(){
        return dx_;
    }
    double get_dy(){
        return dy_;
    }
    void set_dx(double dx){
        dx_ = dx;
    }
    void set_dy(double dy){
        dy_ = dy;
    }
    sf::CircleShape& get_shape(){
        return shape;
    }
    sf::Texture& get_texture(){
        return texture_;
    }
    void set_texture(const sf::Texture &texture){
        texture_ = texture;
    }
    sf::Sprite& get_sprite(){
        //return sprite_;
        return animation_manager().get_current_animation().sprite;
    }
    virtual void update(double dt) = 0;
    virtual void create_animations() = 0;
    //void check_collision_with_ball(Entity *b);
    //void check_collision_with_map(DIRECTION dir);
    void update_angle();
    void set_angle(int angle){
        angle_ = angle;
    }
    int get_angle(){
        return angle_;
    }
    void set_mouse_angle(int mouse_angle){
        mouse_angle_ = mouse_angle;
    }
    int get_mouse_angle(){
        return mouse_angle_;
    }
    bool get_is_alive(){
        return is_alive_;
    }
    void set_is_alive(bool is_alive){
        is_alive_ = is_alive;
    }
    int get_health(){
        return health_;
    }
    void set_health(int health){
        health_ = health;
    }
    int get_damage(){
        return damage_;
    }
    void set_damage(int damage){
        damage_ = damage;
    }
    void draw(sf::RenderWindow &window);
    AnimationManager& animation_manager(){
        return animation_manager_;
    }
    void set_origin(){
        set_origin_x(get_texture().getSize().y / 2);//<---ATTENTION
        set_origin_y(get_texture().getSize().y / 2);
        //std::cout << "origin set to x: " << get_origin_x() << ", y: " <<
        //get_origin_y() << std::endl;
    }
    //void check_collision_with_map(std::vector<std::string> &game_map, COLLISION_DIRECTION dir);
    bool check_collision_with_map(std::vector<std::vector<char> > &game_map, Collision_direction dir);
    bool check_collision_with_map2(std::vector<std::vector<char> > &game_map);
    void update_offset_x();
    void update_offset_y();
    sf::FloatRect bounding_box(){
        return bounding_box_;
    }
    void set_bounding_box(sf::FloatRect bounding_box){
        bounding_box_ = bounding_box;
    }
    void update_bounding_box();
    double get_BB_w(){
        return bounding_box().width;
    }
    double get_BB_h(){
        return bounding_box().height;
    }
    sf::Vector2f get_position(){
        return sf::Vector2f(get_x(), get_y());
    }
    void set_position(sf::Vector2f& position){
        position_ = position;
    }
    //void check_collision_with_entity(Entity *e);
    void set_alive_duration(int alive_duration){
        alive_duration_ = alive_duration;
    }
    int alive_duration(){
        return alive_duration_;
    }
    long long ticks_alive(){
        return ticks_alive();
    }
    void set_ticks_alive(long long ticks_alive){
        ticks_alive_ = ticks_alive;
    }
    long long ticks_alive_ = 0LL;
private:
    sf::CircleShape shape;
    double x_;
    double y_;
    double w_;
    double h_;
    double dx_;
    double dy_;
    double origin_x_;
    double origin_y_;
    int offset_x_ = 0;
    int offset_y_ = 0;
    //double r_;
    int health_;
    int damage_;
    bool is_alive_ = true;
    int angle_ = 0;
    int mouse_angle_ = 0;
    sf::Texture texture_;
    sf::Sprite sprite_;
    AnimationManager animation_manager_;
    double current_frame_;
    sf::FloatRect bounding_box_;
    sf::Vector2f position_;
    int alive_duration_ = 0;//in milliseconds
    //Weapon weapon_;


};


#endif // ENTITY_H
