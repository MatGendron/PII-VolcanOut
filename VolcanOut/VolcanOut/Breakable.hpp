#pragma once

#include "Tile.hpp"
#include <iostream>

using namespace std;

class Breakable :Tile {

public:
	Breakable(int x, int y);

	void draw(sf::RenderWindow* window);

	sf::Texture texture;
	//bool texture_initialized;

private:
	sf::Sprite sprite;
};
