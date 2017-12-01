

#include "animation_manager.h"
#include "entity.h"


AnimationManager& AnimationManager::operator=(const AnimationManager &other){
    if(&other == this){
        return *this;
    }
    current_animation = other.current_animation;
    animation_map = other.animation_map;
    return *this;
}

void AnimationManager::create(const std::string &name, const sf::Texture &texture,
                           int x, int y, int w, int h, int frame_count,
                           double speed, int step, bool loop){
    Animation a;
    a.speed = speed;
    a.loop = loop;
    a.sprite.setTexture(texture);
    //a.sprite.setOrigin(w * 0, h * 0);

    for (int i = 0; i < frame_count; ++i)
    {
        a.frames.push_back(sf::IntRect(x + i * step, y, w, h));
        a.frames_flip.push_back(sf::IntRect(x + i * step + w, y, -w, h));
    }
    animation_map[name] = a;
    current_animation = name;
}

void AnimationManager::set_animation(std::string name){
    //std::cout << "set " << name << std::endl;
    current_animation = name;
    animation_map[current_animation].flip = 0;
}

void AnimationManager::draw(sf::RenderWindow &window, Entity *e){//double x, double y, double offset_x, double offset_y, origin_x, double origin_y, double angle){
    //get_current_animation().sprite.setOrigin(sf::Vector2f(e -> get_origin_x(), e -> get_origin_y()));
    //get_current_animation().sprite.setPosition(e -> get_x() + offset_x, e -> get_y() + offset_y);
    //get_current_animation().sprite.setTextureRect(sf::IntRect(col * w, row * h, w, h));
    //get_current_animation().sprite.rotate((e -> get_angle()) * dt);
    //std::cout << "origin x: " << e -> get_origin_x() << ", y: " << e -> get_origin_y() << std::endl;
    //std::cout << "angle: "  << e -> get_angle() << ", rotation: " <<
    //get_current_animation().sprite.getRotation() << std::endl;
    window.draw(get_current_animation().sprite);
}

void AnimationManager::flip(bool b){
    animation_map[current_animation].flip = b;
}


void AnimationManager::tick(double time){
    animation_map[current_animation].tick(time);
}

void AnimationManager::pause(){
    animation_map[current_animation].is_playing = false;
}

void AnimationManager::play(){
    animation_map[current_animation].is_playing = true;
}

void AnimationManager::play(std::string name){
    animation_map[name].is_playing = true;
}


bool AnimationManager::is_playing(){
    return animation_map[current_animation].is_playing;
}

double AnimationManager::get_h(){
    return animation_map[current_animation].frames[0].height;
}


double AnimationManager::get_w(){
    return animation_map[current_animation].frames[0].width;
}


Animation& AnimationManager::get_current_animation(){
    return animation_map[current_animation];
}
