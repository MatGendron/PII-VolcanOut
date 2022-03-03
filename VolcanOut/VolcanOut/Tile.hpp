#pragma once

#include <SFML/Graphics.hpp>

using namespace std;

class Tile {
public:
	static sf::Texture texture;
	int x;
	int y;
	Tile(int x, int y);
};