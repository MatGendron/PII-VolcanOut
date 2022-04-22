#include "Lava.hpp"

using namespace std;

void Lava::updateParameters(Level* level) {
	_speed = level->getSpeed();
	_levelHeight = level->getHeight() * 16.f;
	_x = _levelHeight;
}

void Lava::rise() {
	if (_clock.getElapsedTime().asMilliseconds() > _speed) {
		_x -= 8;
		_clock.restart();
	}
}

void Lava::reset() {
	_x = _levelHeight;
}

void Lava::draw(sf::RenderWindow* window, int levelWidth, int levelHeight) {
	for (float i = _x; i < levelHeight*16.f; i+=16.f) {
		for (int j = 0; j < levelWidth*16.f; j+=16.f) {
			sf::Sprite sprite;
			sprite.setTexture(*_texture);
			sprite.setPosition(j, i);
			window->draw(sprite);
		}
	}
}