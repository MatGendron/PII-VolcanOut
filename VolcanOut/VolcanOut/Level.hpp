#pragma once
#include "SFML/Graphics.hpp"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class Level {
public:
	Level(const char* filename, sf::RenderWindow* window, sf::View* view);

	int getTile(int x, int y) {
		return _level[x][y];
	}

	void setTile(int x, int y, int val) {
		_level[x][y] = val;
	}

	int getStartX() {
		return _playerStartX;
	}

	int getStartY() {
		return _playerStartY;
	}

	int getWidth() {
		return _levelWidth;
	}

	int getHeight() {
		return _levelHeight;
	}

	int getSpeed() {
		return _lavaSpeed;
	}

	int getBlockCount() {
		return _startingBlockCount;
	}

	/*Loads a new level from a file
	*/
	void loadNew(const char* filename);

	/*Loads the meta data contained within a line of
	* level file.
	* Said metadata is comprised of:
	* - level width and height
	* - player's starting coordinates
	* - frequency at which the lava rises
	* - number of blocks the player starts with
	*/
	void loadMetaData(string line);

	/*Resets a level to its original state
	*/
	void reset();

	/*Loads the next level or triggers the game winning screen
	*/
	bool nextLevel();

	/*Deletes the dynamically allocated _level and _levelInit fields
	*/
	void deleteLevel();

private:
	int** _level;
	int** _levelInit;
	int _levelHeight;
	int _levelWidth;
	int _playerStartX;
	int _playerStartY;
	int _lavaSpeed;
	int _startingBlockCount;
	string _nextLevel;

	sf::RenderWindow* _window;
	sf::View* _view;
};