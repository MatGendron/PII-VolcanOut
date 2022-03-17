#pragma once
#include <SFML/Graphics.hpp>

using namespace std;

class Player {
public:
	Player(float x, float y);

private:
	float _x;
	float _y;
	sf::Texture _jump;
	sf::Texture _fall;
	
};