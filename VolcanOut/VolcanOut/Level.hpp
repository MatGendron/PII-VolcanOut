#pragma once
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class Level {
public:
	Level(const char* filename);

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

	void loadNew(const char* filename);

	void loadMetaData(string line);

	void deleteLevel();

private:
	int** _level;
	int _levelHeight;
	int _levelWidth;
	int _playerStartX;
	int _playerStartY;
	int _lavaSpeed;
};