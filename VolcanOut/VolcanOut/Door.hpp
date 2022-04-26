#pragma once
#include "Tile.hpp"

using namespace std;

class Door :Tile {
public:
	Door(float x, float y, sf::Texture* texture);

	void draw(sf::RenderWindow* window);

private:
	sf::Texture* _texture;
	sf::Sprite _sprite;
};