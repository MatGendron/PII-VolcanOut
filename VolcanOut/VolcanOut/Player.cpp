#include "Player.hpp"

using namespace std;

Player::Player(Level* level) {
	_x = level->getStartX()*16;
	_y = level->getStartY()*16;
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
	_level = level;
	idle();
	_gravity = 0.5;
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
		if (!checkCollision(Direction::DOWN)) {
			fall(true);
		}
		break;
	}
	
}

void Player::walk() {
	if (!checkCollision(_direction)) {
		_x += (float)_direction * 8;
	}
	if(_state != State::JUMP && _state!=State::FALL){
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
				_vertSpeed = 6;
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
			_vertSpeed = 0;
		}
		_sprite.setTexture(_direction == Direction::LEFT ? _fallL : _fallR);
		_vertSpeed = max(-6.f, _vertSpeed - _gravity);
		_y -= _vertSpeed;
	}
	else {
		_state = State::IDLE;
	}
}

void Player::pick(Direction dir){
	if (_state == State::IDLE || _state == State::WALK) {
		_state = State::PICK;
		_sprite.setTexture(_direction == Direction::LEFT ? _pickL : _pickR);
		int x; int y;
		switch (dir) {
		case Direction::UP:
			x = (int) _x / 16; y = (int)(_y - 1) / 16;
			break;
		case Direction::DOWN:
			x = (int)_x / 16; y = (int)(_y + 17) / 16;
			break;
		case Direction::RIGHT:
			x = (int)(_x + 17) / 16; y = (int)_y / 16;
			break;
		case Direction::LEFT:
			x = (int)(_x - 1) / 16; y = (int)_y / 16;
			break;
		default:
			throw std::runtime_error("Invalid direction in checkCollision call.");
			break;
		}
		if (_level->getTile(x,y) == 2) {
			_level->setTile(x,y,0);
		}
	}
	
}

void Player::place() {
	if (!checkCollision(Direction::DOWN) && (_state == State::JUMP || _state == State::FALL)) {
		_direction == Direction::LEFT ? _level->setTile((int)floor(_x / 16),(int)(_y + 24) / 16,2) :
			_level->setTile((int)ceil(_x / 16),(int)(_y + 24) / 16, 2);
	}
}

bool Player::checkCollision(Direction dir) {
	switch (dir) {
	case Direction::UP:
		return _level->getTile((int)floor((_x + 7) / 16),(int)(_y - 1) / 16) != 0 || _level->getTile((int) floor((_x+8) / 16),(int)(_y - 1) / 16) != 0;
		break;
	case Direction::DOWN:
		return _level->getTile((int)floor((_x + 7) / 16),(int)(_y + 17) / 16) != 0 || _level->getTile((int) floor((_x+8) / 16),(int)(_y + 17) / 16) != 0;
		break;
	case Direction::RIGHT:
		return _level->getTile((int)(_x + 17) / 16,(int) (_y+8) / 16) != 0;
		break;
	case Direction::LEFT:
		return _level->getTile((int)(_x - 1) / 16,(int) (_y+8) / 16) != 0;
		break;
	default:
		throw std::runtime_error("Invalid direction in checkCollision call.");
		break;
	}
}


void Player::processDirection(Direction dir) {
	if (_state == State::JUMP) {
		jump(false);
	}
	if (_state == State::FALL) {
		fall(false);
	}
	if (checkCollision(dir)) {
		pick(dir);
	}
	else {
		switch (dir) {
		case Direction::UP:
			if (_state != State::JUMP && _state != State::FALL) {
				jump(true);
			}
			break;
		case Direction::DOWN:
			place();
			break;
		case Direction::RIGHT:
			setDirection(dir);
			walk();
			break;
		case Direction::LEFT:
			setDirection(dir);
			walk();
			break;
		default:
			throw std::runtime_error("Invalid direction in processDirection call.");
			break;
		}
	}
}

void Player::draw(sf::RenderWindow* window) {
	_sprite.setPosition(_x, _y);
	window->draw(_sprite);
}