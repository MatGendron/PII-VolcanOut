#include "Tile.hpp"
#include "Breakable.hpp"
#include <iostream>

using namespace std;

Breakable::Breakable(int x, int y) : Tile{ x,y } {
	//if (!texture_initialized) {
		if (!texture().loadFromFile("Breakable_tex.png")) {
			std::cout << "Could not load Breakable_tex.png";
		}
		//texture_initialized = true;
		sprite.setTexture(texture());
	//}
	//texture.loadFromFile("Breakable_tex.png");
	//sprite.setTexture(texture);
}

void Breakable::draw(sf::RenderWindow* window) {
	sprite.setPosition((float) x, (float) y);
	window->draw(sprite);
}