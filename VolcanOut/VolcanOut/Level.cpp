#include "Level.hpp"

using namespace std;

Level::Level(const char* filename, sf::RenderWindow* window, sf::View* view) {
    _window = window;
    _view = view;
    loadNew(filename);
}

/*Beware that the coordinates for initiliazing and reading
* the level (for drawing or checking collision)
* are reversed.
*/
void Level::loadNew(const char* filename) {
    ifstream levelFile;
    string line;
    levelFile.open("Level_files/Test_level.txt");
    if (levelFile.is_open()) {
        getline(levelFile, line);
        loadMetaData(line);
        getline(levelFile, line);
        _nextLevel = line;
        _level = new int* [_levelWidth];
        _levelInit = new int* [_levelWidth];
        for (int i = 0; i < _levelWidth; i++) {
            _level[i] = new int[_levelHeight];
            _levelInit[i] = new int[_levelHeight];
        }
        int i = 0;
        while (getline(levelFile, line)) {
            int j = 0;
            for (char& c : line) {
                //Conversion of char in file into int
                _level[j][i] = c - '0';
                _levelInit[j][i] = c - '0';
                j++;
            }
            i++;
        }
    }
}

void Level::loadMetaData(string line) {
    int metaData[5] = { -1, -1, -1, -1, -1 };
    int start = 0;
    int end = line.find(' ');
    int i = 0;
    while (end != -1) {
        metaData[i] = stoi(line.substr(start, end - start));
        start = end+1;
        end = line.find(' ', start);
        i++;
    }
    _levelWidth = metaData[0];
    _levelHeight = metaData[1];
    _playerStartX = metaData[2];
    _playerStartY = metaData[3];
    _lavaSpeed = metaData[4];
}

void Level::reset() {
    for (int i = 0; i < _levelWidth; i++) {
        for (int j = 0; j < _levelHeight; j++) {
            _level[i][j] = _levelInit[i][j];
        }
    }
}

bool Level::nextLevel() {
    if (_nextLevel.compare("WIN")==0) {
        return false;
    }
    else {
        loadNew(_nextLevel.c_str());
        return true;
    }
}

void Level::deleteLevel() {
    for (int i = 0; i < _levelWidth; i++) {
        delete[] _level[i];
        delete[] _levelInit[i];
    }
    delete[] _level;
    delete[] _levelInit;
}

