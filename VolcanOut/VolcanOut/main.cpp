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
        
        Breakable test = Breakable(10, 10);
        //sf::Texture texture;
        //texture.loadFromFile("Breakable_tex.png");
        //sf::Sprite sprite;
        //sprite.setTexture(texture);

        window.clear();
        //window.draw(sprite);
        test.draw(&window);
        window.display();
    }

    return 0;
}