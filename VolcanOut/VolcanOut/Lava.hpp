#pragma once

#include <SFML/Graphics.hpp>
#include "Level.hpp"

using namespace std;

class Lava {
public:
	Lava(sf::Texture* texture, Level* level) {
		_speed = level->getSpeed();
		_texture = texture;
		_x = level->getHeight()*16.f;
	}

	//Lets the lava rise according to its speed
	void rise();

	//Draw the lava on the window
	void draw(sf::RenderWindow* window, int width, int height);


private:
	float _x;
	int _speed;
	sf::Texture* _texture;
	sf::Clock _clock;
};