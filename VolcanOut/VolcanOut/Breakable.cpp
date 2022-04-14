#include "Tile.hpp"
#include "Breakable.hpp"

using namespace std;

Breakable::Breakable(float x, float y, sf::Texture* texture) : Tile{ x,y } {
	_texture = texture;
	_sprite.setTexture(*_texture);
}

void Breakable::draw(sf::RenderWindow* window) {
	_sprite.setPosition(_x, _y);
	window->draw(_sprite);
}