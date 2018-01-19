#ifndef ANIMATION_MANAGER_H_
#define ANIMATION_MANAGER_H_

#include "animation.h"
#include<map>


class Entity;



class AnimationManager {

public:
    std::string current_animation;
	std::map<std::string, Animation> animation_map;

	AnimationManager() {};

	~AnimationManager() {
        animation_map.clear();
	}
	AnimationManager& operator=(const AnimationManager &other);
	void create(const std::string &name, const sf::Texture &texture,
             int x, int y, int w, int h, int frame_count, double speed, int step = 0, bool loop = true);
    void set_animation(std::string name);
    void draw(sf::RenderWindow &window, Entity *e);
    void flip(bool b = true);
    void tick(double time);
    void pause();
    void play();
    void play(std::string name);
    bool is_playing();
    double get_h();
    double get_w();
    Animation& get_current_animation();
};


#endif // ANIMATION_MANAGER_H_

