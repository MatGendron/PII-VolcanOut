#include "Player.hpp"

using namespace std;

Player::Player(float x, float y, int** level) {
	_x = x;
	_y = y;
	_idleL.loadFromFile("Textures/Character/idle_left.png");
	_idleR.loadFromFile("Textures/Character/idle_right.png");
	_jumpL.loadFromFile("Textures/Character/jump_left.png");
	_jumpR.loadFromFile("Textures/Character/jump_right.png");
	_fallL.loadFromFile("Textures/Character/fall_left.png");
	_fallR.loadFromFile("Textures/Character/fall_right.png");
	_walkL[0].loadFromFile("Textures/Character/walk0_left.png");
	_walkR[0].loadFromFile("Textures/Character/walk0_right.png");
	_walkL[1].loadFromFile("Textures/Character/walk1_left.png");
	_walkR[1].loadFromFile("Textures/Character/walk1_right.png");
	_walkL[2].loadFromFile("Textures/Character/walk2_left.png");
	_walkR[2].loadFromFile("Textures/Character/walk2_right.png");
	_walkL[3].loadFromFile("Textures/Character/walk3_left.png");
	_walkR[3].loadFromFile("Textures/Character/walk3_right.png");
	_pickL.loadFromFile("Textures/Character/pick_left.png");
	_pickR.loadFromFile("Textures/Character/pick_right.png");
	_direction = Direction::RIGHT;
	idle();
	_level = level;
}

void Player::idle() {
	_state = State::IDLE;
	_sprite.setTexture(_direction == Direction::LEFT ? _idleL : _idleR);
	_walkCycle = 0;
}

void Player::walk() {
	_state = State::WALK;
	_sprite.setTexture(_direction == Direction::LEFT ? _walkL[_walkCycle] : _walkR[_walkCycle]);
	_x += (float) _direction*8;
	_walkCycle = (_walkCycle + 1) % 4;
}
void Player::jump(){}
void Player::fall(){}
void Player::pick(){}

void Player::draw(sf::RenderWindow* window) {
	_sprite.setPosition(_x, _y);
	window->draw(_sprite);
}