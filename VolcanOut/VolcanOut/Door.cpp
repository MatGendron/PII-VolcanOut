#include "Tile.hpp"
#include "Door.hpp"

using namespace std;

Door::Door(float x, float y, sf::Texture* texture) :Tile{ x,y } {
	_texture = texture;
	_sprite.setTexture(*_texture);
}

void Door::draw(sf::RenderWindow* window) {
	_sprite.setPosition(_x, _y);
	window->draw(_sprite);
}
