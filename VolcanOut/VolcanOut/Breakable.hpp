#pragma once

#include "Tile.hpp"
#include <iostream>

using namespace std;

class Breakable :Tile {

public:
	Breakable(int x, int y);

	void draw(sf::RenderWindow* window);

	static sf::Texture& texture() { static sf::Texture tex; return tex; };
	//sf::Texture texture;
	//bool texture_initialized = false;

private:
	sf::Sprite sprite;
};
