#pragma once

#include <SFML/Graphics.hpp>
#include "Level.hpp"

using namespace std;

class Lava {
public:
	Lava(sf::Texture* texture, Level* level) {
		_speed = level->getSpeed();
		_texture = texture;
		_levelHeight = level->getHeight() * 16.f;
		_x = _levelHeight;
	}

	float getHeight() {
		return _x;
	}

	/*Used to update the lava parameters when 
	* switching to a new level
	*/
	void updateParameters(Level* level);

	//Lets the lava rise according to its speed
	void rise();

	//Resets the lava to the height of the level
	void reset();

	//Draw the lava on the window
	void draw(sf::RenderWindow* window, int width, int height);


private:
	float _x;
	int _speed;
	float _levelHeight;
	sf::Texture* _texture;
	sf::Clock _clock;
};