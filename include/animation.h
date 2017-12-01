#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include <vector>

class Animation{
public:
	std::vector<sf::IntRect> frames;
	std::vector<sf::IntRect> frames_flip;
	double current_frame;
	double speed;
	bool loop;//loop показвает зациклена ли анимация. Например анимация взрыва должна проиграться один раз и остановиться, loop=false
	bool flip;
	bool is_playing;
	sf::Sprite sprite;
	Animation();
	void tick(double time);
};


#endif // ANIMATION_H

