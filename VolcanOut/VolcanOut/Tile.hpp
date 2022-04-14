#pragma once

#include <SFML/Graphics.hpp>

using namespace std;

class Tile {
public:
	Tile();
	Tile(float x, float y);

protected:
	static sf::Texture texture;
	float _x;
	float _y;
};