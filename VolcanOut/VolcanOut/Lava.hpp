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


private:
	int _speed;
	sf::Texture* _texture;
};