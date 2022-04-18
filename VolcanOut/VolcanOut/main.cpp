#include <SFML/Graphics.hpp>
#include "Breakable.hpp"
#include "Unbreakable.hpp"
#include "Player.hpp"
#include "Lava.hpp"
#include "Level.hpp"
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
    sf::Texture lavaTex;
    lavaTex.loadFromFile("Textures/Lava_tex.png");
    sf::Clock clock;

    //Level reading
    Level level("Level_files/Test_level.txt");

    //Player initialization
    Player player = Player(&level);

    sf::View view(sf::Vector2f(96.f, 80.f), sf::Vector2f(192.f, 190.f));

    //Lava initialization
    Lava lava = Lava(&lavaTex, &level);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        for (int i = 0; i < LEVEL_WIDTH; i++) {
            for (int j = 0; j < LEVEL_HEIGHT; j++) {
                switch (level.getLevel()[i][j]) {
                case 1:
                {
                    Unbreakable bTile((float)i, (float)j, &unbreakableTex);
                    bTile.draw(&window);
                    break;
                }
                case 2:
                {
                    Breakable ubTile((float)i, (float)j, &breakableTex);
                    ubTile.draw(&window);
                    break;
                }
                default:
                    break;
                }
            }
        }

        if (clock.getElapsedTime().asMilliseconds() > 80) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                player.processDirection(Direction::RIGHT);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                player.processDirection(Direction::LEFT);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                player.processDirection(Direction::UP);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                player.processDirection(Direction::DOWN);
            }
            if (event.type != sf::Event::KeyPressed) {
                player.idle();
            }
            clock.restart();
        }
        lava.rise();
        lava.draw(&window, LEVEL_WIDTH, LEVEL_HEIGHT);
        player.draw(&window);
        window.setView(view);
        window.display();
    }

    //Deletion of alloted space for level
    level.deleteLevel();

    return 0;
}