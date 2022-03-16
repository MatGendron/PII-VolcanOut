#pragma once

#include "Tile.hpp"

using namespace std;

class Breakable :Tile {

public:
	Breakable(float x, float y, sf::Texture* texture);

	void draw(sf::RenderWindow* window);
	
	sf::Texture* getTexture() {
		return _texture;
	}

	void setTexture(sf::Texture* texture){
		_texture = texture;
	}

	void initSprite();

private:
	sf::Texture* _texture;
	sf::Sprite _sprite;
};