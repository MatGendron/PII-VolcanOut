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

	void loadNew(const char* filename);

	void loadMetaData(string line);

	void reset();

	bool nextLevel();

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