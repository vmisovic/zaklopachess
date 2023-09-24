#include <SFML/Graphics.hpp>

#include "../lib/game.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(1024, 1024), "zaklopachess");
    window.setFramerateLimit(60);

    Game game;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if(event.type == sf::Event::MouseButtonPressed){
                if(event.mouseButton.button == sf::Mouse::Left){
                    game.move(event.mouseButton.y/128, event.mouseButton.x/128);
                }
            }
        }

        window.clear();
        game.draw(window);
        window.display();
    }
    return 0;
}
