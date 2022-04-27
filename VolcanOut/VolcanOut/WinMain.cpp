#include <SFML/Graphics.hpp>
#include "Breakable.hpp"
#include "Unbreakable.hpp"
#include "Door.hpp"
#include "Player.hpp"
#include "Lava.hpp"
#include "Level.hpp"
#include <iostream>
#include <fstream>
#define LEVEL_WIDTH 12
#define LEVEL_HEIGHT 11

using namespace std;

int WinMain()
{
    //Window and textures initializations
    sf::RenderWindow window(sf::VideoMode(800, 800), "VolcanOut");
    sf::Texture breakableTex;
    breakableTex.loadFromFile("Textures/Breakable_tex.png");
    sf::Texture unbreakableTex;
    unbreakableTex.loadFromFile("Textures/UnBreakable_tex.png");
    sf::Texture lavaTex;
    lavaTex.loadFromFile("Textures/Lava_tex.png");
    sf::Texture doorTex;
    doorTex.loadFromFile("Textures/Door_Tex.png");
    sf::Clock clock;

    //View initialization
    sf::View view;

    //Level reading
    Level level("Level_files/Level1.txt", &window, &view);

    //Lava initialization
    Lava lava = Lava(&lavaTex, &level);

    //Player initialization
    Player player = Player(&level, &lava);

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
                switch (level.getTile(i,j)) {
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
                case 3:
                {
                    Door dTile((float)i, (float)j, &doorTex);
                    dTile.draw(&window);
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