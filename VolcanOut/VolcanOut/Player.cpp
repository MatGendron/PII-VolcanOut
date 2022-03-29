#include "Player.hpp"
#include <iostream>

using namespace std;

Player::Player(float x, float y, int** level) {
	_x = x*16;
	_y = y*16;
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
	_gravity = 2;
}

void Player::idle() {
	switch (_state) {
	case State::JUMP:
		jump(false);
		break;
	case State::FALL:
		fall(false);
		break;
	default:
		_state = State::IDLE;
		_sprite.setTexture(_direction == Direction::LEFT ? _idleL : _idleR);
		_walkCycle = 0;
		break;
	}
	
}

void Player::walk() {
	if (!checkCollision(_direction)) {
		_x += (float)_direction * 8;
	}
	switch (_state) {
	case State::JUMP:
		jump(false);
		break;
	case State::FALL:
		fall(false);
		break;
	default:
		_state = State::WALK;
		_sprite.setTexture(_direction == Direction::LEFT ? _walkL[_walkCycle] : _walkR[_walkCycle]);
		_walkCycle = (_walkCycle + 1) % 4;
		if (!checkCollision(Direction::DOWN)) {
			fall(true);
		}
	}
}

void Player::jump(bool init){
	if (!checkCollision(Direction::UP)){
		if (_state == State::IDLE || _state == State::WALK) {
			_state = State::JUMP;
			if (init) {
				_vertSpeed = 12;
			}
		}
		_sprite.setTexture(_direction == Direction::LEFT ? _jumpL : _jumpR);
		_vertSpeed = max(0.0f, _vertSpeed - _gravity);
		if (_vertSpeed > 0) {
			_y -= _vertSpeed;
		}
		else {
			fall(true);
		}
	}
	else if(_state==State::JUMP) {
		fall(true);
	}
}

void Player::fall(bool init){
	if (!checkCollision(Direction::DOWN)) {
		if (init) {
			_state = State::FALL;
			_vertSpeed = -2;
		}
		_sprite.setTexture(_direction == Direction::LEFT ? _fallL : _fallR);
		_vertSpeed = max(-12.f, _vertSpeed - _gravity);
		_y -= _vertSpeed;
	}
	else {
		_state = State::IDLE;
	}
}

void Player::pick(){}

void Player::place() {
	if (!checkCollision(Direction::DOWN) && (_state == State::JUMP || _state == State::FALL)) {
		_direction == Direction::LEFT ? _level[(int)(_y + 24) / 16][(int)floor(_x / 16)] = 2 :
			_level[(int)(_y + 24) / 16][(int)ceil(_x / 16)] = 2;
	}
}

/*Checks if the next tile in the Direction dir is occupied
* Returns true if there is a tile in that direction
*/
bool Player::checkCollision(Direction dir) {
	switch (dir) {
	case Direction::UP:
		return _level[(int) (_y - 1) / 16][(int)floor(_x / 16)] != 0 || _level[(int)(_y - 1) / 16][(int)ceil(_x / 16)] != 0;
		break;
	case Direction::DOWN:
		return _level[(int)(_y+17) / 16][(int)floor(_x / 16)] != 0 || _level[(int)(_y+17) / 16][(int)ceil(_x / 16)] != 0;
		break;
	case Direction::RIGHT:
		return _level[(int)_y / 16][(int)(_x + 17) / 16] != 0;
		break;
	case Direction::LEFT:
		return _level[(int)_y / 16][(int)(_x - 1) / 16] != 0;
		break;
	default:
		throw std::runtime_error("Invalid direction in checkCollision call.");
		break;
	}
}

void Player::draw(sf::RenderWindow* window) {
	_sprite.setPosition(_x, _y);
	window->draw(_sprite);
}