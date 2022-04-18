#pragma once

#include "Tile.hpp"

using namespace std;

class Unbreakable :Tile {

public:
	Unbreakable(float x, float y, sf::Texture* texture);

	sf::Texture* getTexture() {
		return _texture;
	}

	void setTexture(sf::Texture* texture) {
		_texture = texture;
	}

	//Draw the tile on the window
	void draw(sf::RenderWindow* window);

private:
	sf::Texture* _texture;
	sf::Sprite _sprite;
};
