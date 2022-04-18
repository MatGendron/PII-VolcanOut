#pragma once

#include <SFML/Graphics.hpp>

using namespace std;

class Lava {
public:
	Lava(int speed, sf::Texture* texture) {
		_speed = speed;
		_texture = texture;
	}

	//Lets the lava rise according to its speed
	void rise();

	//Draw the lava on the window
	void draw(sf::RenderWindow* window);


private:
	int _speed;
	sf::Texture* _texture;
	sf::Clock _clock;
};