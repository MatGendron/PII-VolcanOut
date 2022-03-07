#include "Tile.hpp"
#include "Unbreakable.hpp"

using namespace std;

Unbreakable::Unbreakable(float x, float y, sf::Texture* texture) : Tile{ x,y } {
	_texture = texture;
	_sprite.setTexture(*_texture);
}

void Unbreakable::initSprite() {
	_sprite.setTexture(*_texture);
}

void Unbreakable::draw(sf::RenderWindow* window) {
	_sprite.setPosition(_x, _y);
	window->draw(_sprite);
}