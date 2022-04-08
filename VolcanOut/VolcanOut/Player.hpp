#pragma once
#include <SFML/Graphics.hpp>

using namespace std;

enum class Direction : int { LEFT=-1, RIGHT=1, UP, DOWN };
enum class State : int {WALK, IDLE, JUMP, FALL, PICK};

class Player {
public:
	Player(float x, float y, int** level);

	void setDirection(Direction dir) {
		_direction = dir;
	}

	void idle();
	void walk();
	void jump(bool init);
	void fall(bool init);
	void pick(Direction dir);
	void place();

	bool checkCollision(Direction dir);

	void processDirection(Direction dir);

	void draw(sf::RenderWindow* window);


private:
	float _x;
	float _y;
	sf::Texture _idleL;
	sf::Texture _idleR;
	sf::Texture _jumpL;
	sf::Texture _jumpR;
	sf::Texture _fallL;
	sf::Texture _fallR;
	sf::Texture _walkL[4];
	sf::Texture _walkR[4];
	sf::Texture _pickL;
	sf::Texture _pickR;

	Direction _direction;
	State _state;

	sf::Sprite _sprite;

	int _walkCycle;
	float _vertSpeed;

	float _gravity;

	int** _level;
};