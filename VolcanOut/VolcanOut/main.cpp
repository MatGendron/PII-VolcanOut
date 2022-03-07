#include <SFML/Graphics.hpp>
#include "Breakable.hpp"
#include "Unbreakable.hpp"
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

    //Level reading
    int level[LEVEL_HEIGHT][LEVEL_WIDTH];
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
                    Unbreakable bTile((float)j * 16, (float)i * 16, &unbreakableTex);
                    bTile.draw(&window);
                    break;
                }
                case 2:
                {
                    Breakable ubTile((float)j * 16, (float)i * 16, &breakableTex);
                    ubTile.draw(&window);
                    break;
                }
                default:
                    break;
                }
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            view.move(0.08, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            view.move(-0.08, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            view.move(0, -0.08);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            view.move(0, 0.08);
        }
        window.setView(view);
        window.display();
    }

    return 0;
}