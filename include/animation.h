#ifndef ANIMATION_H_
#define ANIMATION_H_

#include <SFML/Graphics.hpp>
#include <vector>

class Animation {
public:
	std::vector<sf::IntRect> frames;
	std::vector<sf::IntRect> frames_flip;
	double current_frame;
	double speed;
	bool loop;
	bool flip;
	bool is_playing;
	sf::Sprite sprite;
	Animation();
	void tick(double time);
};


#endif // ANIMATION_H_

