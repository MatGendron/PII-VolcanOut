#include <SFML/Graphics.hpp>
#include "Breakable.hpp"
#include "Unbreakable.hpp"
#include "Player.hpp"
#include <iostream>
#include <fstream>
#define LEVEL_WIDTH 12
#define LEVEL_HEIGHT 11

using namespace std;

int main()
{
    //Window and textures initializations
    sf::RenderWindow window(sf::VideoMode(800, 800), "VolcanOut");
    sf::Texture breakableTex;
    breakableTex.loadFromFile("Textures/Breakable_tex.png");
    sf::Texture unbreakableTex;
    unbreakableTex.loadFromFile("Textures/UnBreakable_tex.png");
    sf::Clock clock;

    //Level reading
    int** level;
    level = new int* [LEVEL_HEIGHT];
    for (int i = 0; i < LEVEL_HEIGHT; i++) {
        level[i] = new int[LEVEL_WIDTH];
    }
    
    ifstream levelFile;
    string line;
    levelFile.open("Level_files/Test_level.txt");
    if (levelFile.is_open()) {
        int i = 0;
        while (getline(levelFile, line)) {
            int j = 0;
            for (char& c : line) {
                //Conversion of char in file into int
                level[i][j] = c-'0'; 
                j++;
            }
            i++;
        }
    }

    //Player initialization
    Player player = Player(6, 9, level);

    sf::View view(sf::Vector2f(96.f, 80.f), sf::Vector2f(192.f, 190.f));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        for (int i = 0; i < LEVEL_HEIGHT; i++) {
            for (int j = 0; j < LEVEL_WIDTH; j++) {
                switch (level[i][j]) {
                case 1:
                {
                    Unbreakable bTile((float)j, (float)i, &unbreakableTex);
                    bTile.draw(&window);
                    break;
                }
                case 2:
                {
                    Breakable ubTile((float)j, (float)i, &breakableTex);
                    ubTile.draw(&window);
                    break;
                }
                default:
                    break;
                }
            }
        }
        if (clock.getElapsedTime().asMilliseconds() > 80) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                player.jump(true);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                player.setDirection(Direction::RIGHT);
                player.walk();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                player.setDirection(Direction::LEFT);
                player.walk();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                player.place();
            }
            if (event.type != sf::Event::KeyPressed) {
                player.idle();
            }
            clock.restart();
        }
        player.draw(&window);
        window.setView(view);
        window.display();
    }

    for (int i = 0; i < LEVEL_HEIGHT; i++) {
        delete[] level[i];
    }
    delete[] level;

    return 0;
}