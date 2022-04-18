#pragma once
#include <SFML/Graphics.hpp>

using namespace std;

enum class Direction : int { LEFT=-1, RIGHT=1, UP, DOWN };
enum class State : int {WALK, IDLE, JUMP, FALL, PICK};

class Player {
public:
	Player(float x, float y, int** level);

	/*Sets the direction in of the player for use in choosing 
	* the proper direction's sprite.
	*/
	void setDirection(Direction dir) {
		_direction = dir;
	}

	////////////////////////////////////////////////////////

	/*The following functions allow the player character to perform the different actions
	* possible in the game, they change the player's sprite, move it and update the level
	* accordingly
	*/

	/*Idle pose, when the player is just on the ground and no key is pressed
	*/
	void idle();

	/*Walking or moving in the air towards the left or right
	*/
	void walk();

	/*Jumping a set distance.
	* init has to be set to true when starting
	* a jump from the ground
	*/
	void jump(bool init);

	/*Falling from a platform or while in the air after a jump
	* init has to be set to true when the player starts falling
	*/
	void fall(bool init);

	/*Break a breakable block in the dir direction
	* That block is removed from the level and a placable block is
	* added to the player's block count
	*/
	void pick(Direction dir);

	/*The player places a block on a free tile bellow him
	* One block is consumed from the player's block count
	*/
	void place();

	////////////////////////////////////////////////////////

	/*Check if the next tile in the Direction dir is occupied
	* Returns true if there is a tile in that direction
	*/
	bool checkCollision(Direction dir);

	/*Make player perform an action according to the dir
	* parameter and the player's direct environment
	*/
	void processDirection(Direction dir);

	//Draw the player on the window
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