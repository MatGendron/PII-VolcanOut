#include "Player.hpp"

using namespace std;

Player::Player(Level* level, Lava* lava) {
	_x = level->getStartX()*16;
	_y = level->getStartY()*16;
	_blockCount = level->getBlockCount();
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
	_blockCounterTex.loadFromFile("Textures/BlockCount_Tex.png");
	_blockCounterSpt.setTexture(_blockCounterTex);
	_blockCounterSpt.setPosition(0, -16);
	if (!_font.loadFromFile("Fonts/8-bit-pusab.ttf")) {
		throw std::runtime_error("Couldn't load font for block counter.");
	}
	_blockCounterTxt.setFont(_font);
	_blockCounterTxt.setCharacterSize(6);
	_blockCounterTxt.setFillColor(sf::Color::White);
	_blockCounterTxt.setPosition(16, -8);
	_blockCounterTxt.setString(" X "+ std::to_string(_blockCount));
	_direction = Direction::RIGHT;
	_level = level;
	_lava = lava;
	instructions();
	_gravity = 0.5;
}

void Player::idle() {
	if (_state != State::MESG && _y + 16 > _lava->getHeight()) {
		lose();
	}
	switch (_state) {
	case State::JUMP:
		jump(false);
		break;
	case State::FALL:
		fall(false);
		break;
	case State::MESG:
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
		_y = round(_y / 16) * 16;
		_state = State::IDLE;
	}
}

void Player::pick(Direction dir){
	if (_clock.getElapsedTime().asMilliseconds() < 300) {
		return;
	}
	if (_state == State::IDLE || _state == State::WALK) {
		_state = State::PICK;
		_sprite.setTexture(_direction == Direction::LEFT ? _pickL : _pickR);
		int x; int y;
		switch (dir) {
		case Direction::UP:
			x = (int) (_x+8) / 16; y = (int)(_y - 1) / 16;
			break;
		case Direction::DOWN:
			x = (int) (_x+8) / 16; y = (int)(_y + 17) / 16;
			break;
		case Direction::RIGHT:
			x = (int)(_x + 17) / 16; y = (int) (_y+8) / 16;
			break;
		case Direction::LEFT:
			x = (int)(_x - 1) / 16; y = (int) (_y+8) / 16;
			break;
		default:
			throw std::runtime_error("Invalid direction in checkCollision call.");
			break;
		}
		if (_level->getTile(x,y) == 2) {
			_level->setTile(x,y,0);
			_blockCount += 1;
			_blockCounterTxt.setString(" X " + std::to_string(_blockCount));
			if (!checkCollision(Direction::DOWN)) {
				_state = State::FALL;
				_clock.restart();
			}
		}
	}
	
}

void Player::place() {
	if (_clock.getElapsedTime().asMilliseconds()>300 &&
		_blockCount > 0 && !checkCollision(Direction::DOWN) && 
		(_state == State::JUMP || _state == State::FALL)) {
		int x; int y;
		if (_direction == Direction::LEFT) {
			x = (int)floor(_x / 16); y = (int)(_y + 24) / 16;
		}
		else {
			x = (int)ceil(_x / 16); y = (int)(_y + 24) / 16;
		}
		if (_level->getTile(x, y) == 0) {
			_level->setTile(x, y, 2);
			_blockCount -= 1;
			_blockCounterTxt.setString(" X " + std::to_string(_blockCount));
			_clock.restart();
		}
	}
}

void Player::message(string msg, unsigned int size) {
	_state = State::MESG;
	if (!_font.loadFromFile("Fonts/8-bit-pusab.ttf")) {
		throw std::runtime_error("Couldn't load font for game over screen.");
	}
	_message.setFont(_font);
	_message.setString(msg);
	_message.setCharacterSize(size);
	_message.setFillColor(sf::Color::Yellow);
	sf::FloatRect messageRect = _message.getLocalBounds();
	_message.setOrigin(messageRect.width / 2.f, messageRect.height / 2);
	_message.setPosition(sf::Vector2f(_level->getWidth() * 8.f, _level->getHeight() * 8.f));
	_clock.restart();
}

void Player::instructions() {
	message(
		"  This game uses the four directionnal keys\n"
		"Press left and right to move left and right\n"
		"                           Press up to jump\n"
		" Press down while airborne to place a block\n"
		"              Press any key to start the game",
		4
	);
	_lava->setRising(false);
}

void Player::lose() {
	message(
		"                     You lose!\n"
		"Press any movement key to retry.",
		6
	);
}

void Player::win() {
	message(
		"                      You Win!\n"
		"Press any movement key to retry.",
		6
	);
	_lava->setRising(false);
}

bool Player::checkCollision(Direction dir) {
	switch (dir) {
	case Direction::UP:
	{
		int tileUpLeft = _level->getTile((int)floor((_x + 7) / 16), (int)(_y - 1) / 16);
		int tileUpRight = _level->getTile((int)floor((_x + 8) / 16), (int)(_y - 1) / 16);
		return (tileUpLeft != 0 || tileUpRight != 0) &&
			(tileUpLeft != 3 || tileUpRight != 3);
		break;
	}
	case Direction::DOWN:
	{
		int tileDownLeft = _level->getTile((int)floor((_x + 7) / 16), (int)(_y + 17) / 16);
		int tileDownRight = _level->getTile((int)floor((_x + 8) / 16), (int)(_y + 17) / 16);
		return (tileDownLeft != 0 || tileDownRight != 0) &&
			(tileDownLeft != 3 || tileDownRight != 3);
		break;
	}
	case Direction::RIGHT:
	{
		int tileRight = _level->getTile((int)(_x + 17) / 16, (int)(_y + 8) / 16);
		return tileRight != 0 && tileRight != 3;
		break;
	}
	case Direction::LEFT:
	{
		int tileLeft = _level->getTile((int)(_x - 1) / 16, (int)(_y + 8) / 16);
		return tileLeft != 0 && tileLeft != 3;
		break;
	}
	default:
		throw std::runtime_error("Invalid direction in checkCollision call.");
		break;
	}
}


void Player::processDirection(Direction dir) {
	if (_state == State::MESG) {
		if (_clock.getElapsedTime().asMilliseconds() < 500) {
			return;
		}
		else {
			_state == State::IDLE;
			_lava->reset();
			_level->reset();
			_x = _level->getStartX() * 16;
			_y = _level->getStartY() * 16;
			_blockCount = _level->getBlockCount();
			_blockCounterTxt.setString(" X " + std::to_string(_blockCount));
		}
	}
	if (dir == Direction::UP && _level->getTile((int)(_x + 8) / 16, (int)(_y + 8) / 16) == 3) {
		if (!_level->nextLevel()) {
			win();
		}
		else {
			_x = _level->getStartX() * 16;
			_y = _level->getStartY() * 16;
			_lava->updateParameters(_level);
			_blockCount = _level->getBlockCount();
			_blockCounterTxt.setString(" X " + std::to_string(_blockCount));
			return;
		}
	}
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
	if (_y + 16 > _lava->getHeight()) {
		lose();
	}
}

void Player::draw(sf::RenderWindow* window) {
	_sprite.setPosition(_x, _y);
	window->draw(_sprite);
	if (_state == State::MESG) {
		window->draw(_message);
	}
	window->draw(_blockCounterSpt);
	window->draw(_blockCounterTxt);
}