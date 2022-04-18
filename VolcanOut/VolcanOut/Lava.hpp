#pragma once

#include <SFML/Graphics.hpp>

using namespace std;

class Lava {
public:
	Lava(int speed, sf::Texture* texture, int levelHeight) {
		_speed = speed;
		_texture = texture;
		_x = levelHeight*16.f;
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