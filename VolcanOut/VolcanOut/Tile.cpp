#include "Tile.hpp"

using namespace std;

Tile::Tile() {
	_x = 0;
	_y = 0;
}

Tile::Tile(float x, float y) {
	_x = x*16.f;
	_y = y*16.f;
}


