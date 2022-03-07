#pragma once

#include <SFML/Graphics.hpp>

using namespace std;

class Tile {
public:
	static sf::Texture texture;
	float _x;
	float _y;
	Tile();
	Tile(float x, float y);
};