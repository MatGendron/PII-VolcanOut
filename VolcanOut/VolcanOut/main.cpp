#include <SFML/Graphics.hpp>
#include "Breakable.hpp"

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "VolcanOut");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        
        //sf::Texture texture;
        //texture.loadFromFile("Breakable_tex.png");
        //sf::Sprite sprite;
        //sprite.setTexture(texture);

        window.clear();
        for (int i = 0; i < 100; i++) {
            for (int j = 0; j < 100; j++) {
                Breakable test = Breakable(16 * i, 16 * j);
                test.draw(&window);
            }
        }
        window.display();
    }

    return 0;
}