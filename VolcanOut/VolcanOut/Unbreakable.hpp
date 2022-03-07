#pragma once

#include "Tile.hpp"
//#include <iostream>

using namespace std;

class Unbreakable :Tile {

public:
	Unbreakable(float x, float y, sf::Texture* texture);

	void draw(sf::RenderWindow* window);

	sf::Texture* getTexture() {
		return _texture;
	}

	void setTexture(sf::Texture* texture) {
		_texture = texture;
	}

	void initSprite();

private:
	sf::Texture* _texture;
	sf::Sprite _sprite;
};
